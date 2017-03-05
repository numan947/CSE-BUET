package main;

import java.io.IOException;
import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.Socket;
import java.net.URL;

/**
 * Created by numan947 on 3/5/17.
 **/
public class NetworkThread implements Runnable {
    private String studentID;
    private String ipAddress;
    private int port;

    public NetworkThread(String studentID, String ipAddress, int port) {
        this.studentID = studentID;
        this.ipAddress = ipAddress;
        this.port = port;
    }

    @Override
    public void run() {
        NetworkUtil networkUtil=null;
        try {
            networkUtil = new NetworkUtil(ipAddress, port);
        } catch (IOException e) {
            e.printStackTrace();
        }







    }
}
