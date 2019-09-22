package CLIENT;

/**
 * Created by numan947 on 2015-11-21.
 */

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

public class ClientLogin {
    private ClientApp main;

    @FXML
    private TextField ClientName;

    @FXML

    private Button connect;

    @FXML
    private Button Reset;

    @FXML
    void LoginAction(ActionEvent event) {
        main.userName=ClientName.getText();

        try {
            main.showMessage();
        } catch (Exception e) {
            System.out.println("exception at CLIENTLOGIN/ LOGINACTION, can't open COMMUNICATION THREAD");
        }
    }

    @FXML
    void ResetAction(ActionEvent event) {
        ClientName.clear();
    }

    void setMain(ClientApp main) {
        this.main = main;
    }
}