package geass;

/**
 * Created by numan947 on 2015-12-03.
 */

import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaPlayer.Status;
import javafx.scene.media.SubtitleTrack;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.stage.Window;
import javafx.util.Duration;
import java.io.File;
import java.net.URL;
import java.util.List;

/**
 *PanelController class is controller of our PlayerControls fxml file,
 * It contains several variables and Initializes various features of the Player controls
 * It contains two inner classes, StatusListener and CurrentTimeListener
 */

public class PanelController {

    CODE main;
    MediaModel mediaModel;
    //Listeners for mediaplayer
    private StatusListener status;
    private CurrentTimeListener currentTime;

    //Image and Imageviews of different buttons
    ImageView playPauseIcon,seeR,seeL,stopIcon,playlistImgview,repeatView,fileOpenImageView,fsImageView,muteView;
    Image playIcon,pauseIcon,hi,lo,playlistImg,repIcon1,repIcon2,fileOpenImage,fsImage,muteImg1,muteImg2;

    //ContextMenu & it's Items
    ContextMenu cm=new ContextMenu();
    MenuItem closeItem=new MenuItem("Close");
    MenuItem exitFS=new MenuItem("Exit Fullscreen");
    MenuItem playList=new MenuItem("Show playlist");
    MenuItem openItem=new MenuItem("Open Files...");
    MenuItem playFile=new MenuItem("Play");
    MenuItem stopFile=new MenuItem("stop");
    MenuItem about=new MenuItem("About");

    //Button tooltips
    Tooltip playt,stopt,seelt,seert,mutet,repet,opent,listt,fst;


    String mediaName;
    boolean showinglist=false,repeat=false;
    double prevvol;

    Stage playliststage,aboutStage,errorStage;

    //controllers for fxmls
    mediaViewController playerview;
    mediaListController mediaList;


    public void setPlayerview(mediaViewController playerview) {
        this.playerview = playerview;
    }
    public void setMediaList(mediaListController mediaList) {
        this.mediaList = mediaList;
    }


    @FXML
    private Button playListButton;

    @FXML
    protected Slider positionSlider;

    @FXML
    private Button SeekL;

    @FXML
    private Button SeekR;

    @FXML
    private Button OpenFileButton;

    @FXML
    private Label totalPlayTime;

    @FXML
    private ImageView loImg;

    @FXML
    Slider volumeSlider;

    @FXML
    private ImageView hiImg;

    @FXML
    private Label currentPlayTime;

    @FXML
    protected Label StatusLabel;

    @FXML
    private Button playButton;

    @FXML
    private Button stopButton;

    @FXML
    private Button fullScreenButton;

    @FXML
    private Button repeatButton;

    @FXML
    private Button muteButton;

    /**
     * setMediaModel method sets the url of the media to be played
     * given an url, it checks the validity of mediaType and sets the borderPane's center children accordingly and also
     * starts playing the media
     */


    void setMediaModel(String url) {
        System.out.println(prevvol);
        boolean noerr=true;
        if (url != null && mediaList.validated(new File(url))) {

            try {
                this.mediaModel.setUrl(url);
            }catch (Exception e){
                errorStage.setScene(main.errorScene);
                errorStage.show();
                if(mediaModel.getPlayer()!=null)
                    mediaModel.getPlayer().stop();
                main.bp.setCenter(main.def);
                if(mediaModel.getPlayer()!=null)
                removeAllListeners(mediaModel.getPlayer());
                DISABLEALL();
                System.out.println(e);
                noerr=false;
            }

            if (this.mediaModel.getPlayer() != null&&noerr) {
                ENABLEALL();
                //validating fileType (mp4/mp3) and setting the view of borderpane's center child
                String fileType = url.substring(url.lastIndexOf('.') + 1);
                if (fileType.equals("MP4") || fileType.equals("mp4")) {
                    main.bp.setCenter(main.control4.mediaView);
                    playerview.mediaView.setMediaPlayer(this.mediaModel.getPlayer());
                    //System.out.println(mediaModel.getPlayer());
                } else if (fileType.equals("MP3") || fileType.equals("mp3")) {
                    main.bp.setCenter(main.root2);
                } else {
                    System.out.println("fileTypeNotSupported");
                    DISABLEALL();
                    if (mediaList.mediaList.getItems().size() > 1)
                        mediaList.getNext();
                    return;
                }


                playFile.setText("Pause");
                mediaModel.getPlayer().play();
                if (volumeSlider.getValue() == 0.0) mediaModel.getPlayer().setMute(true);

                /**
                 * If the center is mediaView then, full screening will hide mediaControls else mediaCotrols
                 * will be always visible
                 */
                if (main.bp.getCenter() == playerview.mediaView) {
                    /**
                     * The code snippet below, resizes the mediaview once gone in fullScreen mode or vice versa, as the
                     * size of mediaView can't be changed from javafx's thread, we used Platform.Runlater to complete this task
                     * as a part of javafx application thread, as it's just some simple logic code, it doesn't BLOCK javafx's application thread
                     */

                    Platform.runLater(() -> {
                        int h = (int) main.stage.getHeight();

                        if (main.stage.isFullScreen()) {
                            if (main.controlboxshowoff)
                                playerview.mediaView.setFitHeight(h - 80);
                            else playerview.mediaView.setFitHeight(h - 1.2);
                        } else {
                            playerview.mediaView.setFitHeight(h - 110);
                        }

                        //System.out.println("IN PanelControl:: setURl");
                    });
                }
            }
        }
    }


