package sample;

import javafx.application.Platform;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.geometry.VPos;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.media.MediaPlayer;
import javafx.stage.FileChooser;
import javafx.util.Duration;
import sample.BaseView;
import sample.MediaModel;

import java.io.File;
import java.net.URL;

class PlayerControlsView extends BaseView {
    private Image pauseImg;
    private Image playImg;
    private ImageView playPauseIcon;

    private StatusListener statusListener;
    private CurrentTimeListener currentTimeListener;

    private Node controlPanel;
    private Label statusLabel;
    private Label currentTimeLabel;
    private Label totalDurationLabel;
    private Slider volumeSlider;
    private Slider positionSlider;

    public PlayerControlsView(MediaModel mediaModel) {
        super(mediaModel);

        mediaModel.playerProperty().addListener(new MediaPlayerListener());

        statusListener = new StatusListener();
        currentTimeListener = new CurrentTimeListener();
        addListenersAndBindings(mediaModel.getPlayer());
    }

    @Override
    public Node initializeNode() {
        final Button openButton = createOpenButton();
        controlPanel = createControlPanel();
        volumeSlider = createSlider("volumeSlider");
        statusLabel = createLabel("Buffering", "statusDisplay");
        positionSlider = createSlider("positionSlider");
        totalDurationLabel = createLabel("00:00", "mediaText");
        currentTimeLabel = createLabel("00:00", "mediaText");

        positionSlider.valueChangingProperty().addListener(new PositionListener());

        final ImageView volLow = new ImageView();
        volLow.setId("volumeLow");

        final ImageView volHigh = new ImageView();
        volHigh.setId("volumeHigh");

        final GridPane gp = new GridPane();
        gp.setHgap(1);
        gp.setVgap(1);
        gp.setPadding(new Insets(10));

        final ColumnConstraints buttonCol = new ColumnConstraints(100);
        final ColumnConstraints spacerCol = new ColumnConstraints(40, 80, 80);
        final ColumnConstraints middleCol = new ColumnConstraints();
        middleCol.setHgrow(Priority.ALWAYS);

        gp.getColumnConstraints().addAll(buttonCol, spacerCol, middleCol,
                spacerCol, buttonCol);

        GridPane.setValignment(openButton, VPos.BOTTOM);
        GridPane.setHalignment(volHigh, HPos.RIGHT);
        GridPane.setValignment(volumeSlider, VPos.TOP);
        GridPane.setHalignment(statusLabel, HPos.RIGHT);
        GridPane.setValignment(statusLabel, VPos.TOP);
        GridPane.setHalignment(currentTimeLabel, HPos.RIGHT);

        gp.add(openButton, 0, 0, 1, 3);
        gp.add(volLow, 1, 0);
        gp.add(volHigh, 1, 0);
        gp.add(volumeSlider, 1, 1);
        gp.add(controlPanel, 2, 0, 1, 2);
        gp.add(statusLabel, 3, 1);
        gp.add(currentTimeLabel, 1, 2);
        gp.add(positionSlider, 2, 2);
        gp.add(totalDurationLabel, 3, 2);

        return gp;
    }

    private Button createOpenButton() {
        final Button openButton = new Button();
        openButton.setId("openButton");
        openButton.setOnAction(new OpenHandler());
        openButton.setPrefWidth(32);
        openButton.setPrefHeight(32);
        return openButton;
    }

