package main;

import sun.nio.ch.Net;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Date;

/**
 * Created by numan947 on 3/6/17.
 **/
public class FileTransferThread implements Runnable {
    private NetworkUtil util;
    MainNetworkThread parentThread;
    private String examCode;
    private String studentID;
    private String ipAddress;
    private int port;
    private int backupInterval;
    private boolean running;

    private Exam exam;
    private Participant participant;

    public FileTransferThread(MainNetworkThread parentThread, String examCode, String studentID, String ipAddress, int port, int backupInterval) {
        this.parentThread = parentThread;
        this.examCode = examCode;
        this.studentID = studentID;
        this.ipAddress = ipAddress;
        this.port = port;
        this.backupInterval=backupInterval;
    }

    public FileTransferThread(NetworkUtil util,Participant participant)
    {
        this.util=util;
        this.participant=participant;
    }

    public void setUtil(NetworkUtil util) {
        this.util = util;
    }

    public NetworkUtil getUtil() {
        return util;
    }

    public void runThread()
    {
        this.running=true;
        Thread t=new Thread(this);
        t.setDaemon(true);
        t.start();
    }

    public void stopThread(boolean running){
        this.running=false;
        try {
            util.closeAll();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    @Override
    public void run() {

        byte[]buff=new byte[8192];
        int cnt=0;
        String msg=null;
        System.out.println(counter());
        try {
            util.writeBuff("CONFIRMED".getBytes());
            util.flushStream();


            System.out.println(counter());

            while(running){
                receiveBackup(this.util,cnt,msg,buff,null);
            }
        } catch (Exception e) {
            if(e.getMessage().toLowerCase().contains("string index out of range: -1")||
                    e.getMessage().toLowerCase().contains("socket closed")){
                //handle crash

                if(running){
                    participant.setCrashed(true);
                    participant.setTimeup(false);
                }
            }
            e.printStackTrace();
        }

    }


    public void receiveBackup(NetworkUtil util,int cnt,String msg,byte[]buff,String spc) throws IOException {

        cnt=util.readBuff(buff);
        msg=new String(buff,0,cnt);

        System.out.println(counter());
        String[] tmp=msg.split("\\$\\$\\$\\$");

        String fileName=new Date().toString()+"_"+tmp[0];
        if(spc!=null)fileName=spc+"_"+fileName;
        System.out.println(fileName);

        long fileSize= Long.parseLong(tmp[1]);
        System.out.println(counter());

        util.writeBuff("SEND_NOW".getBytes());
        util.flushStream();


        int totalRead=0;
        boolean corrupted=false;

        if(!participant.getBackupStoragePath().exists())participant.getBackupStoragePath().mkdirs();
        File fileToSave=new File(participant.getBackupStoragePath(),fileName);
        if(!fileToSave.exists())fileToSave.createNewFile();
        System.out.println(counter());

        //file transfer start
        FileOutputStream fos=new FileOutputStream(fileToSave);
        BufferedOutputStream fbuff=new BufferedOutputStream(fos);
        cnt=0;
        totalRead=0;
        while (true) {
            if (cnt == fileSize||totalRead==-1){
                break;
            }
            totalRead = util.readBuff(buff);
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
            util.writeBuff("BACKUP_RECEIVED".getBytes());
            util.flushStream();

            //giving 2 second extra time to send some backup
            participant.setNextScheduledBackup(System.currentTimeMillis()+participant.getBackupInterval()+Server_GUI_Controller.backupepstime);
            participant.setCurrentBackupFile(fileToSave);
        }
        fbuff.close();
        fos.close();

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

    private static int kaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa=0;
    private String  counter()
    {
        return ++kaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa+"WHY MAN??????";
    }
}
