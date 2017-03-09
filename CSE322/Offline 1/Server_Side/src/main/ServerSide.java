package main;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.Hashtable;

/**
 * Created by numan947 on 3/5/17.
 **/
public class ServerSide extends Application {
    //these are some maps and lists that'll be singleton in the whole project
    private ArrayList<String>examList;
    private Hashtable<String,ArrayList<String>>exam_Participant_Map;
    private Hashtable<Integer, Participant> participantObjectMap;
    private Hashtable <String,Exam> examMap;
    private Stage mainStage;





    @Override
    public void start(Stage primaryStage) throws Exception {
        //initialization
        exam_Participant_Map=new Hashtable<>();
        examList=new ArrayList<>();
        participantObjectMap=new Hashtable<Integer, Participant>();
        examMap =new Hashtable<>();


        //setting up the primary gui
        FXMLLoader fxmlLoader=new FXMLLoader(getClass().getResource("/res/server_side_gui_main.fxml"));
        Parent root = fxmlLoader.load();
        ((Server_GUI_Controller)fxmlLoader.getController()).setInitiator(this);



        primaryStage.setTitle("OWOWOWOWWOWOWOWOW");
        primaryStage.setScene(new Scene(root, 900, 600));
        primaryStage.show();
        mainStage=primaryStage;
    }

    public static void main(String[] args) {
        launch(args);
    }


    public ArrayList<String> getExamList() {
        return examList;
    }

    public Hashtable<String, ArrayList<String>> getExam_Participant_Map() {
        return exam_Participant_Map;
    }

    public Hashtable<Integer, Participant> getParticipantObjectMap() {
        return participantObjectMap;
    }

    public Hashtable<String, Exam> getExamMap() {
        return examMap;
    }

    public Stage getMainStage() {
        return mainStage;
    }
}