    private Node createControlPanel() {
        final HBox hbox = new HBox();
        hbox.setAlignment(Pos.CENTER);
        hbox.setFillHeight(false);

        final Button playPauseButton = createPlayPauseButton();

        final Button seekStartButton = new Button();
        seekStartButton.setId("seekStartButton");
        seekStartButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                seekAndUpdatePosition(Duration.ZERO);
            }
        });

        final Button seekEndButton = new Button();
        seekEndButton.setId("seekEndButton");
        seekEndButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                final MediaPlayer mediaPlayer = mediaModel.getPlayer();
                final Duration totalDuration = mediaPlayer.getTotalDuration();
                final Duration oneSecond = Duration.seconds(1);
                seekAndUpdatePosition(totalDuration.subtract(oneSecond));
            }
        });

        hbox.getChildren().addAll(seekStartButton, playPauseButton, seekEndButton);
        return hbox;
    }

    private Button createPlayPauseButton() {
        URL url = getClass().getResource("pause.png");
        pauseImg = new Image(url.toString());

        url = getClass().getResource("play.png");
        playImg = new Image(url.toString());

        playPauseIcon = new ImageView(playImg);

        final Button playPauseButton = new Button(null, playPauseIcon);
        playPauseButton.setId("playPauseButton");
        playPauseButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent arg0) {
                final MediaPlayer mediaPlayer = mediaModel.getPlayer();
                if (mediaPlayer.getStatus() == MediaPlayer.Status.PLAYING) {
                    mediaPlayer.pause();
                } else {
                    mediaPlayer.play();
                }
            }
        });
        return playPauseButton;
    }

    private Slider createSlider(String id) {
        final Slider slider = new Slider(0.0, 1.0, 0.1);
        slider.setId(id);
        slider.setValue(0);
        return slider;
    }

    private Label createLabel(String text, String styleClass) {
        final Label label = new Label(text);
       // label.getStyleClass().add(styleClass);
        return label;
    }

    private void addListenersAndBindings(final MediaPlayer mp) {
        mp.statusProperty().addListener(statusListener);
        mp.currentTimeProperty().addListener(currentTimeListener);
        mp.totalDurationProperty().addListener(new TotalDurationListener());

        mp.setOnEndOfMedia(new Runnable() {
            @Override
            public void run() {
                mediaModel.getPlayer().stop();
            }
        });

        volumeSlider.valueProperty().bindBidirectional(mp.volumeProperty());
    }

    private void removeListenersAndBindings(MediaPlayer mp) {
        volumeSlider.valueProperty().unbind();
        mp.statusProperty().removeListener(statusListener);
        mp.currentTimeProperty().removeListener(currentTimeListener);
    }

    private void seekAndUpdatePosition(Duration duration) {
        final MediaPlayer mediaPlayer = mediaModel.getPlayer();

        if (mediaPlayer.getStatus() == MediaPlayer.Status.STOPPED) {
            mediaPlayer.pause();
        }

        mediaPlayer.seek(duration);

        if (mediaPlayer.getStatus() != MediaPlayer.Status.PLAYING) {
            updatePositionSlider(duration);
        }
    }

    private String formatDuration(Duration duration) {
        double millis = duration.toMillis();
        int seconds = (int) (millis / 1000) % 60;
        int minutes = (int) (millis / (1000 * 60));
        return String.format("%02d:%02d", minutes, seconds);
    }

    private void updateStatus(MediaPlayer.Status newStatus) {
        if (newStatus == MediaPlayer.Status.UNKNOWN || newStatus == null) {
            controlPanel.setDisable(true);
            positionSlider.setDisable(true);
            statusLabel.setText("Buffering");
        } else {
            controlPanel.setDisable(false);
            positionSlider.setDisable(false);

            statusLabel.setText(newStatus.toString());

            if (newStatus == MediaPlayer.Status.PLAYING) {
                playPauseIcon.setImage(pauseImg);
            } else {
                playPauseIcon.setImage(playImg);
            }
        }
    }

    private void updatePositionSlider(Duration currentTime) {
        if (positionSlider.isValueChanging())
            return;

        final MediaPlayer mediaPlayer = mediaModel.getPlayer();
        final Duration total = mediaPlayer.getTotalDuration();

        if (total == null || currentTime == null) {
            positionSlider.setValue(0);
        } else {
            positionSlider.setValue(currentTime.toMillis() / total.toMillis());
        }
    }

    private class MediaPlayerListener implements ChangeListener<MediaPlayer> {
        @Override
        public void changed(ObservableValue<? extends MediaPlayer> observable,
                            MediaPlayer oldValue, MediaPlayer newValue) {
            if (oldValue != null) {
                removeListenersAndBindings(oldValue);
            }
            addListenersAndBindings(newValue);
        }
    }

    private class OpenHandler implements EventHandler<ActionEvent> {
        @Override
        public void handle(ActionEvent event) {
            FileChooser fc = new FileChooser();
            fc.setTitle("Pick a Sound File");
            File song = fc.showOpenDialog(viewNode.getScene().getWindow());
            if (song != null) {
                mediaModel.setUrl(song.toURI().toString());
                mediaModel.getPlayer().play();
            }
        }
    }

    private class StatusListener implements InvalidationListener {
        @Override
        public void invalidated(Observable observable) {
            Platform.runLater(new Runnable() {
                @Override
                public void run() {
                    updateStatus(mediaModel.getPlayer().getStatus());
                }
            });
        }
    }

    private class CurrentTimeListener implements InvalidationListener {
        @Override
        public void invalidated(Observable observable) {
            Platform.runLater(new Runnable() {
                @Override
                public void run() {
                    final MediaPlayer mediaPlayer = mediaModel.getPlayer();
                    final Duration currentTime = mediaPlayer.getCurrentTime();
                    currentTimeLabel.setText(formatDuration(currentTime));
                    updatePositionSlider(currentTime);
                }
            });
        }
    }

    private class TotalDurationListener implements InvalidationListener {
        @Override
        public void invalidated(Observable observable) {
            final MediaPlayer mediaPlayer = mediaModel.getPlayer();
            final Duration totalDuration = mediaPlayer.getTotalDuration();
            totalDurationLabel.setText(formatDuration(totalDuration));
        }
    }

    private class PositionListener implements ChangeListener<Boolean> {
        @Override
        public void changed(ObservableValue<? extends Boolean> observable,
                            Boolean oldValue, Boolean newValue) {
            if (oldValue && !newValue) {
                double pos = positionSlider.getValue();
                final MediaPlayer mediaPlayer = mediaModel.getPlayer();
                final Duration seekTo = mediaPlayer.getTotalDuration().multiply(pos);
                seekAndUpdatePosition(seekTo);
            }
        }
    }
}