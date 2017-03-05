package main;
/**
 * Sample Skeleton for 'server_side_gui_main.fxml' Controller Class
 */

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.*;

public class server_gui_controller {

    // general fields
    private FXMLLoader fxmlLoader=null;





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

    }

    @FXML
    void create_exam_action(ActionEvent event) {
        try {
            // reuse fxmlLoader
            fxmlLoader.setRoot(null);
            fxmlLoader.setController(null);

            fxmlLoader.setLocation(getClass().getResource("/res/server_side_tab_pane.fxml"));
            Parent pp=fxmlLoader.load();
            controller_for_the_tabs tabController=fxmlLoader.getController();

            //get-set the exam_
            tabController.setUnique_exam_id(this.exam_id.getText());
            this.exam_id.clear();


            Tab t=new Tab("WHY",pp);
            exam_list.getTabs().add(t);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    @FXML // This method is called by the FXMLLoader when initialization is complete
    void initialize() {
        // initiate general resource
        fxmlLoader=new FXMLLoader();

        assert start_server != null : "fx:id=\"start_server\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert port_number != null : "fx:id=\"port_number\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert exam_list != null : "fx:id=\"exam_list\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert ip_address != null : "fx:id=\"ip_address\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert exam_id != null : "fx:id=\"exam_id\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert create_exam != null : "fx:id=\"create_exam\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";
        assert status != null : "fx:id=\"status\" was not injected: check your FXML file 'server_side_gui_main.fxml'.";

    }
}
