package main;

import java.net.URL;
import java.util.ArrayList;
import java.util.Date;

/**
 * Created by numan947 on 3/5/17.
 **/
public class Exam {
    private controller_for_the_tabs controllerForTheTabs;
    private Date startTime;
    private int warningTime;
    private int backupInterval;
    private ArrayList<String>allowedIDs;
    private ArrayList<String>listOfCorrections;
    private String examCode;
    private ArrayList<Participant>participants;
    private URL pathToBackupFolder;


    public Exam(controller_for_the_tabs controllerForTheTabs, String examCode) {
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

    public controller_for_the_tabs getControllerForTheTabs() {
        return controllerForTheTabs;
    }

    public void setControllerForTheTabs(controller_for_the_tabs controllerForTheTabs) {
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

    public ArrayList<String> getAllowedIDs() {
        return allowedIDs;
    }

    public void setAllowedIDs(ArrayList<String> allowedIDs) {
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
}
