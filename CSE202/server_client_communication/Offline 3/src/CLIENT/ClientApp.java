package CLIENT;
/**
 * Created by numan947 on 2015-11-21.
 */

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;



public class ClientApp extends Application {
    Stage myStage;
    public String msg;
    String userName;

    @Override
    public void start(Stage primaryStage) throws Exception {
        myStage=primaryStage;
        loginPage();
    }

    public void loginPage() throws Exception {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("clientLogin.fxml"));
        Parent root = loader.load();


        ClientLogin control=loader.getController();
        control.setMain(this);


        myStage.setTitle("Client");
        myStage.setScene(new Scene(root,550,250));
        myStage.show();
    }

    public void showMessage() throws Exception {
        FXMLLoader loader=new FXMLLoader();
        loader.setLocation(getClass().getResource("messageFromServer.fxml"));
        Parent root=loader.load();

        clientMessage control=loader.getController();
        control.setMain(this);
        NetworkUtil util;
        util=new NetworkUtil("localhost",12345);
        util.write(userName);
        control.setUtil(util);
        new CommunicationThread(control,util);

        myStage.setTitle("From Server with Love: "+userName);
        myStage.setScene(new Scene(root,600,380));
        myStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

}
