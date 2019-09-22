package geass;

/**
 * Created by numan947 on 2015-12-03.
 */

import javafx.animation.PauseTransition;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.event.Event;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Cursor;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.media.MediaPlayer;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.io.File;
import java.io.IOException;
import java.util.List;

/**
 * This class is our main javafx application class several scenes, stages and fucntions are defined in
 * this class
 */

public class CODE extends Application {
    //Variables in Main Application Class
    MediaModel model;
    Stage stage;
    StringProperty mediaName=new SimpleStringProperty();
    BorderPane bp=new BorderPane();
    HBox hbox=new HBox();
    boolean controlboxshowoff;

    //loaders and parents
    FXMLLoader loader1,loader2,loader3,loader4,loader5,loader6;
    Parent root1,root2,root3,root4,root5,root6;

    //Movable Scenes
    Scene playlistScene;
    Scene panelScene;
    Scene mainScene;
    Scene aboutScene;
    Scene errorScene;

    //Scene Controllers
    PanelController control1;
    MetaDataController control2;
    mediaListController control3;
    mediaViewController control4;

    //Default image of mediaPlayer
    ImageView def=new ImageView(new Image(getClass().getResource("1234.png").toString()));


    public static void main(String[] args) {
        launch(args);
    }


    @Override
    public void start(Stage primaryStage) throws IOException {
        //layouts
        stage=primaryStage;


        //mediaNaming, while none is playing medianame==playername
        mediaName.setValue("MK Player :)");


        //default mediaModel
        model=new MediaModel();



        //loading fxml4 (mediaview)
        loader4=new FXMLLoader(getClass().getResource("mediaView.fxml"));
        root4=loader4.load();
        control4=loader4.getController();


        //loading fxml3 (PlayList)
        loader3=new FXMLLoader(getClass().getResource("mediaList.fxml"));
        root3=loader3.load();
        control3=loader3.getController();


        //loading fxml1 (ControlPanel)
        loader1=new FXMLLoader(getClass().getResource("PlayerControls.fxml"));
        root1=loader1.load();
        control1=loader1.getController();


        //loading fxml2(metaData)
        loader2=new FXMLLoader(getClass().getResource("MetaData.fxml"));
        root2=loader2.load();
        control2=loader2.getController();


        //loading fxml5(About)
        loader5=new FXMLLoader(getClass().getResource("credits.fxml"));
        root5=loader5.load();

        //loading fxml6(Error Scene)
        loader6=new FXMLLoader(getClass().getResource("unavailable.fxml"));
        root6=loader6.load();

        //Setting up different Scenes
        playlistScene=new Scene(root3,213,397);
        panelScene=new Scene(root1,745,95);
        mainScene=new Scene(bp,900,645);
        aboutScene=new Scene(root5,344,423);
        errorScene=new Scene(root6);


        //controlling the fxmls (interconnecting different controllers)

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
        control1.removeAllFocus();
        control1.playliststage.initOwner(stage);
        control1.aboutStage.initOwner(stage);
        control1.errorStage.initOwner(control1.playliststage);



        //Applying DragNDrop to scnens
        INITDragDropEvent(mainScene);
        INITDragDropEvent(playlistScene);

        //configuring hbox
        hbox.setMinHeight(80);
        hbox.setMinWidth(900);
        hbox.getChildren().addAll(root1);
        hbox.setAlignment(Pos.CENTER);
        HBox.setHgrow(root1, Priority.ALWAYS);
        hbox.setStyle("-fx-background-color: #3E3E3E");
        root1.setStyle("-fx-background-color: #3E3E3E");


        //configuring borderpane
        bp.setCenter(def);
        bp.setOnMouseClicked(click -> {
            if (bp.getCenter() == root2 && click.getButton() == MouseButton.PRIMARY && click.getClickCount() == 2) {
                if (stage.isFullScreen()) stage.setFullScreen(false);
                else stage.setFullScreen(true);
            }
        });
        bp.setBottom(hbox);
        bp.setStyle("-fx-background-color: #000000");
        bp.setRight(null);
        bp.setLeft(null);
        bp.setTop(null);

        //Applying misc features
        applyMousePointerHiding();
        initKeyControls(mainScene);
        setupContextMenu();
        applyControlHiding();


        //primary stage configurations
        stage.getIcons().add(new Image(getClass().getResource("107235.jpg").toString()));
        control1.playliststage.getIcons().add(new Image(getClass().getResource("107235.jpg").toString()));
        control1.aboutStage.getIcons().add(new Image(getClass().getResource("107235.jpg").toString()));

        primaryStage.setOnCloseRequest(e -> {
            Platform.exit();
        });

        primaryStage.fullScreenProperty().addListener((observable, oldValue, newValue) -> {
            if(newValue) {
                if(bp.getCenter()==control4.mediaView)
                    showTempMediaControlBar();
            } else {
                showConstantMediaControlBar();
            }
        });

        primaryStage.setFullScreenExitKeyCombination(KeyCombination.NO_MATCH);

        //primaryStage.setMinHeight(715);
        //primaryStage.setMinWidth(915);
        primaryStage.setResizable(false);
        primaryStage.titleProperty().bind(mediaName);
        primaryStage.setScene(mainScene);
        primaryStage.show();

    }

    /**
     *INITDragDropEvent method initializes drag and drop features for
     * passed scene
     */


