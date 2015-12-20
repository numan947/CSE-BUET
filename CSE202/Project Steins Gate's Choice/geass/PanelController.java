package geass;

import javafx.application.Platform;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.beans.binding.Bindings;
import javafx.beans.property.DoubleProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCharacterCombination;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaPlayer.Status;
import javafx.scene.media.MediaView;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.stage.Window;
import javafx.util.Duration;

import java.io.File;
import java.net.URL;
import java.util.List;

public class PanelController {

    CODE main;
    MediaModel mediaModel;
    private StatusListener status;
    private CurrentTimeListener currentTime;
    ImageView playPauseIcon,seeR,seeL,stopIcon,playlistImgview,repeatView,fileOpenImageView,fsImageView,muteView;
    Image playIcon,pauseIcon,hi,lo,playlistImg,repIcon1,repIcon2,fileOpenImage,fsImage,muteImg;
    boolean repeat=false,alldisable=true;


    ContextMenu cm=new ContextMenu();
    MenuItem closeItem=new MenuItem("Close");
    MenuItem exitFS=new MenuItem("Exit Fullscreen");
    MenuItem playList=new MenuItem("Show playlist");
    MenuItem openItem=new MenuItem("Open Files...");
    MenuItem playFile=new MenuItem("Play");
    MenuItem stopFile=new MenuItem("stop");
    MenuItem about=new MenuItem("About");


    private Duration duration;
    String mediaName;
    boolean showinglist=false;
    Stage playliststage;
    mediaViewController playerview;

    public void setPlayerview(mediaViewController playerview) {
        this.playerview = playerview;
    }
    public void setMediaList(mediaListController mediaList) {
        this.mediaList = mediaList;
    }




    mediaListController mediaList;
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
    private Slider volumeSlider;

    @FXML
    private ImageView hiImg;

    @FXML
    private Label currentPlayTime;

    @FXML
    private Label StatusLabel;

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



    void setMediaModel(String url)//THIS IS WHERE THE PLAY BEGINS mu ha ha ha...
    {
        if(url!=null){
          //  removeAllListeners(mediaModel.getPlayer());
            this.mediaModel.setUrl(url);
            ENABLEALL();

            String fileType=url.substring(url.lastIndexOf('.')+1);
            if(fileType.equals("MP4")||fileType.equals("mp4")){
                main.bp.setCenter(main.control4.mediaView);
                main.bp.setBottom(main.hbox);
                playerview.mediaView.setMediaPlayer(this.mediaModel.getPlayer());
                System.out.println(mediaModel.getPlayer());
                main.bp.setTop(null);


                //playerview.mediaView.setPreserveRatio(true);
                main.root2.setOpacity(0.0);
            }
            else if(fileType.equals("MP3")||fileType.equals("mp3")){
                main.bp.setCenter(main.root2);
                main.root2.setOpacity(1.0);
            }
            else{
                System.out.println("fileTypeNotSupported");

                DISABLEALL();
                if(mediaList.mediaList.getItems().size()>1)
                mediaList.getNext();
                return;
            }

            playFile.setText("Pause");
            mediaModel.getPlayer().play();
            if(main.bp.getCenter()==playerview.mediaView) {
                Platform.runLater(() -> {
                    int h = (int) main.stage.getHeight();
                    //int h=playerview.mediaView.getMediaPlayer().getMedia().getHeight();

                    if(main.stage.isFullScreen()){
                        if(main.controlboxshowoff)
                            playerview.mediaView.setFitHeight(h-80);
                        else playerview.mediaView.setFitHeight(h-1.2);
                    }
                    else {
                        playerview.mediaView.setFitHeight(h - 110);
                    }
                    System.out.println("IN PanelControl:: setURl");
                });
            }
        }
    }


    @FXML
    void chooseFile(ActionEvent actionEvent) {
        OpenFile(OpenFileButton.getScene().getWindow());
    }