    /**
     * chooseFile the method which is called when openFiles button is pressed
     *
     */

    @FXML
    void chooseFile(ActionEvent actionEvent) {
        OpenFile(OpenFileButton.getScene().getWindow());
    }

    /**
     * Plays the media & also checks status of the mediaPlayer
     */

    @FXML
    void playAction(ActionEvent event) {

        MediaPlayer mediaPlayer = mediaModel.getPlayer();

        if(null != mediaPlayer) {
            Status status = mediaPlayer.getStatus();
            if (status == Status.UNKNOWN || status == Status.HALTED) {
                /**
                 * usually UNKNOWN status is the status of mediaplayer, when it is just created, we replaced it with Ready Label
                 * HALTED status is given when critical error takes place
                 */
                return;
            }


            if (status == Status.PAUSED || status == Status.READY || status == Status.STOPPED) {
                stopButton.setDisable(false);
                stopFile.setDisable(false);
                mediaPlayer.play();
                main.mediaName.setValue("Now Playing "+this.mediaName);
            }
            else {
                mediaPlayer.pause();
                main.mediaName.setValue("MediaPlayer Paused");
            }
        } else {
            event.consume();
        }
    }

    /**
     * stopAction method handles the action of stop button and update the views accordingly
     */
    @FXML
    void stopAction(ActionEvent event) {
        MediaPlayer mediaPlayer = mediaModel.getPlayer();
        if(null != mediaPlayer) {
            mediaPlayer.stop();
            playPauseIcon.setImage(playIcon);
            stopButton.setDisable(true);
            stopFile.setDisable(true);
            playFile.setText("Play");
            main.mediaName.setValue("mediaPlayer Stopped");
            positionSlider.setValue(0.0);
        } else {
            event.consume();
        }
    }

    /**
     * seekRAction method gets and plays the next mediafile in the playlist
     **/

    @FXML
    void seekRAction(ActionEvent event) {
        mediaList.getNext();
    }

    /**
     * seekLAction method gets and plays the previous mediafile in the playlist
     **/

    @FXML
    void seekLAction(ActionEvent event) {
       mediaList.getPrev();
    }

    /**
     * repeatAction method handles repeatButton's event, it either enables or disables
     * repeating current file based on the current status
     */

    @FXML
    void repaetAction(ActionEvent event) {
        if(repeat){
            repeatView.setImage(repIcon1);
            repet.setText("Repeat This File");
            repeat=false;
        }
        else{
            repeatView.setImage(repIcon2);
            repet.setText("Repeat PlayList");
            repeat=true;
        }
    }

    /**
     * muteAction method mutes or unmutes the mediaPlayer
     */

    @FXML
    void muteAction(ActionEvent event) {
        if(mediaModel.getPlayer().isMute()){
            mediaModel.getPlayer().setMute(false);
            volumeSlider.setValue(prevvol);
            muteView.setImage(muteImg2);
            mutet.setText("Mute Audio");
        }
        else{
            prevvol=volumeSlider.getValue();
            volumeSlider.setValue(0.0);
            mediaModel.getPlayer().setMute(true);
            muteView.setImage(muteImg1);
            mutet.setText("Unmute Audio");
        }
    }

    /**
     * showPlaylist method shows the playlist
     *
     */
    @FXML
    void showPlayList(ActionEvent event) {
        showList();
    }

