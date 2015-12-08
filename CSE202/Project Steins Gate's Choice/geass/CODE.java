package geass;/**
 * Created by numan947 on 2015-12-03.
 */

import javafx.application.Application;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.nio.file.Paths;

public class CODE extends Application {
    //Variables in Main Application Class
    MediaModel model;
    Stage stage;
    StringProperty mediaName=new SimpleStringProperty();

    //loaders and parents
    FXMLLoader loader1,loader2,loader3;
    Parent root1,root2,root3;

    //playlist Scene
    Scene playlistScene;

    //Main
    public static void main(String[] args) {
        launch(args);
    }

    //Start of start()
    @Override
    public void start(Stage primaryStage) throws IOException {
        //layouts
        stage=primaryStage;
        BorderPane bp=new BorderPane();
        HBox hbox=new HBox();


        //mediaNaming
        mediaName.setValue("Makise Kurisu Player :)");


        //default Media
        model=new MediaModel();



        //loading fxml3
        loader3=new FXMLLoader(getClass().getResource("mediaList.fxml"));
        root3=loader3.load();
        mediaListController control3=loader3.getController();


        //loading fxml1
        loader1=new FXMLLoader(getClass().getResource("PlayerControls.fxml"));
        root1=loader1.load();
        PanelController control1=loader1.getController();

        //loading fxml2
        loader2=new FXMLLoader(getClass().getResource("MetaData.fxml"));
        root2=loader2.load();
        MetaDataController control2=loader2.getController();




        //controlling the fxmls
        control3.setMain(this);
        control3.INITIALIZE();
        control3.setPanel(control1);

        control2.INITIALIZE(model);

        control1.INITVIEW(model);
        control1.DISABLEALL();
        control1.setMain(this);
        control1.setMediaList(control3);

        playlistScene=new Scene(root3,213,397);

        //PrimaryStage configurations
        hbox.getChildren().add(root1);
        hbox.getChildren().add(root2);
        hbox.setAlignment(Pos.BASELINE_RIGHT);
        HBox.setHgrow(root1, Priority.ALWAYS);
        HBox.setHgrow(root2,Priority.NEVER);

        //BorderPane settings
        bp.setBottom(hbox);

        //primaryStage settings
        primaryStage.titleProperty().bind(mediaName);
        primaryStage.setScene(new Scene(bp,1000,700));
        primaryStage.show();
    }
}