    @FXML
    void playAction(ActionEvent event) {

        //System.out.println("PLAY -_-");
       // System.out.println(mediaModel.getPlayer());
       // System.out.println(mediaModel.getPlayer().getStatus().toString());
       // System.out.println("ENDOFMEDIA "+atEndOfMedia);
       // System.out.println("CURRENT TIME PROPERTY "+ mediaModel.getPlayer().currentTimeProperty().getValue().toSeconds());



        MediaPlayer mediaPlayer = mediaModel.getPlayer();
        if(null != mediaPlayer) {
            MediaPlayer.Status status = mediaPlayer.getStatus();
            if (status == MediaPlayer.Status.UNKNOWN || status == MediaPlayer.Status.HALTED) {
                // don't do anything in these states
                return;
            }


            if (status == MediaPlayer.Status.PAUSED || status == MediaPlayer.Status.READY || status == MediaPlayer.Status.STOPPED) {
                stopButton.setDisable(false);
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


    @FXML
    void stopAction(ActionEvent event) {
        MediaPlayer mediaPlayer = mediaModel.getPlayer();
        if(null != mediaPlayer) {
            mediaPlayer.stop();
            playPauseIcon.setImage(playIcon);
            stopButton.setDisable(true);
            main.mediaName.setValue("mediaPlayer Stopped");
        } else {
            event.consume();
        }
    }

    @FXML
    void seekRAction(ActionEvent event) {
        //SeekAndUpdate(mediaModel.getPlayer().getTotalDuration().subtract(Duration.seconds(1)));
        mediaList.getNext();
    }

    @FXML
    void seekLAction(ActionEvent event) {
        //SeekAndUpdate(Duration.ZERO);
        mediaList.getPrev();
    }

    @FXML
    void repaetAction(ActionEvent event) {
        if(repeat){
            repeatView.setImage(repIcon1);
            repeat=false;
        }
        else{
            repeatView.setImage(repIcon2);
            repeat=true;
        }

    }


    @FXML
    void muteAction(ActionEvent event) {
        if(mediaModel.getPlayer().isMute()){
            mediaModel.getPlayer().setMute(false);
            muteView.setImage(hi);
        }
        else{
            mediaModel.getPlayer().setMute(true);
            muteView.setImage(muteImg);
        }


    }

    @FXML
    void showPlayList(ActionEvent event) {
        showList();
    }



    void INITVIEW(MediaModel mediamodel)
    {
        //Iitiating PlayList variables & others :P
        playliststage=new Stage();
        playliststage.initStyle(StageStyle.DECORATED);
        playliststage.setOnCloseRequest(e->{
            playliststage.close();
            showinglist=false;
        });
        playlistImg=new Image(getClass().getResource("playlistimg.png").toString());
        playlistImgview=new ImageView(playlistImg);
        playListButton.setGraphic(playlistImgview);

        //Seek Buttons views
        URL url=getClass().getResource("seekL.png");
        seeL=new ImageView(url.toString());
        url=getClass().getResource("seekR.png");
        seeR=new ImageView(url.toString());
        SeekL.setGraphic(seeL);
        SeekR.setGraphic(seeR);

        //PlayPause Button views
        playIcon=new Image(getClass().getResource("play.png").toString());
        pauseIcon=new Image(getClass().getResource("pause.png").toString());
        playPauseIcon=new ImageView(playIcon);
        playButton.setGraphic(playPauseIcon);
        //Stop Button views
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
        muteImg=new Image(getClass().getResource("muteImg.png").toString());
        muteView=new ImageView();
        muteView.setImage(hi);
        muteButton.setGraphic(muteView);



        //newing listeners
        status=new StatusListener();
        currentTime=new CurrentTimeListener();

        this.mediaModel=mediamodel;
        volumeSlider.setValue(.50);

        //PositionListener
        positionSlider.valueChangingProperty().addListener((observable, oldValue, newValue) -> {
            if(oldValue&&!newValue){
                double pos=positionSlider.getValue();
                SeekAndUpdate(mediamodel.getPlayer().getTotalDuration().multiply(pos));
            }
        });

        fullScreenButton.setOnAction(e->{
            if(main.stage.isFullScreen()){
                Platform.runLater(() -> {
                    int h = (int) main.stage.getHeight();
                    main.control4.mediaView.setFitHeight(h - 110);
                    System.out.println("IN Panel Controls::fs button");
                });
                main.stage.setFullScreen(false);
            }
            else main.stage.setFullScreen(true);

        });

        INITCONTEXTMENU();


    }

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
        alldisable=true;
    }
    void ENABLEALL()
    {
        muteButton.setDisable(false);
        positionSlider.setDisable(false);
        playButton.setDisable(false);
        SeekL.setDisable(false);
        SeekR.setDisable(false);
        stopButton.setDisable(false);
        mediaModel.getPlayer().setVolume(volumeSlider.getValue());
        volumeSlider.valueProperty().bindBidirectional(mediaModel.getPlayer().volumeProperty());
        addAllListeners(mediaModel.getPlayer());
        alldisable=false;
    }

    void INITCONTEXTMENU()
    {


        closeItem.setOnAction(event->{
            Platform.exit();
        });


        exitFS.setOnAction(event->{
            main.stage.setFullScreen(false);
        });


        playList.setOnAction(event->{
            showList();
        });


        openItem.setOnAction(event->{
            OpenFile(playerview.mediaView.getScene().getWindow());
        });


        playFile.setOnAction(event->{
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
            }
        });


        about.setOnAction(event->{
            //showAbout
        });


        cm.getItems().addAll(playList,playFile,stopFile,openItem,exitFS,closeItem);
    }















    private void addAllListeners(MediaPlayer newValue) {
        newValue.statusProperty().addListener(status);
        newValue.currentTimeProperty().addListener(currentTime);
        newValue.totalDurationProperty().addListener(observable -> {
            MediaPlayer mp=mediaModel.getPlayer();
            Duration total=mp.getTotalDuration();
            totalPlayTime.setText(processDuration(total));
        });

        newValue.setOnEndOfMedia(() -> {
            positionSlider.setValue(0.0);
            mediaModel.getPlayer().stop();
            playPauseIcon.setImage(playIcon);
            if(!repeat) mediaList.getNext();
            else mediaList.getNOW();
        });
    }

    void removeAllListeners(MediaPlayer oldValue) {
        volumeSlider.valueProperty().unbind();
        oldValue.statusProperty().removeListener(status);
        oldValue.currentTimeProperty().removeListener(currentTime);
    }

    private String processDuration(Duration duration) {
        double millis = duration.toMillis();
        int seconds = (int) (millis / 1000) % 60;
        int minutes = (int) (millis / (1000 * 60));
        return String.format("%02d:%02d", minutes, seconds);
    }

    private void updatePositionSlider(Duration duration)
    {
       // System.out.println("positionSlider value "+positionSlider.getValue()+"\ncurrentTIme "+duration.toSeconds());
        if(positionSlider.isValueChanging())return;
        Duration total=mediaModel.getPlayer().getTotalDuration();
       // System.out.println(total.toSeconds());
        if(total!=null)positionSlider.setValue(duration.toMillis()/total.toMillis());
    }



    private void UpdateStatus(Status status)
    {
        if(status==Status.UNKNOWN||status==null){
            positionSlider.setDisable(true);
            StatusLabel.setText("Loading...");
        }
        else{
            positionSlider.setDisable(false);
            StatusLabel.setText(status.toString());
            if(status==Status.PLAYING)playPauseIcon.setImage(pauseIcon);
            else if(status==Status.PAUSED)playPauseIcon.setImage(playIcon);
        }
    }


    private void SeekAndUpdate(Duration duration)
    {
        if(mediaModel.getPlayer().getStatus()==Status.STOPPED)mediaModel.getPlayer().pause();
        mediaModel.getPlayer().seek(duration);
        if(mediaModel.getPlayer().getStatus()!=Status.PLAYING)updatePositionSlider(duration);
    }


    private class StatusListener implements InvalidationListener {
        @Override
        public void invalidated(Observable observable) {
            Platform.runLater(() -> {
                UpdateStatus(mediaModel.getPlayer().getStatus());
            });
        }
    }
    private class CurrentTimeListener implements ChangeListener {

        @Override
        public void changed(ObservableValue observable, Object oldValue, Object newValue) {
            Platform.runLater(() -> {
                MediaPlayer mediaPlayer = mediaModel.getPlayer();
                Duration currentTime1 = mediaPlayer.getCurrentTime();
                //System.out.println("HELLO CURRENTTIME -_- "+ currentTime.toSeconds());
                currentPlayTime.setText(processDuration((Duration)newValue));
                if(newValue!=null)updatePositionSlider((Duration) newValue);
            });

        }
    }

    void setMain(CODE main)
    {
        this.main=main;
    }

    void showList()
    {
        if(!showinglist) {

            playliststage.setScene(main.playlistScene);
            playliststage.setMinWidth(400);
            playliststage.setAlwaysOnTop(true);
            playliststage.setResizable(false);
            playliststage.show();
            showinglist=true;
        }
        else{
            int gf=main.control3.nowPlaying;
            playliststage.close();
            main.control3.mediaList.getSelectionModel().clearSelection();
            showinglist=false;
            Platform.runLater(()->{
                main.control3.mediaList.requestFocus();
                main.control3.mediaList.getFocusModel().focus(gf);
            });
        }
        playliststage.setOnCloseRequest(event->{
            int gf=main.control3.nowPlaying;
            main.control3.mediaList.getSelectionModel().clearSelection();
            showinglist=false;
            Platform.runLater(()->{
                main.control3.mediaList.requestFocus();
                main.control3.mediaList.getFocusModel().focus(gf);
            });
        });
    }

    void OpenFile(Window window)
    {
        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("MediaFiles","*.mp3","*.mp4"));
        List<File> lst=fc.showOpenMultipleDialog(window);

        if(lst!=null) {

            for (File f : lst) {
                mediaForList mm = new mediaForList();
                mediaList.cnt++;
                mm.setMediaPos(Integer.toString(mediaList.cnt));
                mm.setMediaFile(f);
                mm.setMediaName(f.getName());
                mediaList.mediaList.getItems().add(mm);
            }

            if (this.mediaModel.getPlayer() == null) {
                ObservableList<mediaForList> items = mediaList.mediaList.getItems();
                mediaList.nowPlaying = 0;
                mediaForList nowMedia = items.get(mediaList.nowPlaying);
                this.mediaName=nowMedia.getMediaName();
                main.mediaName.setValue("NOW PLAYING" + " " + nowMedia.getMediaName());
                setMediaModel(nowMedia.getMediaFile().toURI().toString());
                System.out.println("NOW PLAYING " + mediaList.nowPlaying);

            }
        }
    }




}
