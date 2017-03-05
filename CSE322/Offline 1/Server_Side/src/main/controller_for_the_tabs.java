package main;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

public class controller_for_the_tabs {

    private String unique_exam_id;

    public void setUnique_exam_id(String unique_exam_id) {
        this.unique_exam_id = unique_exam_id;
        this.exam_id.setText(exam_id.getText()+" "+unique_exam_id);
    }

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
        assert allowed_ids != null : "fx:id=\"allowed_ids\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert correction_list != null : "fx:id=\"correction_list\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert start_time != null : "fx:id=\"start_time\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert warning_time != null : "fx:id=\"warning_time\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert corrections != null : "fx:id=\"corrections\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert exam_name != null : "fx:id=\"exam_name\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert backup_interval != null : "fx:id=\"backup_interval\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert send_corrections != null : "fx:id=\"send_corrections\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";
        assert exam_id != null : "fx:id=\"exam_id\" was not injected: check your FXML file 'server_side_tab_pane.fxml'.";

    }
}