    /**
     * INITVIEW method initializes different images, imageviews, buttons, sliders etc and also
     * ContextMenu. It's the very first method that's called from the main(CODE) class
     */

    void INITVIEW(MediaModel mediamodel)
    {
        //Initiating playlist stage
        playliststage=new Stage();
        playliststage.initStyle(StageStyle.DECORATED);
        playliststage.setOnCloseRequest(e -> {
            playliststage.close();
            showinglist = false;
        });
        playliststage.setTitle("Play List");
        playliststage.setMinWidth(400);
        playliststage.setAlwaysOnTop(true);
        playliststage.setResizable(false);

        //initializing about stage
        aboutStage=new Stage();
        aboutStage.initStyle(StageStyle.DECORATED);

        //initializing errorstage
        errorStage=new Stage();
        errorStage.initStyle(StageStyle.UTILITY);
        errorStage.setAlwaysOnTop(true);
        errorStage.setResizable(false);

        //playlistbutton's image
        playlistImg=new Image(getClass().getResource("playlistimg.png").toString());
        playlistImgview=new ImageView(playlistImg);
        playListButton.setGraphic(playlistImgview);


        //Seek Buttons' views
        URL url=getClass().getResource("seekL.png");
        seeL=new ImageView(url.toString());
        url=getClass().getResource("seekR.png");
        seeR=new ImageView(url.toString());
        SeekL.setGraphic(seeL);
        SeekR.setGraphic(seeR);


        //PlayPause Button's views
        playIcon=new Image(getClass().getResource("play.png").toString());
        pauseIcon=new Image(getClass().getResource("pause.png").toString());
        playPauseIcon=new ImageView(playIcon);
        playButton.setGraphic(playPauseIcon);


        //Stop Button's views
        stopIcon=new ImageView(getClass().getResource("stop.png").toString());
        stopButton.setGraphic(stopIcon);


        //volume Icons
        hi=new Image(getClass().getResource("hivol.png").toString());
        lo=new Image(getClass().getResource("lovol.png").toString());
        hiImg.setImage(hi);
        loImg.setImage(lo);


        //repeatIcons
        repIcon1=new Image(getClass().getResource("repeatIcon1.png").toString());
        repIcon2=new Image(getClass().getResource("repeatIcon2.png").toString());
        repeatView=new ImageView();
        repeatView.setImage(repIcon1);
        repeatButton.setGraphic(repeatView);


        //FileOpenIcons
        fileOpenImage=new Image(getClass().getResource("fileopen.png").toString());
        fileOpenImageView=new ImageView(fileOpenImage);
        OpenFileButton.setGraphic(fileOpenImageView);


        //FullScreenIcons
        fsImage=new Image(getClass().getResource("fsicon.png").toString());
        fsImageView=new ImageView(fsImage);
        fullScreenButton.setGraphic(fsImageView);


        //MuteIcons
        muteImg1=new Image(getClass().getResource("muteImg1.png").toString());
        muteImg2=new Image(getClass().getResource("muteImg2.png").toString());
        muteView=new ImageView();
        muteView.setImage(muteImg2);
        muteButton.setGraphic(muteView);


        //newing listeners
        status=new StatusListener();
        currentTime=new CurrentTimeListener();

        //setting this class's mediamodel
        this.mediaModel=mediamodel;

        //setting default volume
        volumeSlider.setValue(.50);


        //adding listener to position slider
        positionSlider.valueChangingProperty().addListener((observable, oldValue, newValue) -> {
            if (oldValue && !newValue) {
                double pos = positionSlider.getValue();
                SeekAndUpdate(mediamodel.getPlayer().getTotalDuration().multiply(pos));
            }
        });

        //Resetting focus after dragging position slider
        positionSlider.setOnMouseReleased(event -> {
            if (main.bp.getCenter() == playerview.mediaView)
                playerview.mediaView.requestFocus();
            else if (main.bp.getCenter() == main.root2) main.root2.requestFocus();
            else main.def.requestFocus();
        });

        //Clicking on position slider will update it's position as well as mediaplayer's position
        positionSlider.setOnMouseClicked(event -> {

            System.out.println(positionSlider.getValue() + " VS " + event.getX() / 300);
            Status curstat = mediamodel.getPlayer().getStatus();

            mediamodel.getPlayer().pause();
            SeekAndUpdate(mediamodel.getPlayer().getTotalDuration().multiply(event.getX() / 300));
            if (curstat == Status.PLAYING) mediamodel.getPlayer().play();
        });

        //Resetting focus after dragging volume slider
        volumeSlider.setOnMouseReleased(event -> {
            if (main.bp.getCenter() == playerview.mediaView) playerview.mediaView.requestFocus();
            else if (main.bp.getCenter() == main.root2) main.root2.requestFocus();
            else main.def.requestFocus();
        });

        //fullScreen button action
        fullScreenButton.setOnAction(e -> {
            if (main.stage.isFullScreen()) {
                Platform.runLater(() -> {
                    int h = (int) main.stage.getHeight();
                    main.control4.mediaView.setFitHeight(h - 110);
                    System.out.println("IN Panel Controls::fs button");
                });
                main.stage.setFullScreen(false);
            } else main.stage.setFullScreen(true);

        });

        //default status label
        StatusLabel.setText("READY");


        //initializing contextmenu
        INITCONTEXTMENU();

        //initializing tooltip
        INITTOOLTIP();

    }

