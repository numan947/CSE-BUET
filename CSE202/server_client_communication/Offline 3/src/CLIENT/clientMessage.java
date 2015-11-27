package CLIENT;
/**
 * Created by numan947 on 2015-11-21.
 */

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;

public class clientMessage {

    ClientApp main;
    String Message;
    NetworkUtil util;
    @FXML
    private TextArea messagefield;

    @FXML
    private Button closeButton;

    @FXML
    void closeMessage(ActionEvent event) {
        util.closeConnection();
        main.myStage.close();
    }

    void setMain(ClientApp main)
    {
        this.main=main;
    }
    void setMessage(String p)
    {
        this.Message=p;
        messagefield.appendText(p);
        messagefield.setEditable(false);
    }
    void setUtil(NetworkUtil util)
    {
        this.util=util;
    }

}

