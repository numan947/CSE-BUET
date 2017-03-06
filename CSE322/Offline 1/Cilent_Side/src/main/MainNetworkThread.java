package main;

import java.io.IOException;
import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.Socket;
import java.net.URL;

/**
 * Created by numan947 on 3/5/17.
 **/
public class MainNetworkThread implements Runnable {
    private client_main_gui_controller controller;
    private String examCode;
    private String studentID;
    private String ipAddress;
    private int port;
    private byte[]buff=null;

    public MainNetworkThread(client_main_gui_controller controller, String examCode, String studentID, String ipAddress, int port) {
        this.studentID = studentID;
        this.ipAddress = ipAddress;
        this.port = port;
        this.examCode=examCode;
        this.controller=controller;
        buff=new byte[8192];
    }

    @Override
    public void run() {
        NetworkUtil networkUtil=null;
        try {
            networkUtil = new NetworkUtil(ipAddress, port);

            //send student id and exam code
            String data=examCode+"$$$$"+studentID;
            networkUtil.writeBuff(data.getBytes());
            networkUtil.flushStream();

            //reading server's response
            int cnt=networkUtil.readBuff(buff);
            String s=new String(buff,0,cnt);

            //if response is "APPROVED"
            if(s.equals("APPROVED")){

                //send msg for size of the details string
                networkUtil.writeBuff("REQUESTING_SIZE_OF_DETAILS_STRING".getBytes());

                //now we wait for the server to send the size of the details
                cnt=networkUtil.readBuff(buff);
                s=new String(buff,0,cnt);

                int sizeOfDetails=Integer.parseInt(s);

                //send acknowledgement of receiving the size
                networkUtil.writeBuff("SIZE_RECEIVED".getBytes());

                //after this we'll start receiving a big msg, so, to read we make another method
                String fullmsg=readNBytes(sizeOfDetails,networkUtil);
                //now we decode the fullmsg
                String[]info=fullmsg.split("\\$\\$\\$\\$");
                //todo the rest will be done of wednesday inshallah :)


            }else{
                //todo what'll happen if the server sends something else?
            }








        } catch (IOException e) {
            //todo show with alertDialog?
            e.printStackTrace();
        }


    }

    private String readNBytes(int sizeOfDetails, NetworkUtil networkUtil) throws IOException {
        int cnt=0;
        int tmp=0;
        StringBuilder toReturn=new StringBuilder();
        while(cnt>=sizeOfDetails||tmp==-1){
            tmp=networkUtil.readBuff(buff);
            cnt+=tmp;
            toReturn.append(new String(buff,0,tmp));
        }
        return toReturn.toString();
    }
}
