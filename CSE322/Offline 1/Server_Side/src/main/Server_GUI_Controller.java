package main;
/**
 * Sample Skeleton for 'server_side_gui_main.fxml' Controller Class
 */

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Priority;

import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class Server_GUI_Controller {
    // general fields
    public static long backupepstime=5000;
    private String server_default_status="not started";
    private FXMLLoader fxmlLoader=null;
    private ServerSide initiator;
    private MainServerThread mainServerThread=null;
    private BackupCheckerThread backupCheckerThread=null;
    private Alert alert=null;

    public void setInitiator(ServerSide initiator) {
        this.initiator = initiator;
    }

    public synchronized ServerSide getInitiator() {
        return initiator;
    }

    @FXML // ResourceBundle that was given to the FXMLLoader
    private ResourceBundle resources;

    @FXML // URL location of the FXML file that was given to the FXMLLoader
    private URL location;

    @FXML // fx:id="start_server"
    private Button start_server; // Value injected by FXMLLoader

    @FXML // fx:id="port_number"
    private TextField port_number; // Value injected by FXMLLoader

    @FXML // fx:id="exam_list"
    private TabPane exam_list; // Value injected by FXMLLoader

    @FXML // fx:id="ip_address"
    private TextField ip_address; // Value injected by FXMLLoader

    @FXML // fx:id="exam_name"
    private TextField exam_id; // Value injected by FXMLLoader

    @FXML // fx:id="create_exam"
    private Button create_exam; // Value injected by FXMLLoader

    @FXML // fx:id="status"
    private Label status; // Value injected by FXMLLoader

    @FXML
    void start_server_action(ActionEvent event) {
        if(status.getText().equals("status: not started")||status.getText().equals("status: stopped")){
            //server start code here
            if(mainServerThread==null){
                try {
                    this.mainServerThread=new MainServerThread(this, ip_address.getText(),Integer.parseInt(port_number.getText()));

                    //initiate the backup checker thread
                    this.backupCheckerThread=new BackupCheckerThread(initiator.getParticipantObjectMap(),this);
                    status.setText("status: running");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            else{
                this.mainServerThread.setStopServer(false);
                this.backupCheckerThread=new BackupCheckerThread(initiator.getParticipantObjectMap(),this);
                status.setText("status: running");
            }
            start_server.setText("Stop Server");
        }else{
            //server stop code here
            if(mainServerThread!=null)mainServerThread.setStopServer(true);
            if(backupCheckerThread!=null)backupCheckerThread.setRunning(false);
            status.setText("status: stopped");
            start_server.setText("Start Server");
        }
    }

    @FXML
    void create_exam_action(ActionEvent event) {
        // code for the button create exam
        if(!exam_id.getText().equals(""))
            try {
                // reuse fxmlLoader
                fxmlLoader.setRoot(null);
                fxmlLoader.setController(null);


                fxmlLoader.setLocation(getClass().getResource("/res/server_side_tab_pane.fxml"));
                Parent pp=fxmlLoader.load();
                TabController tabController=fxmlLoader.getController();


                //get-set the exam_
                tabController.setUnique_exam_id(this.exam_id.getText());
                tabController.setController(this);
                this.exam_id.clear();


                Tab t=new Tab("WHY",pp);
                t.setClosable(true);

                exam_list.getTabs().add(t);
            } catch (IOException e) {
                e.printStackTrace();
            }

    }

    @FXML // This method is called by the FXMLLoader when initialization is complete
    void initialize() {
        // initiate general resource

        fxmlLoader=new FXMLLoader();
        exam_list.setTabClosingPolicy(TabPane.TabClosingPolicy.SELECTED_TAB);
        assert start_server != null : "fx:id=\"start_server\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert port_number != null : "fx:id=\"port_number\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert exam_list != null : "fx:id=\"exam_list\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert ip_address != null : "fx:id=\"ip_address\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert exam_id != null : "fx:id=\"exam_id\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert create_exam != null : "fx:id=\"create_exam\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert status != null : "fx:id=\"status\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";


        this.status.setText(this.status.getText()+" "+server_default_status);
        alert=new Alert(Alert.AlertType.ERROR);
    }


    public void showErrorDialog(String ss)
    {
        Platform.runLater(() -> {
            alert.setAlertType(Alert.AlertType.ERROR);
            alert.setTitle("ERROR!!");
            alert.setHeaderText("There's an error while connecting");
            alert.setContentText(ss);
            alert.showAndWait();

            //this.clearConnectButton();
        });

    }

    public void showErrorDialog(ArrayList<Integer> integers) {

        Platform.runLater(() -> {
            alert.setAlertType(Alert.AlertType.WARNING);
            alert.setTitle("Warning!!");

            Label label=new Label("NO BACK UP RECEIVED!!");

            TextArea textArea = new TextArea("The Server didn't receive any backup for the following studentIDs: "+integers.toString());
            textArea.setEditable(false);
            textArea.setWrapText(true);
            textArea.setMaxWidth(Double.MAX_VALUE);
            textArea.setMaxHeight(Double.MAX_VALUE);
            GridPane.setVgrow(textArea, Priority.ALWAYS);
            GridPane.setHgrow(textArea, Priority.ALWAYS);

            GridPane expContent = new GridPane();
            expContent.setMaxWidth(Double.MAX_VALUE);
            expContent.add(label, 0, 0);
            expContent.add(textArea, 0, 1);


            alert.getDialogPane().setExpandableContent(expContent);
            alert.getDialogPane().setExpanded(true);

            alert.showAndWait();
            //this.clearConnectButton();
        });

    }
}
