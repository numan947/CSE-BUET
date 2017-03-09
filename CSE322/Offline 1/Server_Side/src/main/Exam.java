package main;

import java.net.URL;
import java.util.ArrayList;
import java.util.Date;

/**
 * Created by numan947 on 3/5/17.
 **/
public class Exam {
    private String examName;
    private TabController controllerForTheTabs;
    private Date startTime;
    private int warningTime;
    private int backupInterval;
    private int duration;

    public int getDuration() {
        return duration;
    }

    public void setDuration(int duration) {
        this.duration = duration;
    }

    private ArrayList<Integer>allowedIDs;
    private ArrayList<String>listOfCorrections;
    private String examCode;
    private ArrayList<Participant>participants;
    private URL pathToBackupFolder;
    private URL pathToQuestion;


    public Exam(TabController controllerForTheTabs, String examCode) {
        this.controllerForTheTabs = controllerForTheTabs;
        this.examCode = examCode;
        this.allowedIDs=new ArrayList<>();
        this.listOfCorrections=new ArrayList<>();
        this.participants=new ArrayList<>();
    }




    public ArrayList<Participant> getParticipants() {
        return participants;
    }

    public void setParticipants(ArrayList<Participant> participants) {
        this.participants = participants;
    }

    public URL getPathToBackupFolder() {
        return pathToBackupFolder;
    }

    public void setPathToBackupFolder(URL pathToBackupFolder) {
        this.pathToBackupFolder = pathToBackupFolder;
    }

    public TabController getControllerForTheTabs() {
        return controllerForTheTabs;
    }

    public void setControllerForTheTabs(TabController controllerForTheTabs) {
        this.controllerForTheTabs = controllerForTheTabs;
    }

    public Date getStartTime() {
        return startTime;
    }

    public void setStartTime(Date startTime) {
        this.startTime = startTime;
    }

    public int getWarningTime() {
        return warningTime;
    }

    public void setWarningTime(int warningTime) {
        this.warningTime = warningTime;
    }

    public int getBackupInterval() {
        return backupInterval;
    }

    public void setBackupInterval(int backupInterval) {
        this.backupInterval = backupInterval;
    }

    public ArrayList<Integer> getAllowedIDs() {
        return allowedIDs;
    }

    public void setAllowedIDs(ArrayList<Integer> allowedIDs) {
        this.allowedIDs = allowedIDs;
    }

    public ArrayList<String> getListOfCorrections() {
        return listOfCorrections;
    }

    public void setListOfCorrections(ArrayList<String> listOfCorrections) {
        this.listOfCorrections = listOfCorrections;
    }

    public String getExamCode() {
        return examCode;
    }

    public void setExamCode(String examCode) {
        this.examCode = examCode;
    }

    public URL getPathToQuestion() {
        return pathToQuestion;
    }

    public void setPathToQuestion(URL pathToQuestion) {
        this.pathToQuestion = pathToQuestion;
    }

    public String getExamName() {
        return examName;
    }

    public void setExamName(String examName) {
        this.examName = examName;
    }
}