    /**
     * DISABLEALL fucntion disable most of the control buttons of control box. It's done
     * to avoid getting nullpointer exception. As at the very beginning no media is added to the mediaplayer
     */

    void DISABLEALL()
    {
        currentPlayTime.setText("00:00");
        totalPlayTime.setText("00:00");
        positionSlider.setValue(0.0);
        positionSlider.setDisable(true);
        playPauseIcon.setImage(playIcon);
        playButton.setDisable(true);
        SeekR.setDisable(true);
        SeekL.setDisable(true);
        stopButton.setDisable(true);
        muteButton.setDisable(true);
        playFile.setDisable(true);
        stopFile.setDisable(true);
    }

    /**
     * ENABLEALL function enables all the player controls, adds the status & currenttime listeners to the mediaPlayer
     * and also binds mediaPlayer's volume with the value of volumeslider
     */

    void ENABLEALL()
    {
        addAllListeners(mediaModel.getPlayer());
        muteButton.setDisable(false);
        positionSlider.setDisable(false);
        playButton.setDisable(false);
        SeekL.setDisable(false);
        SeekR.setDisable(false);
        stopButton.setDisable(false);
        mediaModel.getPlayer().setVolume(volumeSlider.getValue());
        volumeSlider.valueProperty().bindBidirectional(mediaModel.getPlayer().volumeProperty());

        playFile.setDisable(false);
        stopFile.setDisable(false);
    }

    /**
     * In the very beginning this function is called to cancel default focus on the buttons of the control panel
     */

    void removeAllFocus()
    {
        muteButton.setFocusTraversable(false);
        repeatButton.setFocusTraversable(false);
        fullScreenButton.setFocusTraversable(false);
        stopButton.setFocusTraversable(false);
        playButton.setFocusTraversable(false);
        volumeSlider.setFocusTraversable(false);
        positionSlider.setFocusTraversable(false);
        SeekL.setFocusTraversable(false);
        SeekR.setFocusTraversable(false);
        playListButton.setFocusTraversable(false);
        OpenFileButton.setFocusTraversable(false);
    }

    /**
     * INITCONTEXTMENU method initializes contex menu and it's items
     */

    void INITCONTEXTMENU()
    {
        closeItem.setOnAction(event->{
            Platform.exit();
        });


        exitFS.setOnAction(event->{
            if(main.stage.isFullScreen()){
                Platform.runLater(() -> {
                    int h = (int) main.stage.getHeight();
                    main.control4.mediaView.setFitHeight(h - 110);
                    System.out.println("IN Panel Controls::fs button");
                });
                main.stage.setFullScreen(false);
            }
            else event.consume();
        });


        playList.setOnAction(event->{
            showList();
        });


        openItem.setOnAction(event->{
            OpenFile(main.bp.getScene().getWindow());
        });


        playFile.setOnAction(event->{
            if(stopButton.isDisabled()||stopFile.isDisable()) {
                stopButton.setDisable(false); stopFile.setDisable(false);
            }
            if(mediaModel.getPlayer().getStatus()==Status.PLAYING){
                mediaModel.getPlayer().pause();
                playPauseIcon.setImage(playIcon);
                playFile.setText("Play");

            }
            else{
                if(mediaModel.getPlayer().getStatus()==Status.STOPPED)stopFile.setDisable(false);
                mediaModel.getPlayer().play();
                playPauseIcon.setImage(pauseIcon);
                playFile.setText("Pause");
            }
        });


        stopFile.setOnAction(event->{
            //stopFile
            if(mediaModel.getPlayer().getStatus()!=Status.STOPPED){
                mediaModel.getPlayer().stop();
                stopFile.setDisable(true);
                stopButton.setDisable(true);
                playPauseIcon.setImage(playIcon);
                playFile.setText("Play");
                positionSlider.setValue(0.0);
            }
        });


        about.setOnAction(event->{
            if(aboutStage.isShowing())aboutStage.close();
            else{
                aboutStage.setScene(main.aboutScene);
                aboutStage.setTitle("About MK Player");
                aboutStage.setResizable(false);
                aboutStage.show();
            }
        });


        cm.getItems().addAll(playList,playFile,stopFile,openItem,exitFS,about,closeItem);
    }

