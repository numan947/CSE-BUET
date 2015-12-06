package sample;

import com.sun.javafx.runtime.VersionInfo;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.input.DragEvent;
import javafx.scene.input.Dragboard;
import javafx.scene.input.TransferMode;
import javafx.scene.layout.BorderPane;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;
import javafx.stage.Stage;

import java.net.URL;
import java.nio.file.Paths;

public class Main extends Application {
    private  MediaModel mediaModel;

    private MetadataView metaDataView;
    private PlayerControlsView playerControlsView;

    public static void main(String[] args) {
        launch(args);
    }



    @Override
    public void start(Stage primaryStage) {
        System.out.println("JavaFX version: "+VersionInfo.getRuntimeVersion());
        String path= Paths.get("F:/JAVA/abcd/src/dhur/Maya-Blue Jeans.mp3").toUri().toString();
        mediaModel=new MediaModel();
        //mediaModel.setUrl(path);
        metaDataView = new MetadataView(mediaModel);
        //playerControlsView = new PlayerControlsView(mediaModel);

        final BorderPane root = new BorderPane();
        root.setCenter(metaDataView.getViewNode());
        //root.setBottom(playerControlsView.getViewNode());

        final Scene scene = new Scene(root, 800, 400);
        initSceneDragAndDrop(scene);

        //final URL stylesheet = getClass().getResource("media.css");
        //scene.getStylesheets().add(stylesheet.toString());

        primaryStage.setScene(scene);
        primaryStage.setTitle("Audio Player 3");
        primaryStage.show();
    }

    private void initSceneDragAndDrop(Scene scene) {
        scene.setOnDragOver(new EventHandler<DragEvent>() {
            @Override
            public void handle(DragEvent event) {
                Dragboard db = event.getDragboard();
                if (db.hasFiles() || db.hasUrl()) {
                    event.acceptTransferModes(TransferMode.ANY);
                }
                event.consume();
            }
        });

        scene.setOnDragDropped(event -> {
            Dragboard db = event.getDragboard();
            String url = null;

            if (db.hasFiles()) {
                url = db.getFiles().get(0).toURI().toString();
            } else if (db.hasUrl()) {
                url = db.getUrl();
            }

            if (url != null) {
                mediaModel.setUrl(url);
                mediaModel.getPlayer().play();
            }

            event.setDropCompleted(url != null);
            event.consume();
        });
    }
}