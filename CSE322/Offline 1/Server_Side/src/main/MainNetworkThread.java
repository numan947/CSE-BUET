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
    private boolean correctionFlag = false;
    private String correctionString=null;
    private  TabController tabController;
    private Participant participant=null;

    Thread t;
    public MainNetworkThread(MainServerThread serverThread, NetworkUtil networkUtil) {
        this.serverThread = serverThread;
        this.networkUtil = networkUtil;
        this.buff=new byte[8192];
        t=new Thread(this);
        t.setDaemon(true);
        t.start();
    }

    public void stopThread(boolean b)
    {
        this.correctionFlag=false;
        try {
            this.networkUtil.closeAll();
            this.t.interrupt();
        } catch (IOException e) {
            e.printStackTrace();
        }
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
                        String examCode = "Exam ID: " + tmp[0];

                        int studentId = Integer.parseInt(tmp[1]);

                        Exam exam=serverThread.getController().getInitiator().getExamMap().get(examCode);

                        File questionFile=exam.getPathToQuestion();

                        //put in the participant table, if the id is not new or the id is registering for new exam,
                        //a client of unique roll number at the same time can't participate in two exams
                        if(!serverThread.getController().getInitiator().
                                getParticipantObjectMap().containsKey(studentId)||
                                !serverThread.getController().getInitiator().
                                        getParticipantObjectMap().get(studentId).
                                        getExamCode().equals(examCode)) {
                            participant = new Participant(networkUtil.getSocket().getInetAddress().getHostAddress(), examCode);
                            participant.setFileTransferThread(new FileTransferThread(null, participant));
                            participant.setBackupInterval(exam.getBackupInterval());
                            serverThread.getController().getInitiator().getParticipantObjectMap().put(studentId, participant);
                            participant.setCurrentBackupFile(questionFile);//as there's no backup received, this is default
                            participant.getCorrectionSent().clear();
                            participant.getCorrectionSent().addAll(tabController.getAllCorrections());
                        }
                        // the id's pc is crashed so, send back the last backup
                        else if(serverThread.getController().getInitiator().
                                getParticipantObjectMap().get(studentId).isCrashed()){
                            //System.out.println("IS IT ME??");
                            participant=serverThread.getController().getInitiator().getParticipantObjectMap().get(studentId);
                            questionFile=participant.getCurrentBackupFile();

                            participant.getCorrectionSent().clear();
                            participant.getCorrectionSent().addAll(tabController.getAllCorrections());
                            //the rest of the participant object should have been set by now
                        }
                        else{
                            // check if the participant is trying to connect after the exam is finished and handle it


                        }


                        //send approval
                        networkUtil.writeBuff("APPROVED".getBytes());
                        networkUtil.flushStream();


                        //read the response msg
                        cnt=networkUtil.readBuff(buff);
                        msg=new String(buff,0,cnt);

                        System.out.println(msg);


                        //create the "Details" string to send
                        String ss=exam.getExamCode().replace("Exam ID: ","");
                        String details=ss+"$$$$"+exam.getExamName()+"$$$$"+exam.getDuration()+"$$$$"+exam.getBackupInterval()+"$$$$"+exam.getWarningTime()+"$$$$"+exam.getStartTime().getTime()+"$$$$"+exam.getRules();


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
                                    details=questionFile.getName()+"$$$$"+questionFile.length();

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

                                        BufferedInputStream fbuff=new BufferedInputStream(new FileInputStream(questionFile));
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


                //send the previous corrections
                for(String cc:participant.getCorrectionSent())
                {
                    if(cc!=null&&!cc.equals("")){
                        networkUtil.writeBuff("Corrections".getBytes());
                        networkUtil.flushStream();
                        cnt=networkUtil.readBuff(buff);
                        if(new String(buff,0,cnt).equals("Send")){
                            networkUtil.writeBuff(cc.getBytes());
                            networkUtil.flushStream();
                        }
                    }
                }

                //send any new corrections
                while (correctionFlag && !Thread.interrupted()){
                    // let there be the code for sending correction
                    if(correctionString!=null&&!correctionString.equals("")){
                        networkUtil.writeBuff("Corrections".getBytes());
                        networkUtil.flushStream();
                        cnt=networkUtil.readBuff(buff);
                        if(new String(buff,0,cnt).equals("Send")){
                            networkUtil.writeBuff(correctionString.getBytes());
                            networkUtil.flushStream();
                            correctionString=null;
                        }
                    }
                }

                networkUtil.closeAll();
            }




        } catch (Exception e) {
            if(e.getMessage().toLowerCase().contains("string index out of range: -1")||
                    e.getMessage().toLowerCase().contains("socket closed")){
                //handle crash
                if(participant!=null) {
                    participant.setCrashed(true);
                    participant.setTimeup(false);
                }
            }


            e.printStackTrace();
        }

    }

    public String getCorrectionString() {
        return correctionString;
    }

    public void setCorrectionString(String correctionString) {
        this.correctionString = correctionString;
    }

    public TabController getTabController() {
        return tabController;
    }

    public void setTabController(TabController tabController) {
        this.tabController = tabController;
    }
}
