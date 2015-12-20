package geass;/**
 * Created by numan947 on 2015-12-03.
 */

import javafx.animation.FadeTransition;
import javafx.animation.PauseTransition;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.beans.binding.Bindings;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.event.Event;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Cursor;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.input.*;
import javafx.scene.layout.*;
import javafx.scene.media.AudioSpectrumListener;
import javafx.scene.media.MediaView;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.util.Duration;

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
    boolean controlboxshowoff;

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
        mediaName.setValue("MK Player :)");


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
        control2.setMain(this);

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
        hbox.setMinHeight(80);
        hbox.setMinWidth(900);



        //Drag and Drop events
        INITDragDropEvent(mainScene);
        INITDragDropEvent(playlistScene);



        //PrimaryStage configurations
        hbox.getChildren().addAll(root1);
        //hbox.getChildren().add(root2);
        hbox.setAlignment(Pos.CENTER);


        HBox.setHgrow(root1, Priority.ALWAYS);
        HBox.setHgrow(root2,Priority.NEVER);

        bp.setCenter(control4.mediaView);

        BINDALL();
        root1.setStyle("-fx-background-color: #3E3E3E");
        hbox.setStyle("-fx-background-color: #3E3E3E");

        bp.setOnMouseClicked(click->{
            if(bp.getCenter()==root2&&click.getButton()== MouseButton.PRIMARY&&click.getClickCount()==2){
                if(stage.isFullScreen())stage.setFullScreen(false);
                else stage.setFullScreen(true);
            }
        });
        applyMousePointerHiding();


       bp.setBottom(hbox);

        control4.mediaView.setStyle("-fx-background-color: #3E3E3E");
        bp.setStyle("-fx-background-color: #000000");
        //bp.getCenter().setDisable(true);
        bp.setRight(null);
        bp.setLeft(null);
        bp.setTop(null);

        //primaryStage settings
        primaryStage.setOnCloseRequest(e->{
            Platform.exit();
        });
        primaryStage.setFullScreenExitKeyCombination(KeyCombination.NO_MATCH);
        setupContextMenu();
        primaryStage.setResizable(false);
        primaryStage.titleProperty().bind(mediaName);
        primaryStage.setScene(mainScene);
        primaryStage.show();

    }


    void INITDragDropEvent(Scene scene)
    {

        applyControlHiding(hbox);
        onFullScreenHideControl(stage);
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

                File frst=lst.get(0);
                int np=control3.mediaList.getItems().size();
                for(File f:lst){
                    mediaForList mm=new mediaForList();
                    mm.setMediaFile(f);
                    mm.setMediaPos(Integer.toString(++control3.cnt));
                    mm.setMediaName(f.getName());
                    control3.mediaList.getItems().add(mm);
                }
                if(scene==mainScene){
                    control1.setMediaModel(frst.toURI().toString());
                    this.mediaName.setValue("NOW PLAYING "+frst.getName());
                    control1.mediaName=frst.getName();
                    Platform.runLater(()->{
                        control3.mediaList.requestFocus();
                        control3.mediaList.getFocusModel().focus(np);
                        System.out.println("HI NUMAN "+np);
                    });
                }
            }
        });
    }

    void BINDALL()
    {
        MediaView view=control4.mediaView;
        view.fitWidthProperty().bind(mainScene.widthProperty());
        //view.fitHeightProperty().bind(mainScene.heightProperty().subtract(80));
        control4.mediaView.setPreserveRatio(false);
    }

    void setupContextMenu()
    {
        bp.addEventHandler(MouseEvent.MOUSE_CLICKED, event->{
            if(event.getButton()== MouseButton.SECONDARY){
                control1.cm.show(this.stage,event.getScreenX(),event.getScreenY());
            }
        });
        hbox.addEventHandler(MouseEvent.MOUSE_CLICKED,event->{
            event.consume();
        });
    }

    private void applyControlHiding(Node node) {
        hbox.setOnMouseEntered(e->{
            showConstantMediaControlBar();
        });
        hbox.setOnMouseExited(e->{
            if(stage.isFullScreen()&&bp.getCenter()==control4.mediaView) {

                showTempMediaControlBar();

            }

        });

    }

    private void onFullScreenHideControl(Stage stage) {
        try {
            stage.fullScreenProperty().addListener((observable, oldValue, newValue) -> {
                if(newValue) {
                    if(bp.getCenter()==control4.mediaView)
                    showTempMediaControlBar();
                } else {
                    showConstantMediaControlBar();
                }
            });
        } catch (Exception iep) {
            iep.printStackTrace();
        }
    }

    private void showTempMediaControlBar(){
        Platform.runLater(()->{
            int h= (int) stage.getHeight();
            control4.mediaView.setFitHeight(h-1.1);
            System.out.println("IN MAIN::showTEMPCONTROLBAR");
        });
        controlboxshowoff=false;
        hbox.setOpacity(0.0);

    }

    void showConstantMediaControlBar(){
        if(stage.isFullScreen()&&bp.getCenter()==control4.mediaView) {
            controlboxshowoff=true;
            Platform.runLater(() -> {
                int h = (int) stage.getHeight();
                control4.mediaView.setFitHeight(h - 80);
                System.out.println("IN MAIN::showConstantControls");
            });
        }
        hbox.setOpacity(1.0);
    }

    void applyMousePointerHiding()
    {
        PauseTransition idle = new PauseTransition(Duration.seconds(1.5));
        idle.setOnFinished(e ->bp.setCursor(Cursor.NONE));
        bp.addEventHandler(Event.ANY, e -> {
            idle.playFromStart();
            bp.setCursor(Cursor.DEFAULT);
        });
        hbox.addEventHandler(Event.ANY,e->{
            hbox.setCursor(Cursor.DEFAULT);
        });
    }





}
