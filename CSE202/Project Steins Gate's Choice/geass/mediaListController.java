package geass;

import javafx.application.Platform;
import javafx.beans.value.ObservableListValue;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.media.Media;
import javafx.stage.DirectoryChooser;
import javafx.stage.FileChooser;

import java.io.*;
import java.util.Hashtable;
import java.util.List;
import java.util.StringTokenizer;

public class mediaListController {
    CODE main;
    int cnt,nowPlaying;
    PanelController panel;
    File playListDir=new File("Playlists");

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

    @FXML
    private Button clearButton;

    @FXML
    private Button appendBtn;

    @FXML
    private Button saveBtn;

    @FXML
    private Button opensaved;

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
        hashCol.setResizable(false);
        FileNameCol.setCellValueFactory(new PropertyValueFactory<mediaForList, String>("mediaName"));
        FileNameCol.setMinWidth(500);
        FileNameCol.setResizable(false);
        mediaList.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        cnt=0;
        mediaList.setOnMouseClicked(click->{
            if(click.getClickCount()==2){
                mediaForList selected=mediaList.getSelectionModel().getSelectedItem();
                nowPlaying=mediaList.getSelectionModel().getSelectedIndex();
                main.mediaName.setValue("NOW PLAYING "+selected.getMediaName());
                panel.setMediaModel(selected.getMediaFile().toURI().toString());
                Platform.runLater(()->{
                    mediaList.requestFocus();
                    mediaList.getFocusModel().focus(nowPlaying);
                    System.out.println("HI NOW "+nowPlaying);
                });
            }
        });

    }

    @FXML
    void ClearAction(ActionEvent event) {
        ObservableList<mediaForList>items=mediaList.getItems();
        if(items.size()!=0){
            items.clear();
            panel.mediaModel.getPlayer().stop();
            panel.removeAllListeners(panel.mediaModel.getPlayer());
            main.bp.setCenter(null);
            nowPlaying=-1;
            panel.DISABLEALL();
        }

    }


    @FXML
    void addMedia(ActionEvent event) {
        DirectoryChooser dc=new DirectoryChooser();
        File selectedDir=dc.showDialog(addButton.getScene().getWindow());

        if(selectedDir!=null){
            for(File f:selectedDir.listFiles()){
                if(!validated(f))continue;
                mediaForList mm = new mediaForList();
                mm.setMediaPos(Integer.toString(++cnt));
                mm.setMediaFile(f);
                mm.setMediaName(f.getName());
                mediaList.getItems().add(mm);
            }
            if (panel.mediaModel.getPlayer() == null||nowPlaying==-1) {
                ObservableList<mediaForList> items = mediaList.getItems();
                nowPlaying = 0;
                mediaForList nowMedia = items.get(nowPlaying);
                main.mediaName.setValue("NOW PLAYING" + " " + nowMedia.getMediaName());
                panel.setMediaModel(nowMedia.getMediaFile().toURI().toString());
                System.out.println("NOW PLAYING " + nowPlaying);

                Platform.runLater(()->{
                    mediaList.requestFocus();
                    mediaList.getFocusModel().focus(nowPlaying);
                });
            }
        }

    }


    @FXML
    void deleteMedia(ActionEvent event) {
        boolean ok=false;
        ObservableList<mediaForList>del=mediaList.getSelectionModel().getSelectedItems();
        for(mediaForList m:del) System.out.println(m.getMediaName());
        mediaForList NP=mediaList.getItems().get(nowPlaying);
        if(del.contains(NP))ok=true;


        mediaList.getItems().removeAll(del);
        ObservableList<mediaForList>items=mediaList.getItems();
        cnt=0;
        for(mediaForList t:items){
            t.setMediaPos(Integer.toString(++cnt));
        }
        if(items.size()!=0&&ok){
            panel.mediaList.getNOW();
        }

        if(mediaList.getItems().isEmpty()){
            panel.mediaModel.getPlayer().stop();
            panel.removeAllListeners(panel.mediaModel.getPlayer());
            main.bp.setCenter(null);
            nowPlaying=-1;
            panel.DISABLEALL();
        }

    }


    @FXML
    void SaveList(ActionEvent event) {
        if(!playListDir.exists())playListDir.mkdir();

        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().add(new FileChooser.ExtensionFilter("text Files","*.txt"));
        fc.setInitialDirectory(playListDir);

        File f=fc.showSaveDialog(saveBtn.getScene().getWindow());
        if(f!=null){
            SAVELIST(f);
        }

    }

    void SAVELIST(File f)
    {
        try {
            FileWriter fileWriter=new FileWriter(f);
            ObservableList<mediaForList>items=mediaList.getItems();
            for(mediaForList m:items){
                fileWriter.write(m.getMediaFile().getAbsolutePath()+"VICTORIQADEBLOIS");
            }
            fileWriter.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    @FXML
    void openSaved(ActionEvent event) {
        if(!playListDir.exists())playListDir.mkdir();
        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().add(new FileChooser.ExtensionFilter("textFiles","*.txt"));
        fc.setInitialDirectory(playListDir);
        File file=fc.showOpenDialog(opensaved.getScene().getWindow());
        if(file!=null)READLIST(file,1);
    }


    void READLIST(File file,int mode)
    {
        String ALLURLS="";
        BufferedReader bufferedReader=null;

        try {
            bufferedReader=new BufferedReader(new FileReader(file));
            String tmp;
            while((tmp=bufferedReader.readLine())!=null){
                ALLURLS+=tmp;
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        if(mode==1){
            ObservableList<mediaForList>items=mediaList.getItems();
            mediaList.getItems().clear();
            items.clear();
            cnt=0;
            String[]AllMedia=ALLURLS.split("VICTORIQADEBLOIS");

            for(String path:AllMedia){
                File f=new File(path);
                mediaForList mm = new mediaForList();
                mm.setMediaPos(Integer.toString(++cnt));
                mm.setMediaFile(f);
                mm.setMediaName(f.getName());
                mediaList.getItems().add(mm);
            }
            nowPlaying = 0;
            mediaForList nowMedia = items.get(nowPlaying);
            main.mediaName.setValue("NOW PLAYING" + " " + nowMedia.getMediaName());
            panel.setMediaModel(nowMedia.getMediaFile().toURI().toString());
            System.out.println("NOW PLAYING " + nowPlaying);

            Platform.runLater(()->{
                mediaList.requestFocus();
                mediaList.getFocusModel().focus(nowPlaying);
            });
        }

        else{
            ObservableList<mediaForList>items=mediaList.getItems();
            String[]AllMedia=ALLURLS.split("VICTORIQADEBLOIS");

            for(String path:AllMedia){
                File f=new File(path);
                mediaForList mm = new mediaForList();
                mm.setMediaPos(Integer.toString(++cnt));
                mm.setMediaFile(f);
                mm.setMediaName(f.getName());
                mediaList.getItems().add(mm);
            }
        }
    }


    @FXML
    void appendAction(ActionEvent event) {
        if(!playListDir.exists())playListDir.mkdir();

        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().add(new FileChooser.ExtensionFilter("textFiles","*.txt"));
        fc.setInitialDirectory(playListDir);

        File file=fc.showOpenDialog(opensaved.getScene().getWindow());
        if(file!=null)READLIST(file,2);

    }


    void getNext()
    {
        ObservableList<mediaForList>items=mediaList.getItems();
        nowPlaying++;
        int total=items.size();
        nowPlaying=((nowPlaying%total)+total)%total;
        mediaForList nowMedia=items.get(nowPlaying);
        panel.mediaName=nowMedia.getMediaName();
        main.mediaName.setValue("NOW PLAYING"+" "+nowMedia.getMediaName());

        panel.setMediaModel(nowMedia.getMediaFile().toURI().toString());
        System.out.println("NOW PLAYING "+nowPlaying);
        Platform.runLater(()->{
            mediaList.requestFocus();
            mediaList.getFocusModel().focus(nowPlaying);
        });
    }

    void getPrev()
    {
        ObservableList<mediaForList>items=mediaList.getItems();
        nowPlaying--;
        int total=items.size();
        nowPlaying=((nowPlaying%total)+total)%total;
        mediaForList nowMedia=items.get(nowPlaying);
        panel.mediaName=nowMedia.getMediaName();
        main.mediaName.setValue("NOW PLAYING"+" "+nowMedia.getMediaName());

        panel.setMediaModel(nowMedia.getMediaFile().toURI().toString());
        System.out.println("NOW PLAYING "+nowPlaying);
        Platform.runLater(()->{
            mediaList.requestFocus();
            mediaList.getFocusModel().focus(nowPlaying);
        });

    }
    void getNOW()
    {
        ObservableList<mediaForList>items=mediaList.getItems();

        int total=items.size();
        nowPlaying=((nowPlaying%total)+total)%total;
        mediaForList nowMedia=items.get(nowPlaying);
        panel.mediaName=nowMedia.getMediaName();
        main.mediaName.setValue("NOW PLAYING"+" "+nowMedia.getMediaName());

        panel.setMediaModel(nowMedia.getMediaFile().toURI().toString());
        System.out.println("NOW PLAYING "+nowPlaying);

        Platform.runLater(()->{
            mediaList.requestFocus();
            mediaList.getFocusModel().focus(nowPlaying);
        });


    }

    boolean validated(File f)
    {
        String url=f.getAbsolutePath();
        String ft=url.substring(url.lastIndexOf('.')+1);
        return ft.equals("MP4") || ft.equals("mp4") || ft.equals("mp3") || ft.equals("MP3");
    }

}
