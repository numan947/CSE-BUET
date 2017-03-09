package main;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.URISyntaxException;

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


    private int getBuff(byte[]buff, BufferedInputStream fbuff)
    {
        try {
            return fbuff.read(buff);
        } catch (IOException e) {
            System.out.println("Exception In ClientPackage.Client.getBuff "+e.getMessage());
        }
        return 0;
    }

    @Override
    public void run() {
        int cnt;
        String msg;
        boolean correctionFlag = false;

        try {
            cnt=networkUtil.readBuff(buff);

            msg=new String(buff,0,cnt);

            //the msg should contain examCode and StudentId, separated by $$$$
            System.out.println(msg);


            String[]tmp=msg.split("\\$\\$\\$\\$");

            if(tmp.length==2){

                //check if the exam code is in the exam map
                System.out.println("AM I STUCK HERE??1 + "+tmp[0]);
                if(serverThread.getController().getInitiator().getExamMap().containsKey("Exam ID: "+tmp[0])){

                    //check if the student id is in the exam object
                    System.out.println("AM I STUCK HERE??2");
                    if(serverThread.getController().getInitiator().getExamMap().get("Exam ID: "+tmp[0]).getAllowedIDs().contains(Integer.parseInt(tmp[1]))){

                        //save the info
                        examCode="Exam ID: "+tmp[0];

                        studentId= Integer.parseInt(tmp[1]);

                        Exam exam=serverThread.getController().getInitiator().getExamMap().get(examCode);


                        //put in the participant table
                        Participant participant=new Participant(networkUtil.getSocket().getInetAddress().getHostAddress(),examCode);
                        serverThread.getController().getInitiator().getParticipantObjectMap().put(studentId,participant);



                        //send approval
                        networkUtil.writeBuff("APPROVED".getBytes());
                        networkUtil.flushStream();


                        //read the response msg
                        cnt=networkUtil.readBuff(buff);
                        msg=new String(buff,0,cnt);

                        System.out.println(msg);


                        //create the "Details" string to send
                        String details=exam.getExamCode()+"$$$$"+exam.getExamName()+"$$$$"+exam.getDuration()+"$$$$"+exam.getBackupInterval()+"$$$$"+exam.getWarningTime()+"$$$$"+exam.getStartTime().getTime();


                        if(msg.equals("REQUESTING_SIZE_OF_DETAILS_STRING")){
                            //send the details size
                            networkUtil.writeBuff(String.valueOf(details.length()).getBytes());
                            networkUtil.flushStream();


                            //wait for SIZE_RECEIVED msg
                            cnt=networkUtil.readBuff(buff);
                            msg=new String(buff,0,cnt);

                            System.out.println(msg);


                            if(msg.equals("SIZE_RECEIVED")){
                                //send the actual details now
                                System.out.println(details);
                                networkUtil.writeBuff(details.getBytes());
                                networkUtil.flushStream();


                                //wait for the response: DATA_RECEIVED
                                cnt=networkUtil.readBuff(buff);
                                msg=new String(buff,0,cnt);

                                System.out.println(msg);

                                if(msg.equals("DATA_RECEIVED")){
                                    //now we wait for appropriate time to send the question to the sender
                                    long diff=exam.getStartTime().getTime()-System.currentTimeMillis();

                                    //prepare the filename and filesize to send
                                    File file=new File(exam.getPathToQuestion().toURI());
                                    details=file.getName()+"$$$$"+file.length();

                                    //create folder for the participant
                                    File folderForParticipant=new File(new File(exam.getPathToBackupFolder().toURI()),String.valueOf(studentId));
                                    participant.setBackupStoragePath(folderForParticipant);

                                    if(diff>0)Thread.sleep(diff-30);


                                    //start communication
                                    networkUtil.writeBuff(details.getBytes());
                                    networkUtil.flushStream();


                                    cnt=networkUtil.readBuff(buff);
                                    msg=new String(buff,0,cnt);

                                    System.out.println(msg);


                                    if(msg.equals("SEND_QUESTION")){

                                        BufferedInputStream fbuff=new BufferedInputStream(new FileInputStream(file));
                                        int tmpCt=0;
                                        int totalRead=0;
                                        while ((totalRead = getBuff(buff,fbuff)) > -1) {
                                            tmpCt+=totalRead;
                                            networkUtil.writeBuff(buff, 0, totalRead);
                                            if(tmpCt>=8192){
                                                networkUtil.flushStream();
                                                tmpCt=0;
                                            }

                                        }
                                        networkUtil.flushStream();
                                        fbuff.close();


                                        //read the response: QUESTION_RECEIVED
                                        cnt=networkUtil.readBuff(buff);
                                        msg=new String(buff,0,cnt);

                                        System.out.println(msg);


                                        if(msg.equals("QUESTION_RECEIVED"))correctionFlag=true;

                                        // now we go to correction flag to wait for corrections :)
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

        while (correctionFlag){




        }


    }
}
