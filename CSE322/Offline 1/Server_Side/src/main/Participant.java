package main;

import java.net.Socket;
import java.util.Date;

/**
 * Created by numan947 on 3/5/17.
 **/
public class Participant {
    private String ipAddress;
    private String examCode;
    private NetworkUtil networkUtil;
    private Date startTime;

    public Participant(String ipAddress, String examCode, NetworkUtil networkUtil) {
        this.ipAddress = ipAddress;
        this.examCode = examCode;
        this.networkUtil = networkUtil;
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

    public NetworkUtil getNetworkUtil() {
        return networkUtil;
    }

    public void setNetworkUtil(NetworkUtil networkUtil) {
        this.networkUtil = networkUtil;
    }

    public Date getStartTime() {
        return startTime;
    }

    public void setStartTime(Date startTime) {
        this.startTime = startTime;
    }
}