    /**
     * INITTOOLTIP method initializes and adds tooltips of different buttons
     */
    void INITTOOLTIP()
    {
        playt=new Tooltip();
        playButton.setTooltip(playt);


        stopt=new Tooltip();
        stopButton.setTooltip(stopt);
        stopt.setText("Stop File");


        seelt=new Tooltip();
        SeekL.setTooltip(seelt);
        seelt.setText("Play Next Media");


        seert=new Tooltip();
        SeekR.setTooltip(seert);
        seert.setText("Play Previous Media");


        mutet=new Tooltip();
        muteButton.setTooltip(mutet);
        mutet.setText("Mute Audio");


        repet=new Tooltip();
        repeatButton.setTooltip(repet);
        repet.setText("Repeat This File");


        opent=new Tooltip();
        OpenFileButton.setTooltip(opent);
        opent.setText("Open Files...");


        listt=new Tooltip();
        playListButton.setTooltip(listt);
        listt.setText("Show Playlist");


        fst=new Tooltip();
        fullScreenButton.setTooltip(fst);
        fst.setText("Make Full Screen");
    }


    /**
     * addAllListeners method adds statuslistener and currenttime listener to the mediaplayer, when new media is assigned
     * it also sets the total duration of new media file and also defines what to do when the media is at it's end
     */

    private void addAllListeners(MediaPlayer newValue) {
        newValue.statusProperty().addListener(status);
        newValue.currentTimeProperty().addListener(currentTime);
        newValue.totalDurationProperty().addListener(observable -> {
            MediaPlayer mp = mediaModel.getPlayer();
            Duration total = mp.getTotalDuration();
            totalPlayTime.setText(processDuration(total));
        });

        newValue.setOnEndOfMedia(() -> {
            positionSlider.setValue(0.0);
            mediaModel.getPlayer().stop();
            playPauseIcon.setImage(playIcon);
            if (!repeat) mediaList.getNext();
            else mediaList.getNOW();
        });

    }

    /**
     * removes all the listeners from the player when the playlist is empty
     */
    void removeAllListeners(MediaPlayer oldValue) {
        volumeSlider.valueProperty().unbind();
        oldValue.statusProperty().removeListener(status);
        oldValue.currentTimeProperty().removeListener(currentTime);
    }

    /**
     * given a Duration Object processDuration method converts it to
     * minutes and seconds and then return these as String
     */

    private String processDuration(Duration duration) {
        double millis = duration.toMillis();
        int seconds = (int) (millis / 1000) % 60;
        int minutes = (int) (millis / (1000 * 60));
        return String.format("%02d:%02d", minutes, seconds);
    }

    /**
     * given a Duration object updatePositionSlider method updates the position of the positionSlider
     * the value of this slider is from 0 to 1
     */

    void updatePositionSlider(Duration duration)
    {
       if(positionSlider.isValueChanging())return;
        Duration total=mediaModel.getPlayer().getTotalDuration();
       if(total!=null)positionSlider.setValue(duration.toMillis()/total.toMillis());
    }

    /**
     * given a Status object UpdateStatus updates the Status of the StatusLabel
     * it also updates the icon of playbutton
     */
    void UpdateStatus(Status status)
    {
        //System.out.println("UPDATE "+mediaModel.getPlayer().getCurrentTime());
        if(status==Status.UNKNOWN||status==null){
            positionSlider.setDisable(true);
            StatusLabel.setText("UNKNOWN");
        }
        else{
            positionSlider.setDisable(false);
            StatusLabel.setText(status.toString());
            if(status==Status.PLAYING){
                playFile.setText("Pause");
                playPauseIcon.setImage(pauseIcon);
                playt.setText("Pause File");
            }
            else if(status==Status.PAUSED){
                playFile.setText("Play");
                playPauseIcon.setImage(playIcon);
                playt.setText("Play File");
            }
        }
    }

