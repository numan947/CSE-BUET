package main;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Random;

/**
 * Created by numan947 on 10/26/16.
 **/
public class NetworkUtil {
    private BufferedInputStream is=null;
    private BufferedOutputStream os=null;
    private Socket socket=null;
    private int DEFAULT_BUFFER_SIZE=12000;
    private int BUFFER_SIZE;

    public NetworkUtil(Socket socket) throws IOException {
        try {
            this.socket = socket;
            this.os=new BufferedOutputStream(socket.getOutputStream(),DEFAULT_BUFFER_SIZE);
            this.is=new BufferedInputStream(socket.getInputStream(),DEFAULT_BUFFER_SIZE);
        }catch (IOException e) {
            System.out.println("Exception In ClientPackage.NetworkUtil.Constructor1 "+e.getMessage());
            throw e;
        }
    }


    public NetworkUtil(String address, int port) throws IOException {
        try {
            this.socket = new Socket(address,port);
            this.os=new BufferedOutputStream(socket.getOutputStream());
            this.is=new BufferedInputStream(socket.getInputStream());
        }catch (IOException e) {
            System.out.println("Exception In ClientPackage.NetworkUtil.Constructor2 "+e.getMessage());
            throw e;
        }
    }

    public int readBuff(byte []buff) throws IOException {
        try{
            return is.read(buff);
        } catch (IOException e) {
            System.out.println("Exception In ClientPackage.NetworkUtil.readBuff "+e.getMessage());
            throw e;
        }
    }
    public void writeBuff(byte[]buff,int offset,int length) throws IOException {
        try{
            Random r=new Random();
            os.write(buff,offset,length);
        } catch (IOException e) {
            System.out.println("Exception In ClientPackage.NetworkUtil.writeBuff "+e.getMessage());
            throw e;
        }
    }

    public void flushStream() throws IOException {
        try {
            os.flush();
        } catch (IOException e) {
            System.out.println("Exception In ClientPackage.NetworkUtil.flushStream "+e.getMessage());
            throw e;
        }
    }

    public void writeBuff(byte[]buff) throws IOException {
        try{
            os.write(buff);
            os.flush();
        } catch (IOException e) {
            System.out.println("Exception In ClientPackage.NetworkUtil.writeBuff "+e.getMessage());
            throw e;
        }
    }

    public void closeAll() throws IOException {
        try {
            socket.close();
        } catch (IOException e) {
            System.out.println("Exception In ClientPackage.NetworkUtil.closeAll "+e.getMessage());
            throw e;
        }

    }
    public Socket getSocket()
    {
        return this.socket;
    }

    public void setBUFFER_SIZE(int BUFFER_SIZE) throws IOException {
        this.BUFFER_SIZE = BUFFER_SIZE;
        try {
            this.os=new BufferedOutputStream(socket.getOutputStream(),BUFFER_SIZE);
            this.is=new BufferedInputStream(socket.getInputStream(),BUFFER_SIZE);
        } catch (IOException e) {
            System.out.println("Exception In ClientPackage.NetworkUtil.setBUFFER_SIZE "+e.getMessage());
            throw e;
        }
    }
}
