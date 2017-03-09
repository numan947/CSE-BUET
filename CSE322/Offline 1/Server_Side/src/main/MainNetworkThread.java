package main;

import java.io.IOException;

/**
 * Created by numan947 on 3/9/17.
 **/
public class MainNetworkThread implements Runnable {
    private MainServerThread serverThread;
    private NetworkUtil networkUtil;
    private byte[]buff=null;
    private String examCode;
    private int studentId;

    public MainNetworkThread(MainServerThread serverThread, NetworkUtil networkUtil) {
        this.serverThread = serverThread;
        this.networkUtil = networkUtil;
        this.buff=new byte[8192];
        Thread t=new Thread(this);
        t.setDaemon(true);
        t.start();
    }


    @Override
    public void run() {
        int cnt;
        String msg;

        try {
            cnt=networkUtil.readBuff(buff);
            msg=new String(buff,0,cnt);

            //the msg should contain examCode and StudentId, separated by $$$$
            String[]tmp=msg.split("\\$\\$\\$\\$");
            if(tmp.length==2){
                //check if the exam code is in the exam map
                if(serverThread.getController().getInitiator().getExamMap().containsKey(tmp[0])){
                    //check if the student id is in the exam object
                    if(serverThread.getController().getInitiator().getExamMap().get(tmp[0]).getAllowedIDs().contains(Integer.parseInt(tmp[1]))){
                        //send approval
                        examCode=tmp[0];
                        studentId= Integer.parseInt(tmp[1]);
                        Exam exam=serverThread.getController().getInitiator().getExamMap().get(examCode);
                        networkUtil.writeBuff("APPROVED".getBytes());



                        //read the response msg
                        cnt=networkUtil.readBuff(buff);
                        msg=new String(buff,0,cnt);

                        //create the "Details" string to send
                        String details=exam.getExamCode()+"$$$$"+exam.getExamName()+"$$$$"+exam.getDuration()+"$$$$"+exam.getBackupInterval()+"$$$$"+exam.getWarningTime()+"$$$$"+exam.getStartTime().getTime();


                        if(msg.equals("REQUESTING_SIZE_OF_DETAILS_STRING")){
                            //send the details size
                            networkUtil.writeBuff(String.valueOf(details.length()).getBytes());

                            //wait for SIZE_RECEIVED msg
                            cnt=networkUtil.readBuff(buff);
                            msg=new String(buff,0,cnt);
                            if(msg.equals("SIZE_RECEIVED")){
                                //send the actual details now
                                networkUtil.writeBuff(details.getBytes());

                                //wait for the response

                            }
                        }






                    }
                }
















            }




















        } catch (IOException e) {
            e.printStackTrace();
        }


    }
}
