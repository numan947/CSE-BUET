package geass;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.stage.FileChooser;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class mediaListController {

    @FXML
    private Button addButton;

    @FXML
    private Button deleteButton;

    @FXML
    private ListView<?> mediaList;

    @FXML
    void addMedia(ActionEvent event) {
        System.out.println("HELLO WORLD");
        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("AudioFiles","*.mp3"));
        Stage stage=new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);


        fc.showOpenDialog(stage);

    }




}
