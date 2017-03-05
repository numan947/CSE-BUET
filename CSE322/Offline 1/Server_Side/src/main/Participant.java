package main;

import java.net.Socket;
import java.util.Date;

/**
 * Created by numan947 on 3/5/17.
 **/
public class Participant {
    private String ipAddress;
    private String examCode;
    private Socket socket;
    private Date startTime;

    public Participant(String ipAddress, String examCode, Socket socket) {
        this.ipAddress = ipAddress;
        this.examCode = examCode;
        this.socket = socket;
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

    public Socket getSocket() {
        return socket;
    }

    public void setSocket(Socket socket) {
        this.socket = socket;
    }

    public Date getStartTime() {
        return startTime;
    }

    public void setStartTime(Date startTime) {
        this.startTime = startTime;
    }
}
