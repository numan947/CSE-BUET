package main;

/**
 * Sample Skeleton for 'client_side_gui.fxml' Controller Class
 */

import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

public class client_main_gui_controller {

    @FXML // ResourceBundle that was given to the FXMLLoader
    private ResourceBundle resources;

    @FXML // URL location of the FXML file that was given to the FXMLLoader
    private URL location;

    @FXML // fx:id="duration"
    private Label duration; // Value injected by FXMLLoader

    @FXML // fx:id="correction_list"
    private ListView<?> correction_list; // Value injected by FXMLLoader

    @FXML // fx:id="start_time"
    private Label start_time; // Value injected by FXMLLoader

    @FXML // fx:id="rules_and_regulations"
    private TextArea rules_and_regulations; // Value injected by FXMLLoader

    @FXML // fx:id="server_ip_address"
    private TextField server_ip_address; // Value injected by FXMLLoader

    @FXML // fx:id="port_number"
    private TextField port_number; // Value injected by FXMLLoader

    @FXML // fx:id="exam_name"
    private Label exam_name; // Value injected by FXMLLoader

    @FXML // fx:id="backup_interval"
    private Label backup_interval; // Value injected by FXMLLoader

    @FXML // fx:id="connect"
    private Button connect; // Value injected by FXMLLoader

    @FXML // fx:id="status"
    private Label status; // Value injected by FXMLLoader

    @FXML
    void connect(ActionEvent event) {

    }

    @FXML
    void ee1c09(ActionEvent event) {

    }

    @FXML // This method is called by the FXMLLoader when initialization is complete
    void initialize() {
        assert duration != null : "fx:id=\"duration\" was not injected: check your FXML file 'client_side_gui.fxml'.";
        assert correction_list != null : "fx:id=\"correction_list\" was not injected: check your FXML file 'client_side_gui.fxml'.";
        assert start_time != null : "fx:id=\"start_time\" was not injected: check your FXML file 'client_side_gui.fxml'.";
        assert rules_and_regulations != null : "fx:id=\"rules_and_regulations\" was not injected: check your FXML file 'client_side_gui.fxml'.";
        assert server_ip_address != null : "fx:id=\"server_ip_address\" was not injected: check your FXML file 'client_side_gui.fxml'.";
        assert port_number != null : "fx:id=\"port_number\" was not injected: check your FXML file 'client_side_gui.fxml'.";
        assert exam_name != null : "fx:id=\"exam_name\" was not injected: check your FXML file 'client_side_gui.fxml'.";
        assert backup_interval != null : "fx:id=\"backup_interval\" was not injected: check your FXML file 'client_side_gui.fxml'.";
        assert connect != null : "fx:id=\"connect\" was not injected: check your FXML file 'client_side_gui.fxml'.";
        assert status != null : "fx:id=\"status\" was not injected: check your FXML file 'client_side_gui.fxml'.";

    }
}