    /**
     * given a Duration object SeekAndUpdate method
     * seeks and update the mediaplyer's position as well as positionslider's position
     * to the saught time
     */
    void SeekAndUpdate(Duration duration)
    {
        if(mediaModel.getPlayer().getStatus()==Status.STOPPED){
            stopButton.setDisable(false);
            stopFile.setDisable(false);
            mediaModel.getPlayer().pause();
        }
        mediaModel.getPlayer().seek(duration);
        if(mediaModel.getPlayer().getStatus()!=Status.PLAYING)updatePositionSlider(duration);
    }


    /**
     * this class impelents change listener, and the value of status is changed, it updates the status
     */
    private class StatusListener implements ChangeListener {

        @Override
        public void changed(ObservableValue observable, Object oldValue, Object newValue) {
            Platform.runLater(() -> {
                UpdateStatus((Status) newValue);
            });

        }
    }

    /**
     * this class also implements changeListener and when current time
     */

    private class CurrentTimeListener implements ChangeListener {

        @Override
        public void changed(ObservableValue observable, Object oldValue, Object newValue) {
            Platform.runLater(() -> {
                currentPlayTime.setText(processDuration((Duration)newValue));
                if(newValue!=null)updatePositionSlider((Duration) newValue);
            });

        }
    }


    void setMain(CODE main)
    {
        this.main=main;
    }


    /**
     * showList function manages the showing of the playlist it also resets focus to currently playing
     * file
     */

    void showList()
    {
        if(!showinglist) {
            playliststage.setScene(main.playlistScene);
            playliststage.show();
            showinglist=true;
        }


        else{
            int gf=main.control3.nowPlaying;
            playliststage.close();
            main.control3.mediaList.getSelectionModel().clearSelection();
            showinglist=false;

            /**the code snippet in below
             *sets the default focus of
             *the tableview(playlist) to
             *currently playing media
             */

            Platform.runLater(()->{
                main.control3.mediaList.requestFocus();
                main.control3.mediaList.getFocusModel().focus(gf);
            });
        }

        playliststage.setOnCloseRequest(event->{
            int gf=main.control3.nowPlaying;
            main.control3.mediaList.getSelectionModel().clearSelection();
            showinglist=false;

            /**the code snippet in below
             *sets the default focus of
             *the tableview(playlist) to
             *currently playing media
             */
            Platform.runLater(() -> {
                main.control3.mediaList.requestFocus();
                main.control3.mediaList.getFocusModel().focus(gf);
            });
        });

        playliststage.focusedProperty().addListener(event->{
            if(!playliststage.isFocused()){
                main.control3.mediaList.getSelectionModel().clearSelection();
                Platform.runLater(() -> {
                    main.control3.mediaList.requestFocus();
                    main.control3.mediaList.getFocusModel().focus(main.control3.nowPlaying);
                });
            }
        });
    }

    /**
     * OpenFile method handles the openning of file from the control box, when a file is opened from control box, it's appended
     * At the end of playlist & started playing immediately
     */
    void OpenFile(Window window)
    {
        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("MediaFiles","*.mp3","*.mp4"));
        List<File> lst=fc.showOpenMultipleDialog(window);
        mediaList.nowPlaying=mediaList.cnt;
        if(lst!=null) {

            for (File f : lst) {
                mediaForList mm = new mediaForList();
                mediaList.cnt++;
                mm.setMediaPos(Integer.toString(mediaList.cnt));
                mm.setMediaFile(f);
                mm.setMediaName(f.getName());
                mediaList.mediaList.getItems().add(mm);
            }


            ObservableList<mediaForList> items = mediaList.mediaList.getItems();
            mediaForList nowMedia = items.get(mediaList.nowPlaying);
            this.mediaName=nowMedia.getMediaName();
            main.mediaName.setValue("NOW PLAYING" + " " + nowMedia.getMediaName());
            setMediaModel(nowMedia.getMediaFile().toURI().toString());
            //System.out.println("NOW PLAYING " + mediaList.nowPlaying);

            /**the code snippet in below
             *sets the default focus of
             *the tableview(playlist) to
             *currently playing media
             */

            Platform.runLater(()->{
                main.control3.mediaList.requestFocus();
                main.control3.mediaList.getFocusModel().focus(mediaList.nowPlaying);
                System.out.println("HI NUMAN "+mediaList.nowPlaying);
            });
        }
    }
}
