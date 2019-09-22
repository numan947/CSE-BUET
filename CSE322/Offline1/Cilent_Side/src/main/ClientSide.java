package main;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * Created by numan947 on 3/5/17.
 **/
public class ClientSide extends Application {
    private Stage mainStage;

    @Override
    public void start(Stage primaryStage) throws Exception{

        FXMLLoader loader=new FXMLLoader(getClass().getResource("/res/client_side_gui.fxml"));


        Parent root = loader.load();

        ((Client_GUI_Controller)loader.getController()).setInitiator(this);

        primaryStage.setTitle("Not Your Regular Hello World");
        primaryStage.setScene(new Scene(root, 600, 600));
        primaryStage.show();
        mainStage=primaryStage;
    }


    public static void main(String[] args) {
        launch(args);
    }

    public Stage getMainStage() {
        return mainStage;
    }
}
