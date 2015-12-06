package geass;

import javafx.application.Platform;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaPlayer.Status;
import javafx.stage.FileChooser;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.io.File;
import java.net.URL;

public class PanelController {

    CODE main;
    MediaModel mediaModel;
    private StatusListener status;
    private CurrentTimeListener currentTime;
    ImageView playPauseIcon,seeR,seeL,stopIcon;
    Image playIcon,pauseIcon;
    boolean atEndOfMedia=false;
    boolean stopRequested=false;
    private Duration duration;
    String mediaName;

    @FXML
    private Slider positionSlider;

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
    void chooseFile(ActionEvent actionEvent) {
        Stage chooserStage=new Stage();
        FileChooser fc=new FileChooser();
        fc.setTitle("Mad Scientisto :3 :3 ");
        fc.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("audioFile","*.mp3"));
        //chooserStage.initModality(Modality.WINDOW_MODAL);
        //chooserStage.initOwner(main.stage.getScene().getWindow());
        File file=fc.showOpenDialog(main.stage);
        if(file!=null){
            this.mediaName=file.getName();
            main.mediaName.setValue("NOW PLAYING "+ mediaName);
            mediaModel.setUrl(file.toURI().toString());
            ENABLEALL();
            //removeAllListeners(mediaModel.getPlayer());
            addAllListeners(mediaModel.getPlayer());
            mediaModel.getPlayer().play();
        }
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
                main.mediaName.setValue("Now Playing "+mediaName);
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
        SeekAndUpdate(mediaModel.getPlayer().getTotalDuration().subtract(Duration.seconds(1)));
    }

    @FXML
    void seekLAction(ActionEvent event) {
        SeekAndUpdate(Duration.ZERO);
    }


    void INITVIEW(MediaModel mediamodel)
    {
        //Seek Buttons views
        URL url=getClass().getResource("seekL.jpg");
        seeL=new ImageView(url.toString());
        url=getClass().getResource("seekR.jpg");
        seeR=new ImageView(url.toString());
        SeekL.setGraphic(seeL);
        SeekR.setGraphic(seeR);

        //PlayPause Button views
        playIcon=new Image(getClass().getResource("play.png").toString());
        pauseIcon=new Image(getClass().getResource("pause.png").toString());
        playPauseIcon=new ImageView(playIcon);
        playButton.setGraphic(playPauseIcon);
        //Stop Button views
        stopIcon=new ImageView(getClass().getResource("stop.jpg").toString());
        stopButton.setGraphic(stopIcon);


        //newing listeners
        status=new StatusListener();
        currentTime=new CurrentTimeListener();

        this.mediaModel=mediamodel;


        //mediamodel.playerProperty().addListener(new MediaPlayerListener());???

      //  System.out.println("MEDIA MODEL -_- "+mediamodel.getPlayer());
        //PositionListener
        positionSlider.valueChangingProperty().addListener((observable, oldValue, newValue) -> {
            if(oldValue&&!newValue){
                double pos=positionSlider.getValue();
                SeekAndUpdate(mediamodel.getPlayer().getTotalDuration().multiply(pos));
            }
        });
//        addAllListeners(mediaModel.getPlayer());
       // mediamodel.getPlayer().play();
    }

    void DISABLEALL()
    {
        positionSlider.setDisable(true);
        playButton.setDisable(true);
        SeekR.setDisable(true);
        SeekL.setDisable(true);
        stopButton.setDisable(true);
    }
    void ENABLEALL()
    {
        positionSlider.setDisable(false);
        playButton.setDisable(false);
        SeekL.setDisable(false);
        SeekR.setDisable(false);
        stopButton.setDisable(false);
    }















    private void addAllListeners(MediaPlayer newValue) {
        newValue.statusProperty().addListener(status);
        newValue.currentTimeProperty().addListener(currentTime);
        newValue.totalDurationProperty().addListener(observable -> {
            MediaPlayer mp=mediaModel.getPlayer();
            Duration total=mp.getTotalDuration();
            totalPlayTime.setText(processDuration(total));
        });
        volumeSlider.valueProperty().bindBidirectional(newValue.volumeProperty());
        newValue.setOnEndOfMedia(() -> {
            positionSlider.setValue(0.0);
            mediaModel.getPlayer().stop();
            playPauseIcon.setImage(playIcon);
        });
    }

    private void removeAllListeners(MediaPlayer oldValue) {
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
            Platform.runLater(new Runnable() {
                @Override
                public void run() {
                    MediaPlayer mediaPlayer = mediaModel.getPlayer();
                    Duration currentTime = mediaPlayer.getCurrentTime();
                    //System.out.println("HELLO CURRENTTIME -_- "+ currentTime.toSeconds());
                    currentPlayTime.setText(processDuration((Duration)newValue));
                    if(newValue!=null)updatePositionSlider((Duration) newValue);
                }
            });

        }
    }
/*
    private class MediaPlayerListener implements ChangeListener<MediaPlayer> {
        @Override
        public void changed(ObservableValue<? extends MediaPlayer> observable,
                            MediaPlayer oldValue, MediaPlayer newValue) {
            if (oldValue != null) {
                removeAllListeners(oldValue);
            }
            addAllListeners(newValue);
        }
    }*/
    void setMain(CODE main)
    {
        this.main=main;
    }




}
