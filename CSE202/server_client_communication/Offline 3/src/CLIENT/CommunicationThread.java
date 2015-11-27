package CLIENT;

/**
 * Created by numan947 on 2015-11-21.
 */
public class CommunicationThread implements Runnable{
    Thread t;
    NetworkUtil util;
    clientMessage main;
    CommunicationThread(clientMessage main, NetworkUtil util){
        this.main=main;
        this.util=util;
        t=new Thread(this);
        t.start();
    }
    
    @Override
    public void run() {
        String in = null;
        try {
            while(true) {
                in= (String) util.read();
                System.out.println("in dis comThread" + in);
                main.setMessage(in);
            }
        } catch (Exception e) {
           // e.printStackTrace();
           System.out.println("exception at COMMUNICATIONTHREAD/RUN(), problem at INPUTSTREAM "+e);
        }

    }
}
