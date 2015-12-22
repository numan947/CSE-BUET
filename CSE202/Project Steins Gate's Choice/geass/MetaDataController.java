package geass;

/**
 * Created by numan947 on 2015-12-03.
 */

import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

/**It's the controller class of our metaDataview.
 *Each media's metaData has an AlbumCover, a Title, an Artist, an Album name & a Release Year
 *We just Binded these things with the corresponding properties wriiten in the MediaModel class
 *Double Clicking on the Album Cover, enlarges & shows cover in a different stage given that the media contains
 *a cover, otherwise, nothing happens
 */



public class MetaDataController {
    CODE main;

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
        Stage stage=new Stage();
        albumCover.setOnMouseClicked(click->{
            if(click.getClickCount()==2){
                if(albumCover.getImage()!=main.model.default_img) {
                    ImageView view = new ImageView(albumCover.getImage());
                    VBox box = new VBox();
                    box.getChildren().add(view);
                    stage.setScene(new Scene(box, view.getFitWidth(), view.getFitHeight()));
                    stage.show();
                }
            }
        });
    }

    void setMain(CODE main)
    {
        this.main=main;
    }
}
