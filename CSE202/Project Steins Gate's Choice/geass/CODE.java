package geass;/**
 * Created by numan947 on 2015-12-03.
 */

import javafx.application.Application;
import javafx.application.Platform;
import javafx.beans.binding.Bindings;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.input.Dragboard;
import javafx.scene.input.TransferMode;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.StackPane;
import javafx.scene.media.MediaView;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.nio.file.Paths;
import java.util.List;

public class CODE extends Application {
    //Variables in Main Application Class
    MediaModel model;
    Stage stage;
    StringProperty mediaName=new SimpleStringProperty();
    MediaView mv;
    BorderPane bp=new BorderPane();
    HBox hbox=new HBox();
    StackPane pp=new StackPane();
    //loaders and parents
    FXMLLoader loader1,loader2,loader3,loader4;
    Parent root1,root2,root3,root4;

    //Movable Scenes
    Scene playlistScene;
    Scene panelScene;
    Scene fullScreen;
    Scene mainScene;

    //Scene Controllers
    PanelController control1;
    mediaViewController control4;
    mediaListController control3;
    MetaDataController control2;



    //Main
    public static void main(String[] args) {
        launch(args);
    }

    //Start of start()
    @Override
    public void start(Stage primaryStage) throws IOException {
        //layouts
        stage=primaryStage;




        //mediaNaming
        mediaName.setValue("Makise Kurisu Player :)");


        //default Media and MediaViews
        model=new MediaModel();
        mv=new MediaView();




        //setScene(new Scene(new Group(mv), size.getWidth(), size.getHeight()));



        //loading fxml4
        loader4=new FXMLLoader(getClass().getResource("mediaView.fxml"));
        root4=loader4.load();
        control4=loader4.getController();


        //loading fxml3
        loader3=new FXMLLoader(getClass().getResource("mediaList.fxml"));
        root3=loader3.load();
        control3=loader3.getController();


        //loading fxml1
        loader1=new FXMLLoader(getClass().getResource("PlayerControls.fxml"));
        root1=loader1.load();
        control1=loader1.getController();

        //loading fxml2
        loader2=new FXMLLoader(getClass().getResource("MetaData.fxml"));
        root2=loader2.load();
        control2=loader2.getController();




        //controlling the fxmls

        control4.setMain(this);
        control4.INITIALIZE();

        control3.setMain(this);
        control3.INITIALIZE();
        control3.setPanel(control1);

        control2.INITIALIZE(model);

        control1.INITVIEW(model);
        control1.DISABLEALL();
        control1.setMain(this);
        control1.setMediaList(control3);
        control1.setPlayerview(control4);

        //Setting up different Scenes
        pp.getChildren().add(control4.mediaView);
        playlistScene=new Scene(root3,213,397);
        panelScene=new Scene(root1,745,95);
        fullScreen=new Scene(pp,300,400);
        mainScene=new Scene(bp,900,645);



        //Drag and Drop events
        INITDragDropEvent(mainScene);
        INITDragDropEvent(playlistScene);



        //PrimaryStage configurations
        hbox.getChildren().add(root1);
        //hbox.getChildren().add(root2);
        hbox.setAlignment(Pos.CENTER);

        HBox.setHgrow(root1, Priority.ALWAYS);
        HBox.setHgrow(root2,Priority.NEVER);
        BINDALL();

        //BorderPane settings


        bp.setCenter(pp);
        Stage stage1=new Stage();
        stage1.setScene(new Scene(hbox,400,100));
        stage1.show();
        stage1.setAlwaysOnTop(true);

        //bp.setBottom(hbox);
        //bp.getCenter().setDisable(true);
        bp.setRight(null);
        bp.setLeft(null);
        bp.setTop(null);

        //primaryStage settings
        primaryStage.setOnCloseRequest(e->{
            Platform.exit();
        });

        primaryStage.setResizable(false);
        primaryStage.titleProperty().bind(mediaName);
        primaryStage.setScene(mainScene);
        primaryStage.show();

    }


    void INITDragDropEvent(Scene scene)
    {

        scene.setOnDragOver(dragEvent->{
            Dragboard db=dragEvent.getDragboard();
            if(db.hasFiles()){
                dragEvent.acceptTransferModes(TransferMode.COPY);
            }
            else dragEvent.consume();
        });
        scene.setOnDragDropped(dragevent->{
            Dragboard db=dragevent.getDragboard();
            if(db.hasFiles()){
                List<File>lst=db.getFiles();
                int cnt=control3.mediaList.getItems().size();
                File frst=lst.get(0);
                for(File f:lst){
                    mediaForList mm=new mediaForList();
                    mm.setMediaFile(f);
                    mm.setMediaPos(Integer.toString(++cnt));
                    mm.setMediaName(f.getName());
                    control3.mediaList.getItems().add(mm);
                }
                if(scene==mainScene){
                    control1.setMediaModel(frst.toURI().toString());
                    this.mediaName.setValue("NOW PLAYING "+frst.getName());
                    control1.mediaName=frst.getName();
                }
            }
        });
    }

    void BINDALL()
    {
        MediaView view=control4.mediaView;
        view.fitWidthProperty().bind(mainScene.widthProperty());
        view.fitHeightProperty().bind(mainScene.heightProperty().subtract(60));

    }






}
