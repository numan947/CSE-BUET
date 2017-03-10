package main;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
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


    private int getBuffFromFile(byte[]buff, BufferedInputStream fbuff)
    {
        try {
            return fbuff.read(buff);
        } catch (IOException e) {
            System.out.println("Exception In ClientPackage.Client.getBuffFromFile "+e.getMessage());
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
                        participant.setFileTransferThread(new FileTransferThread(null,participant));
                        participant.setBackupInterval(exam.getBackupInterval());
                        serverThread.getController().getInitiator().getParticipantObjectMap().put(studentId,participant);



                        //send approval
                        networkUtil.writeBuff("APPROVED".getBytes());
                        networkUtil.flushStream();


                        //read the response msg
                        cnt=networkUtil.readBuff(buff);
                        msg=new String(buff,0,cnt);

                        System.out.println(msg);


                        //create the "Details" string to send
                        String ss=exam.getExamCode().replace("Exam ID: ","");
                        String details=ss+"$$$$"+exam.getExamName()+"$$$$"+exam.getDuration()+"$$$$"+exam.getBackupInterval()+"$$$$"+exam.getWarningTime()+"$$$$"+exam.getStartTime().getTime();


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
                                    //prepare the fileName and fileSize to send

                                    File file=exam.getPathToQuestion();
                                    participant.setCurrentBackupFile(file);//as there's no backup received, this is default
                                    details=file.getName()+"$$$$"+file.length();

                                    //create folder for the participant
                                    File folderForParticipant=new File(exam.getPathToBackupFolder(),String.valueOf(studentId));
                                    participant.setBackupStoragePath(folderForParticipant);


                                    //now we wait for appropriate time to send the question to the sender
                                    long diff=exam.getStartTime().getTime()-System.currentTimeMillis();
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
                                        while ((totalRead = getBuffFromFile(buff,fbuff)) > -1) {
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

                                        networkUtil.writeBuff("INITIATE_FILE_TRANSFER_THREAD".getBytes());
                                        participant.setNextScheduledBackup(System.currentTimeMillis()+participant.getBackupInterval()+Server_GUI_Controller.backupepstime);

                                        // now we go to correction flag to wait for corrections :)
                                    }
                                }
                            }
                        }
                    }else{
                        //send error for the studentID of the examID
                        networkUtil.writeBuff("NO_SUCH_ROLL_NUMBER_FOR_THE_GIVEN_EXAM_CODE".getBytes());
                        networkUtil.flushStream();
                    }
                }
                else{
                    //send error for the examID
                    networkUtil.writeBuff("NO_SUCH_EXAM_CODE".getBytes());
                    networkUtil.flushStream();
                }
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

        while (correctionFlag){
            // let there be the code for sending correction


        }

        try {
            networkUtil.closeAll();
        } catch (IOException ignore) {
            /*igonre*/
        }


    }
}
