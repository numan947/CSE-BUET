package main;

import javafx.application.Platform;

import java.io.*;
import java.util.Date;

/**
 * Created by numan947 on 3/5/17.
 **/
public class MainNetworkThread implements Runnable {
    private Client_GUI_Controller controller;
    private String examCode;
    private String studentID;
    private String ipAddress;
    private int port;
    private byte[]buff=null;
    private File fileLocation;
    private boolean running;
    private Thread t;
    public MainNetworkThread(Client_GUI_Controller controller, String examCode, String studentID, String ipAddress, int port,File fileLocation) {
        this.studentID = studentID;
        this.ipAddress = ipAddress;
        this.port = port;
        this.examCode=examCode;
        this.controller=controller;
        this.fileLocation=fileLocation;
        buff=new byte[8192];
        this.running=true;

        t=new Thread(this);
        t.setDaemon(true);
        t.start();

    }

    @Override
    public void run() {
        int cnt;
        String msg;
        NetworkUtil networkUtil=null;
        try {
            networkUtil = new NetworkUtil(ipAddress, port);

            //send requestType
            networkUtil.writeBuff("NEW_CONNECTION".getBytes());
            networkUtil.flushStream();

            cnt=networkUtil.readBuff(buff);
            msg=new String(buff,0,cnt);

            if(msg.equals("SEND_ADDITIONAL_INFO")){


                //send student id and exam code; $$$$ is our separator for multiple string information
                String data=examCode+"$$$$"+studentID;
                networkUtil.writeBuff(data.getBytes());
                networkUtil.flushStream();



                //reading server's response
                cnt=networkUtil.readBuff(buff);
                msg=new String(buff,0,cnt);

                //if response is "APPROVED"
                if(msg.equals("APPROVED")) {

                    //send msg for size of the details string
                    networkUtil.writeBuff("REQUESTING_SIZE_OF_DETAILS_STRING".getBytes());
                    networkUtil.flushStream();

                    //now we wait for the server to send the size of the details
                    cnt = networkUtil.readBuff(buff);
                    msg = new String(buff, 0, cnt);

                    int sizeOfDetails = Integer.parseInt(msg);

                    //send acknowledgement of receiving the size
                    networkUtil.writeBuff("SIZE_RECEIVED".getBytes());
                    networkUtil.flushStream();

                    //after this we'll start receiving a big msg, so, to read we make another method
                    cnt=networkUtil.readBuff(buff);
                    String fullmsg=new String(buff,0,cnt);

                    //now we decode the fullmsg:

                    //set the basic info appropriatelys

                    controller.setAll(fullmsg);

                    //todo may be we'll need clean up here
                    String[] info = fullmsg.split("\\$\\$\\$\\$");
                    //parsed all the basic info

                    String e_c = info[0];
                    String examName = info[1];
                    int duration = Integer.parseInt(info[2]);
                    int backupInterval = Integer.parseInt(info[3]);
                    int warningTime = Integer.parseInt(info[4]);
                    long startTimeInLong = Long.parseLong(info[5]);
                    Date startTime = new Date(startTimeInLong);

                    networkUtil.writeBuff("DATA_RECEIVED".getBytes());
                    networkUtil.flushStream();

                    cnt=networkUtil.readBuff(buff);

                    msg=new String(buff,0,cnt);

                   // System.out.println(msg);

                    String[]tmp=msg.split("\\$\\$\\$\\$");
                    String fileName=tmp[0];
                    long fileSize= Long.parseLong(tmp[1]);

                    networkUtil.writeBuff("SEND_QUESTION".getBytes());
                    networkUtil.flushStream();

                    int totalRead=0;
                    boolean corrupted=false;



                    File fileToSave=new File(fileLocation,fileName);

                    if(!fileToSave.exists())fileToSave.createNewFile();


                    //file transfer start
                    FileOutputStream fos=new FileOutputStream(fileToSave);
                    BufferedOutputStream fbuff=new BufferedOutputStream(fos);
                    cnt=0;
                    totalRead=0;
                    while (true) {
                        if (cnt >= fileSize||totalRead==-1) break;
                        totalRead = networkUtil.readBuff(buff);
                        cnt += totalRead;
                        writeToFile(buff, totalRead,cnt,fbuff);
                        System.out.println(fileSize + "  " + totalRead);
                    }
                    if(cnt < fileSize||totalRead==-1){
                        System.out.println("Problem while transferring file..probably file's become corrupted");
                        corrupted=true;
                        fileToSave.delete();
                    }
                    if(!corrupted){
                        networkUtil.writeBuff("QUESTION_RECEIVED".getBytes());
                        networkUtil.flushStream();
                    }
                    fbuff.close();
                    fos.close();
                    //file transfer finished


                    //now we start our FileTransferThread that'll do the backup
                    cnt=networkUtil.readBuff(buff);
                    msg=new String(buff,0,cnt);
                    if(msg.equals("INITIATE_FILE_TRANSFER_THREAD")){
                        new FileTransferThread(this,examCode,studentID,ipAddress,port,backupInterval,fileToSave);
                    }


                    //now we wait for any correction or something :)

                    while(running&&!Thread.interrupted()){
                        networkUtil.readBuff(buff);



                    }













                }
                else{

                }

            }else{
                //todo what'll happen if the server sends something else?
            }

        } catch (IOException e) {
            //todo show with alertDialog?
            Platform.runLater(new Runnable() {
                @Override
                public void run() {
                    controller.clearConnectButton();
                }
            });

            e.printStackTrace();
        }


    }


    private void writeToFile(byte[] b, int totalRead, int cnt, BufferedOutputStream fbuff)
    {
        try {
            fbuff.write(b,0,totalRead);
            if(cnt>=8192)fbuff.flush();
        } catch (IOException e) {
            System.out.println("Exception In ServerPackage.FileProcessingThread.writeToFile "+e.getMessage());
        }
    }

    public void setRunning(boolean running) {
        this.running = running;
    }

    public Thread getT() {
        return t;
    }

    public void setT(Thread t) {
        this.t = t;
    }
}
