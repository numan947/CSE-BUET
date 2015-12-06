package geass;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;

public class MetaDataController {

    @FXML
    private ImageView albumCover;

    @FXML
    private Label mediaTitle;

    @FXML
    private Label mediaArtist;

    @FXML
    private Label mediaAlbum;

    @FXML
    private Label mediaYear;


    void INITIALIZE(MediaModel media)
    {
        albumCover.imageProperty().bind(media.albumCoverProperty());
        mediaAlbum.textProperty().bind(media.albumNameProperty());
        mediaArtist.textProperty().bind(media.artistNameProperty());
        mediaTitle.textProperty().bind(media.songTitleProperty());
        mediaYear.textProperty().bind(media.songYearProperty());
    }



}

