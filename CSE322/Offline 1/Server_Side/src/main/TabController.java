package main;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URISyntaxException;
import java.net.URL;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.stage.DirectoryChooser;
import javafx.stage.FileChooser;

public class TabController {


    private String unique_exam_id;
    private Server_GUI_Controller controller;
    private URL backUpStoragePath;
    private URL questionStoragePath;

    public void setUnique_exam_id(String unique_exam_id) {
        this.unique_exam_id = unique_exam_id;
        this.exam_id.setText(exam_id.getText()+" "+unique_exam_id);
    }

    @FXML
    private TextField exam_duration;

    @FXML
    private Button back_up_storage_path;

    @FXML
    public Button add_to_exam_list;

    @FXML
    public Button remove_from_exam_list;

    
    @FXML
    private Button question_paper_path;

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private TextField allowed_ids;

    @FXML
    private ListView<?> correction_list;

    @FXML
    private TextField start_time;

    @FXML
    private TextField warning_time;

    @FXML
    private TextArea corrections;

    @FXML
    private TextField exam_name;

    @FXML
    private TextField backup_interval;

    @FXML
    private Button send_corrections;

    @FXML
    private Label exam_id;

    @FXML
    void sendCorrections(ActionEvent event) {

    }

    @FXML
    void initialize() {
        assert question_paper_path != null : "fx:id=\"question_paper_path\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert warning_time != null : "fx:id=\"warning_time\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert add_to_exam_list != null : "fx:id=\"add_to_exam_list\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert back_up_storage_path != null : "fx:id=\"back_up_storage_path\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert allowed_ids != null : "fx:id=\"allowed_ids\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert correction_list != null : "fx:id=\"correction_list\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert start_time != null : "fx:id=\"start_time\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert corrections != null : "fx:id=\"corrections\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert exam_duration != null : "fx:id=\"exam_duration\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert remove_from_exam_list != null : "fx:id=\"remove_from_exam_list\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert exam_name != null : "fx:id=\"exam_name\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert backup_interval != null : "fx:id=\"backup_interval\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert send_corrections != null : "fx:id=\"send_corrections\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert exam_id != null : "fx:id=\"exam_id\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";

    }

    public void addToExamList(ActionEvent actionEvent) {
        //this adds the exam to the examlist in the ServerSide class
        String examName= exam_name.getText();
        String startTime=start_time.getText();
        DateFormat format=new SimpleDateFormat("dd-MM-yyyy hh:mm aa");
        Date dd=null;
        try {
            dd=format.parse(startTime);
        } catch (ParseException e) {
            //todo show error
            e.printStackTrace();
        }
        int warning=Integer.parseInt(warning_time.getText())*1000; //milliseconds before warning
        int backupInterval=Integer.parseInt(backup_interval.getText())*1000;//milliseconds
        int duration=Integer.parseInt(exam_duration.getText());// minutes


        String idlist=allowed_ids.getText();
        ArrayList<Integer>allowedId=new ArrayList();
        if(idlist.contains("-")){
            String[]tmp=idlist.split("-");
            int a= Integer.parseInt(tmp[0]);
            int b=Integer.parseInt(tmp[1]);
            for(int i=a;i<=b;i++)allowedId.add(i);
        }
        else if(idlist.contains(",")){
            String[]tmp=idlist.split(",");
            for(String s:tmp)allowedId.add(Integer.parseInt(s));
        }

        // setting up the exam fields
        Exam exam=new Exam(this,exam_id.getText());
        exam.setAllowedIDs(allowedId);
        exam.setWarningTime(warning);
        exam.setBackupInterval(backupInterval);
        exam.setPathToBackupFolder(backUpStoragePath);
        exam.setPathToQuestion(questionStoragePath);
        exam.setStartTime(dd);
        exam.setExamName(examName);
        exam.setDuration(duration);

        //adding to exam_list
        controller.getInitiator().getExamMap().put(exam_id.getText(),exam);
    }

    public void removeFromExamList(ActionEvent actionEvent) {
        //todo do later
    }

    public void setBackUpStoragePath(ActionEvent actionEvent) {
        DirectoryChooser directoryChooser=new DirectoryChooser();

        try {
            directoryChooser.setInitialDirectory(new File(getClass().getProtectionDomain().getCodeSource().getLocation().toURI().getPath()));
            File ff=directoryChooser.showDialog(controller.getInitiator().getMainStage());
            backUpStoragePath=ff.toURI().toURL();
        } catch (URISyntaxException | MalformedURLException e) {
            e.printStackTrace();
        }
    }

    public void setQuestionPaperPath(ActionEvent actionEvent) {
        FileChooser filechooser=new FileChooser();

        try {
            filechooser.setInitialDirectory(new File(getClass().getProtectionDomain().getCodeSource().getLocation().toURI().getPath()));
            File ff=filechooser.showOpenDialog(controller.getInitiator().getMainStage());
            questionStoragePath=ff.toURI().toURL();
        } catch (URISyntaxException | MalformedURLException e) {
            e.printStackTrace();
        }


    }

    public void setController(Server_GUI_Controller controller) {
        this.controller = controller;
    }
}