    void INITDragDropEvent(Scene scene) {

        scene.setOnDragOver(dragEvent -> {
            Dragboard db = dragEvent.getDragboard();
            if (db.hasFiles()) {
                dragEvent.acceptTransferModes(TransferMode.COPY);
            } else dragEvent.consume();
        });


        scene.setOnDragDropped(dragevent -> {
            Dragboard db = dragevent.getDragboard();
            if (db.hasFiles()) {
                List<File> lst = db.getFiles();

                File frst = lst.get(0);

                int np = control3.mediaList.getItems().size();

                for (File f : lst) {
                    mediaForList mm = new mediaForList();
                    mm.setMediaFile(f);
                    mm.setMediaPos(Integer.toString(++control3.cnt));
                    mm.setMediaName(f.getName());
                    control3.mediaList.getItems().add(mm);
                }

                if (scene == mainScene) {
                    control1.setMediaModel(frst.toURI().toString());
                    this.mediaName.setValue("NOW PLAYING " + frst.getName());
                    control1.mediaName = frst.getName();
                    Platform.runLater(() -> {
                        control3.mediaList.requestFocus();
                        control3.mediaList.getFocusModel().focus(np);
                        //System.out.println("NOW Playing " + np);
                    });
                }
            }
        });
    }


    /**
     * Innitializes Key events with the passed Scene
     *
     */

    void initKeyControls(Scene scene) {

        scene.setOnKeyPressed(e -> {

            if (e.getCode() == KeyCode.UP) {
                double vol = control1.volumeSlider.getValue();
                if (vol < .98) vol += .02;
                control1.volumeSlider.setValue(vol);
            }

            else if (e.getCode() == KeyCode.DOWN) {
                double vol = control1.volumeSlider.getValue();
                if (vol > 0.02) vol -= .02;
                control1.volumeSlider.setValue(vol);
            }

            else if (e.getCode() == KeyCode.ESCAPE) {
                if (stage.isFullScreen()) {
                    Platform.runLater(() -> {
                        int h = (int) stage.getHeight();
                        control4.mediaView.setFitHeight(h - 110);
                        System.out.println(" ::ESCAPE Button");
                    });
                    stage.setFullScreen(false);
                }
            }

            else if (e.getCode() == KeyCode.RIGHT) {
                if (!control1.positionSlider.isDisabled()) {
                    if (!e.isAltDown()) {
                        Duration curr = model.getPlayer().getCurrentTime();
                        curr = curr.add(Duration.seconds(5));
                        control1.SeekAndUpdate(curr);
                        System.out.println("GOING RIGHT");
                    } else {
                        control3.getNext();
                    }
                }
            }

            else if (e.getCode() == KeyCode.LEFT) {
                if (!control1.positionSlider.isDisabled()) {
                    if (!e.isAltDown()) {
                        Duration curr = model.getPlayer().getCurrentTime();
                        curr = curr.subtract(Duration.seconds(5));
                        control1.SeekAndUpdate(curr);
                        System.out.println("GOING LEFT");
                    } else {
                        control3.getPrev();
                    }
                }
            }

            else if (e.getCode() == KeyCode.SPACE) {
                if (!control1.positionSlider.isDisabled()) {
                    if (model.getPlayer().getStatus() == MediaPlayer.Status.PLAYING) model.getPlayer().pause();
                    else model.getPlayer().play();
                }
            }

            else if (e.isControlDown() && e.getCode() == KeyCode.ENTER) {
                if (stage.isFullScreen()){
                    Platform.runLater(() -> {
                        int h = (int) stage.getHeight();
                        control4.mediaView.setFitHeight(h - 110);

                    });
                    stage.setFullScreen(false);
                } else stage.setFullScreen(true);
            }
        });
    }


    /**
     * Sets Up context Menu with the primary border except hbox portion
     */
    void setupContextMenu()
    {
        bp.addEventHandler(MouseEvent.MOUSE_CLICKED, event -> {
            if (event.getButton() == MouseButton.SECONDARY) {
                control1.cm.show(this.stage, event.getScreenX(), event.getScreenY());
            }
        });

        hbox.addEventHandler(MouseEvent.MOUSE_CLICKED, Event::consume);
    }

    /**
     * hides control box on full screen
     */

    private void applyControlHiding() {
        hbox.setOnMouseEntered(e->{
            showConstantMediaControlBar();
        });

        hbox.setOnMouseExited(e->{
            if(stage.isFullScreen()&&bp.getCenter()==control4.mediaView) {
                showTempMediaControlBar();
            }
        });
    }

    /**
     * Shows temp mediacontrolbar which basically hides the control box
     */

    private void showTempMediaControlBar(){
        Platform.runLater(()->{
            int h= (int) stage.getHeight();
            control4.mediaView.setFitHeight(h-1.1);
            System.out.println("IN MAIN::showTEMPCONTROLBAR");
        });

        controlboxshowoff=false;
        hbox.setOpacity(0.0);
    }

    /**
     * this method basically shows the hidden controlbox
     */
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


    /**
     * it basically hides the mouse pointer when the mouse is idle for 1.5 seconds
     */
    void applyMousePointerHiding()
    {
        PauseTransition idle = new PauseTransition(Duration.seconds(1.5));
        idle.setOnFinished(e ->bp.setCursor(Cursor.NONE));

        bp.addEventHandler(Event.ANY, e -> {
            idle.playFromStart();
            bp.setCursor(Cursor.DEFAULT);
        });

        hbox.addEventHandler(Event.ANY, e -> {
            hbox.setCursor(Cursor.DEFAULT);
        });
    }
}
