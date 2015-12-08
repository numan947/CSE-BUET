package geass;

import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.media.Media;
import javafx.stage.FileChooser;

import java.io.File;
import java.util.Hashtable;
import java.util.List;

public class mediaListController {
    CODE main;
    int cnt,nowPlaying;
    PanelController panel;

    public PanelController getPanel() {
        return panel;
    }

    public void setPanel(PanelController panel) {
        this.panel = panel;
    }

    public CODE getMain() {
        return main;
    }

    public void setMain(CODE main) {
        this.main = main;
    }


    Hashtable<String,File>playlist=new Hashtable<>();



    @FXML
    private Button addButton;

    @FXML
    private Button deleteButton;

    @FXML
    protected TableView<mediaForList> mediaList;

    @FXML
    private TableColumn<mediaForList, String> hashCol;

    @FXML
    private TableColumn<mediaForList, String > FileNameCol;

    void INITIALIZE()//sets the tablecoloumns value factory :p and other important things ;)
    {
        hashCol.setCellValueFactory(new PropertyValueFactory<mediaForList,String>("mediaPos"));
        FileNameCol.setCellValueFactory(new PropertyValueFactory<mediaForList, String>("mediaName"));
        mediaList.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        cnt=0;
        mediaList.setOnMouseClicked(click->{
            if(click.getClickCount()==2){
                mediaForList selected=mediaList.getSelectionModel().getSelectedItem();
                nowPlaying=mediaList.getSelectionModel().getSelectedIndex();
                main.mediaName.setValue("NOW PLAYING "+selected.getMediaName());
                panel.setMediaModel(selected.getMediaFile().toURI().toString());
            }
        });

    }



    @FXML
    void addMedia(ActionEvent event) {

        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().add(new FileChooser.ExtensionFilter("AudioFiles","*.mp3"));
        List<File>lst=fc.showOpenMultipleDialog(main.stage);
        if(lst!=null) {

            for (File f : lst) {
                mediaForList mm = new mediaForList();
                mm.setMediaPos(Integer.toString(++cnt));
                mm.setMediaFile(f);
                mm.setMediaName(f.getName());
                mediaList.getItems().add(mm);
            }

            if (panel.mediaModel.getPlayer() == null) {
                ObservableList<mediaForList> items = mediaList.getItems();
                nowPlaying = 0;
                mediaForList nowMedia = items.get(nowPlaying);
                main.mediaName.setValue("NOW PLAYING" + " " + nowMedia.getMediaName());
                panel.setMediaModel(nowMedia.getMediaFile().toURI().toString());
                System.out.println("NOW PLAYING " + nowPlaying);
            }
        }
    }


    @FXML
    void deleteMedia(ActionEvent event) {
        Media NP=panel.mediaModel.getPlayer().getMedia();
        ObservableList<mediaForList>del=mediaList.getSelectionModel().getSelectedItems();
        mediaList.getItems().removeAll(del);
        ObservableList<mediaForList>items=mediaList.getItems();
        cnt=0;
        for(mediaForList t:items){
            t.setMediaPos(Integer.toString(++cnt));
        }
        if(mediaList.getItems().isEmpty()){
            panel.DISABLEALL();
        }

    }

    void getNext()
    {
        ObservableList<mediaForList>items=mediaList.getItems();
        nowPlaying++;
        int total=items.size();
        nowPlaying=((nowPlaying%total)+total)%total;
        mediaForList nowMedia=items.get(nowPlaying);
        main.mediaName.setValue("NOW PLAYING"+" "+nowMedia.getMediaName());

        panel.setMediaModel(nowMedia.getMediaFile().toURI().toString());
        System.out.println("NOW PLAYING "+nowPlaying);
    }

    void getPrev()
    {
        ObservableList<mediaForList>items=mediaList.getItems();
        nowPlaying--;
        int total=items.size();
        nowPlaying=((nowPlaying%total)+total)%total;
        mediaForList nowMedia=items.get(nowPlaying);
        main.mediaName.setValue("NOW PLAYING"+" "+nowMedia.getMediaName());

        panel.setMediaModel(nowMedia.getMediaFile().toURI().toString());
        System.out.println("NOW PLAYING "+nowPlaying);
    }


}
