package main;

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

    public FileTransferThread(MainNetworkThread parentThread, String examCode, String studentID, String ipAddress, int port,int backupInterval) {
        this.parentThread = parentThread;
        this.examCode = examCode;
        this.studentID = studentID;
        this.ipAddress = ipAddress;
        this.port = port;
        this.backupInterval=backupInterval;
    }


    @Override
    public void run() {

    }
}
