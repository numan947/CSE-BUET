package main;

import java.io.File;
import java.util.Date;

/**
 * Created by numan947 on 3/5/17.
 **/
public class Participant {
    private String ipAddress;
    private String examCode;
    private File backupStoragePath;
    private Date startTime;
    private FileTransferThread fileTransferThread;
    private int backupInterval;
    private File currentBackupFile;//the file that'll be sent in case of crash;
    private long nextScheduledBackup;//the next scheduled backup time, it'll be accessed by backupchecker thread,
                                        //and update by filetransferthread



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

    public Participant(String ipAddress, String examCode) {
        this.ipAddress = ipAddress;
        this.examCode = examCode;
        this.currentBackupFile=null;
        this.nextScheduledBackup=-1;
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

    public Date getStartTime() {
        return startTime;
    }

    public void setStartTime(Date startTime) {
        this.startTime = startTime;
    }
}
