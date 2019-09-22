package SERVER;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class ServerApp extends Application {

    @Override
    public void start(Stage primaryStage){
        FXMLLoader serverLoader = new FXMLLoader(getClass().getResource("SERVER2.fxml"));
        Parent root = null;
        try {
            root = serverLoader.load();
        } catch (IOException e) {
            System.out.println("problem in loading scene "+e);
        }
        ServerThread control=serverLoader.getController();
        control.SETPORT(12345);
        control.initializeColumns();
        control.RUN();

        primaryStage.setTitle("SERVER MAIN");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
