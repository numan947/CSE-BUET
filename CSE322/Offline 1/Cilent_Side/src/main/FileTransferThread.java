package main;

import java.io.*;

/**
 * Created by numan947 on 3/6/17.
 **/
public class FileTransferThread implements Runnable {
    MainNetworkThread parentThread;
    private String examCode;
    private String studentID;
    private String ipAddress;
    private int port;
    private int backupInterval;
    private File file;
    private boolean running;
    private byte[]buff;
    private  NetworkUtil util=null;

    public FileTransferThread(MainNetworkThread parentThread, String examCode, String studentID, String ipAddress, int port, int backupInterval, File fileToSave) {
        this.parentThread = parentThread;
        this.examCode = examCode;
        this.studentID = studentID;
        this.ipAddress = ipAddress;
        this.port = port;
        this.backupInterval=backupInterval;
        this.file=fileToSave;
        this.running=true;
        buff=new byte[8192];
        Thread t=new Thread(this);
        t.setDaemon(true);
        t.start();
    }

    public void setRunning(boolean running) {
        this.running = running;
        try {
            util.closeAll();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        System.out.println(counter());
        int cnt=0;
        String msg;

        try {
            util=new NetworkUtil(ipAddress,port);
            util.writeBuff((studentID+"$$$$"+"FILE_TRANSFER").getBytes());
            util.flushStream();


            System.out.println(counter());
            //wait for confirmation
            cnt=util.readBuff(buff);
            msg=new String(buff,0,cnt);



            System.out.println(counter());
            if(msg.equals("CONFIRMED")){

                while(running){
                    System.out.println(backupInterval);
                    Thread.sleep(backupInterval);// sleep for this period, then send a backup


                    System.out.println(counter());
                    sendBackup(util);
                    System.out.println(counter());
                }
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

    }

    private void sendBackup(NetworkUtil util) throws IOException {


        String details=file.getName()+"$$$$"+file.length();
        //send the details first and then the file
        util.writeBuff(details.getBytes());
        util.flushStream();



        int cnt=util.readBuff(buff);

        if(new String(buff,0,cnt).equals("SEND_NOW")) {

            System.out.println(counter()+"Hellow");
            BufferedInputStream fbuff = new BufferedInputStream(new FileInputStream(file));
            int tmpCt = 0;
            int totalRead = 0;
            while ((totalRead = getBuffFromFile(buff, fbuff)) > -1) {
                tmpCt += totalRead;
                util.writeBuff(buff, 0, totalRead);
                if (tmpCt >= 8192) {
                    util.flushStream();
                    tmpCt = 0;
                }

            }
            util.flushStream();
            fbuff.close();

            cnt=util.readBuff(buff);
            System.out.println(new String (buff,0,cnt));

        }
    }

    private int getBuffFromFile(byte[]buff, BufferedInputStream fbuff)
    {
        try {
            return fbuff.read(buff);
        } catch (IOException e) {
            System.out.println("Exception In ClientPackage.Client.getBuffFromFile "+e.getMessage());
        }
        return 0;
    }

    private static int kaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa=0;
    private String  counter()
    {
        return ++kaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa+"WHY MAN??";
    }
}
