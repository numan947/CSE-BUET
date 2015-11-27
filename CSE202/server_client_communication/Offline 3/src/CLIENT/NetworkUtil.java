package CLIENT;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class NetworkUtil
{
	private Socket socket;
	private DataOutputStream oos;
	private DataInputStream ois;

	public NetworkUtil(String s, int port) {
		try {
			this.socket=new Socket(s,port);  
			oos=new DataOutputStream(socket.getOutputStream());
			ois=new DataInputStream(socket.getInputStream());
		} catch (Exception e) {
			System.out.println("In NetworkUtil : " + e.toString());
		}
	}

	public NetworkUtil(Socket s) {
		try {
			this.socket = s;
			oos=new DataOutputStream(socket.getOutputStream());
			ois=new DataInputStream(socket.getInputStream());
		} catch (Exception e) {
			System.out.println("In NetworkUtil : " + e.toString());
		}
	}

	public Object read() {
		String o = null;
		try {
			o=ois.readUTF();
		} catch (Exception e) {
		  System.out.println("Reading Error in network : " + e.toString());
		}
		return o;
	}
	
	public void write(String o) {
		try {
			oos.writeUTF(o);
		} catch (IOException e) {
			System.out.println("Writing  Error in network : " + e.toString());
		}
	}

	public void closeConnection() {
		try {
			ois.close();
			oos.close();
		} catch (Exception e) {
			System.out.println("Closing Error in network : "  + e.toString());
		}
	}

	public Socket getSocket() {
		return this.socket;
	}
}

