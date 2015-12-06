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
    MediaModel model;
    Stage stage;
    StringProperty mediaName=new SimpleStringProperty();
    public static void main(String[] args) {
        launch(args);
    }

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
        //String url= Paths.get("F:/JAVA/abcd/src/geass/Angel.mp3").toUri().toString();
       // model.setUrl("file:/E:/Her%20OST%20-%2006.%20Some%20Other%20Place.mp3");
       // model.getPlayer().play();




        FXMLLoader loader1,loader2,loader3;
        Parent root1,root2,root3;


        loader1=new FXMLLoader(getClass().getResource("PlayerControls.fxml"));
        root1=loader1.load();
        PanelController control1=loader1.getController();


        loader2=new FXMLLoader(getClass().getResource("MetaData.fxml"));
        root2=loader2.load();
        MetaDataController control2=loader2.getController();

        loader3=new FXMLLoader(getClass().getResource("mediaList.fxml"));
        root3=loader3.load();
        mediaListController control3=loader3.getController();




        control2.INITIALIZE(model);
        control1.INITVIEW(model);
        control1.DISABLEALL();
        control1.setMain(this);


        hbox.getChildren().add(root1);
        hbox.getChildren().add(root2);
        hbox.setAlignment(Pos.BASELINE_RIGHT);
        HBox.setHgrow(root1, Priority.ALWAYS);
        HBox.setHgrow(root2,Priority.NEVER);

        bp.setRight(root3);
        bp.setBottom(hbox);

        primaryStage.titleProperty().bind(mediaName);

        primaryStage.setScene(new Scene(bp,1000,500));
        primaryStage.show();
    }
}
