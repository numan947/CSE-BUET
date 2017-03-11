package main;

import sun.applet.Main;

import java.io.File;
import java.util.ArrayList;
import java.util.Date;

/**
 * Created by numan947 on 3/5/17.
 **/
public class Participant {
    private String ipAddress;
    private String examCode;
    private File backupStoragePath;
    private int remainingTimeInSeconds;
    private FileTransferThread fileTransferThread;
    private MainNetworkThread mainNetworkThread;
    private int backupInterval;
    private File currentBackupFile;//the file that'll be sent in case of crash;
    private long nextScheduledBackup;//the next scheduled backup time, it'll be accessed by backupchecker thread,
                                        //and update by filetransferthread
    private boolean crashed;
    private boolean timeup;
    private ArrayList<String>correctionSent;



    public Participant(String ipAddress, String examCode) {
        this.ipAddress = ipAddress;
        this.examCode = examCode;
        this.currentBackupFile=null;
        this.nextScheduledBackup=-1;
        this.crashed=false;
        this.timeup=false;
        this.correctionSent=new ArrayList<>();
        this.remainingTimeInSeconds=-1;
    }

    public ArrayList<String> getCorrectionSent() {
        return correctionSent;
    }
    public MainNetworkThread getMainNetworkThread() {
        return mainNetworkThread;
    }

    public void setMainNetworkThread(MainNetworkThread mainNetworkThread) {
        this.mainNetworkThread = mainNetworkThread;
    }
    public void setCorrectionSent(ArrayList<String> correctionSent) {
        this.correctionSent = correctionSent;
    }

    public boolean isTimeup() {
        return timeup;
    }

    public void setTimeup(boolean timeup) {
        this.timeup = timeup;
    }

    public boolean isCrashed() {
        return crashed;
    }

    public void setCrashed(boolean crashed) {
        this.crashed = crashed;
    }

    public File getCurrentBackupFile() {
        return currentBackupFile;
    }

    public void setCurrentBackupFile(File currentBackupFile) {
        this.currentBackupFile = currentBackupFile;
    }

    public long getNextScheduledBackup() {
        return nextScheduledBackup;
    }

    public void setNextScheduledBackup(long nextScheduledBackup) {
        this.nextScheduledBackup = nextScheduledBackup;
    }

    public int getBackupInterval() {
        return backupInterval;
    }

    public void setBackupInterval(int backupInterval) {
        this.backupInterval = backupInterval;
    }

    public FileTransferThread getFileTransferThread() {
        return fileTransferThread;
    }

    public void setFileTransferThread(FileTransferThread fileTransferThread) {
        this.fileTransferThread = fileTransferThread;
    }

    public File getBackupStoragePath() {
        return backupStoragePath;
    }

    public void setBackupStoragePath(File backupStoragePath) {
        this.backupStoragePath = backupStoragePath;
    }

    public String getIpAddress() {
        return ipAddress;
    }

    public void setIpAddress(String ipAddress) {
        this.ipAddress = ipAddress;
    }

    public String getExamCode() {
        return examCode;
    }

    public void setExamCode(String examCode) {
        this.examCode = examCode;
    }

    public int getRemainingTimeInSeconds() {
        return remainingTimeInSeconds;
    }

    public void setRemainingTimeInSeconds(int remainingTimeInSeconds) {
        this.remainingTimeInSeconds = remainingTimeInSeconds;
    }
}
