package geass;


import javafx.beans.property.*;
import javafx.collections.MapChangeListener;
import javafx.scene.image.Image;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

/**
 * Created by numan947 on 2015-12-03.
 */
public class MediaModel {

    private final String default_img_url=getClass().getResource("326271.png").toString();

    private final Image default_img=new Image(default_img_url);

    private final StringProperty albumName=new SimpleStringProperty(this,"album");
    private final StringProperty artistName=new SimpleStringProperty(this,"artist");
    private final StringProperty songTitle=new SimpleStringProperty(this,"title");
    private final StringProperty songYear=new SimpleStringProperty(this,"year");

    private final ObjectProperty<Image>albumCover=new SimpleObjectProperty<>(this,"cover");

    private final ReadOnlyObjectWrapper<MediaPlayer> player=new ReadOnlyObjectWrapper<>(this,"mediaPlayer");

/**********RESETS THE BASIC PROPERTIES**************/
    void resetProperties()
    {
        this.artistName.setValue("Artist: Unknown");
        this.albumName.setValue("Album: Unknown");
        this.songTitle.setValue("Title: Unknown");
        this.songYear.setValue("Year: Unknown");
        this.albumCover.setValue(default_img);
    }



    /*************PROPERY**************/
    public MediaModel()
    {
        resetProperties();
    }

    public String getAlbumName() {
        return albumName.get();
    }

    public StringProperty albumNameProperty() {
        return albumName;
    }

    public void setAlbumName(String albumName) {
        this.albumName.set(albumName);
    }

    public String getArtistName() {
        return artistName.get();
    }

    public StringProperty artistNameProperty() {
        return artistName;
    }

    public void setArtistName(String artistName) {
        this.artistName.set(artistName);
    }

    public String getSongTitle() {
        return songTitle.get();
    }

    public StringProperty songTitleProperty() {
        return songTitle;
    }

    public void setSongTitle(String songTitle) {
        this.songTitle.set(songTitle);
    }

    public String getSongYear() {
        return songYear.get();
    }

    public StringProperty songYearProperty() {
        return songYear;
    }

    public void setSongYear(String songYear) {
        this.songYear.set(songYear);
    }

    public Image getAlbumCover() {
        return albumCover.get();
    }

    public ObjectProperty<Image> albumCoverProperty() {
        return albumCover;
    }

    public void setAlbumCover(Image albumCover) {
        this.albumCover.set(albumCover);
    }

    public MediaPlayer getPlayer() {
        return player.get();
    }

    public ReadOnlyObjectWrapper<MediaPlayer> playerProperty() {
        return player;
    }

    public void setPlayer(MediaPlayer player) {
        this.player.set(player);
    }



    /***************INITIALIZES THE MAIN MEDIA**************/
    public void initMedia(String url)
    {
        resetProperties();

        try{
            Media media=new Media(url);

            media.getMetadata().addListener((MapChangeListener<String, Object>) change -> {
                if (change.wasAdded()) {
                    setMetaData(change.getKey(),change.getValueAdded());
                }
            });
            this.player.setValue(new MediaPlayer(media));

            player.get().setOnError(()->{
                System.out.println(player.get().getError().getMessage());
            });

        }catch (Exception e){
            System.out.println("ERROR AT INIT MEDIA "+e);
        }
    }

    /**************FILLS UP THE LIST FROM METADATA***************/
    void setMetaData(String key,Object Value)
    {
        switch (key){
            case "album":
                setAlbumName("Album: "+Value.toString());
                break;
            case "artist":
                setArtistName("Artist: "+Value.toString());
                break;
            case "title":
                setSongTitle("Title: "+Value.toString());
                break;
            case "year":
                setSongYear("Year: "+Value.toString());
                break;
            case "image":
                setAlbumCover((Image) Value);
                break;
        }
    }


    void setUrl(String url)
    {

        if(player.get()!=null)player.get().stop();
        System.out.println(url);
        initMedia(url);
    }
}
