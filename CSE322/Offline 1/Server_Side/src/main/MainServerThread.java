package main;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by numan947 on 3/9/17.
 **/
public class MainServerThread implements Runnable {
    private boolean stopServer;
    private Server_GUI_Controller controller;
    private ServerSocket serverSocket;
    private InetAddress ipAddress;
    private int port;

    public MainServerThread(Server_GUI_Controller controller,String ipAddress,int port) throws IOException {
        this.controller=controller;
        this.stopServer=false;
        if(!ipAddress.equals(""))this.ipAddress=InetAddress.getByName(ipAddress);
        else this.ipAddress=null;

        this.port=port;
        this.serverSocket=new ServerSocket(port,50, this.ipAddress);

        Thread t=new Thread(this);
        t.setDaemon(true);
        t.start();
    }


    public void setStopServer(boolean stopServer) {
        this.stopServer = stopServer;
        if(!stopServer){
            //re-initiate the thread
            Thread t=new Thread(this);
            t.setDaemon(true);
            t.start();
        }
    }


    @Override
    public void run() {
        while (!stopServer){
            System.out.println("HELLO FROM SERVER");
            try {
                Socket accept=serverSocket.accept();
                final NetworkUtil util=new NetworkUtil(accept);


                //a thread that handles sorting the thread to the right types (i.e fileTransfer/newConnection)
                new Thread(() -> {
                    byte[]buff=new byte[8192];
                    try {

                        //read and convert the very first msg
                        int cnt=util.readBuff(buff);
                        String msg=new String(buff,0,cnt);

                        // send msg to tell the client to send additional information
                        // and create the proper threads

                        if(msg.equals("NEW_CONNECTION")){
                            //open new networkThread as it's a new connection
                            util.writeBuff("SEND_ADDITIONAL_INFO".getBytes());
                            util.flushStream();
                            new MainNetworkThread(this,util);

                        }
                        else if(msg.equals("FILE_TRANSFER")){
                            //open a file transfer thread
                            util.writeBuff("SEND_ADDITIONAL_INFO".getBytes());
                            util.flushStream();
                            // todo new FileTransferThread();
                        }
                        else{
                            util.closeAll();
                        }

                    } catch (IOException e) {
                        e.printStackTrace();
                    }


                }).start();


            } catch (IOException e) {
                e.printStackTrace();
            }

        }
    }

    public synchronized Server_GUI_Controller getController() {
        return controller;
    }
}
