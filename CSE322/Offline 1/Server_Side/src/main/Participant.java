package main;

import java.io.File;
import java.net.URL;
import java.util.Date;

/**
 * Created by numan947 on 3/5/17.
 **/
public class Participant {
    private String ipAddress;
    private String examCode;
    private File backupStoragePath;

    private Date startTime;

    public File getBackupStoragePath() {
        return backupStoragePath;
    }

    public void setBackupStoragePath(File backupStoragePath) {
        this.backupStoragePath = backupStoragePath;
    }

    public Participant(String ipAddress, String examCode) {
        this.ipAddress = ipAddress;
        this.examCode = examCode;
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
