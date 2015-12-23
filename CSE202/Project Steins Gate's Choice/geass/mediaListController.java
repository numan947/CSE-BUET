package geass;

import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.DirectoryChooser;
import javafx.stage.FileChooser;

import java.io.*;
import java.net.URL;
import java.net.URLDecoder;

/**This is the controller class for our Playlist.
 * cnt & nowplaying tracks the number of elements corrently in the list & the current song number
 *correspondingly.
 *playListDir is the default directory where playlists are saved and saved playlists are reloaded from
 *Other Functions' functionalities are described just before the declaration of the functions
 */



public class mediaListController {
    CODE main;
    int cnt,nowPlaying;
    PanelController panel;
    File playListDir;

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


    /**INITIALIZE function initializes the table coloumns, sets the selection model for TableView
     *initializes mouse click action, which is, double clicking on an item in the playlist, starts playing that media
     */
     void INITIALIZE()
    {
        URL url = CODE.class.getProtectionDomain().getCodeSource().getLocation();
        String jarPath = null;
        try {
            jarPath = URLDecoder.decode(url.getFile(), "UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        String parentPath = new File(jarPath).getParentFile().getPath();
        String separator=System.getProperty("file.separator");
        playListDir=new File(parentPath+separator+"Playlists"+separator);



        hashCol.setCellValueFactory(new PropertyValueFactory<mediaForList,String>("mediaPos"));
        hashCol.setResizable(false);
        FileNameCol.setCellValueFactory(new PropertyValueFactory<mediaForList, String>("mediaName"));
        FileNameCol.setMinWidth(400);
        FileNameCol.setResizable(false);
        mediaList.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        cnt=0;
        mediaList.setOnMouseClicked(click->{
            if(click.getClickCount()==2){
                mediaForList selected=mediaList.getSelectionModel().getSelectedItem();
                nowPlaying=mediaList.getSelectionModel().getSelectedIndex();
                main.mediaName.setValue("NOW PLAYING "+selected.getMediaName());
                panel.setMediaModel(selected.getMediaFile().toURI().toString());
                panel.mediaName=selected.getMediaName();
                Platform.runLater(()->{
                    mediaList.requestFocus();
                    mediaList.getFocusModel().focus(nowPlaying);
                    //System.out.println("HI NOW "+nowPlaying);
                });
            }
        });
    }

    /**clears the playlist and removes all listeners from the mediaplayer
     *sets the main view with defaultview
     **/
    @FXML
    void ClearAction(ActionEvent event) {
        ObservableList<mediaForList>items=mediaList.getItems();
        if(items.size()!=0){
            items.clear();
            cnt=0;
            panel.mediaModel.getPlayer().stop();
            panel.StatusLabel.setText("READY");
            panel.removeAllListeners(panel.mediaModel.getPlayer());
            main.bp.setCenter(main.def);
            main.mediaName.setValue("MK Player :)");
            nowPlaying=-1;
            panel.DISABLEALL();
        }

    }

    /**addMedia function loads all mediafiles(mp3,mp4) from the chosen directory
     *before adding media in the playlist, it verifies if it is of mp3/mp4 format
     *if the playlist is empty then, it starts playing the first media from the playlist
     */
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
                panel.mediaName=nowMedia.getMediaName();
                //System.out.println("NOW PLAYING " + nowPlaying);

                /**the code snippet in below
                 *sets the default focus of
                 *the tableview(playlist) to
                 *currently playing media
                 */
                Platform.runLater(()->{
                    mediaList.requestFocus();
                    mediaList.getFocusModel().focus(nowPlaying);
                });
            }
        }

    }

    /**deleteMedia function deletes the selected items from the playlist
     *if the currently playing media is deleted then the next media is automatically selected and starts playing
     *if all the items in the list are deleted, then the function works as ClearAction function mentioned above
     */

    @FXML
    void deleteMedia(ActionEvent event) {
        boolean ok=false;
        ObservableList<mediaForList>del=mediaList.getSelectionModel().getSelectedItems();
        //for(mediaForList m:del) System.out.println(m.getMediaName());
        mediaForList NP=mediaList.getItems().get(nowPlaying);
        if(del.contains(NP))ok=true;


        mediaList.getItems().removeAll(del);
        ObservableList<mediaForList>items=mediaList.getItems();
        cnt=0;
        for(mediaForList t:items){
            t.setMediaPos(Integer.toString(++cnt));
        }
        if(items.size()!=0&&ok){
            getNOW();
        }

        if(mediaList.getItems().isEmpty()){
            panel.mediaModel.getPlayer().stop();
            panel.removeAllListeners(panel.mediaModel.getPlayer());
            main.bp.setCenter(main.def);
            main.mediaName.setValue("MK Player :)");
            nowPlaying=-1;
            panel.DISABLEALL();
            panel.StatusLabel.setText("READY");
        }

    }

    /**SaveList function saves the current playlist in the default directory, if the directory doesn't exist
     *then it's remade and selected as default directory
     */

    @FXML
    void SaveList(ActionEvent event) {
        if(!playListDir.exists())playListDir.mkdir();

        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().add(new FileChooser.ExtensionFilter("playlist","*.txt"));
        fc.setInitialDirectory(playListDir);

        File f=fc.showSaveDialog(saveBtn.getScene().getWindow());
        if(f!=null){
            SAVELIST(f);
        }
    }

    /**SAVELIST function does the saving of playlist. It saves the media files' urls with splitter
     *String "VICTORIQADEBLOIS"
     */

    void SAVELIST(File f)
    {
        BufferedWriter out=null;
        try {
            out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(f), "UTF-8"));

            ObservableList<mediaForList>items=mediaList.getItems();
            for(mediaForList m:items){
                out.write(m.getMediaFile().getAbsolutePath() + "VICTORIQADEBLOIS");
            }
            out.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**openSaved function opens a saved playlist, the initial directory is selected as Playlist, if
     *it doesn't exist, then it's made and seleced as initial directory
     */
    @FXML
    void openSaved(ActionEvent event) {
        if(!playListDir.exists())playListDir.mkdir();
        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().add(new FileChooser.ExtensionFilter("playlist","*.txt"));
        fc.setInitialDirectory(playListDir);
        File file=fc.showOpenDialog(opensaved.getScene().getWindow());
        if(file!=null)READLIST(file,1);
    }
    /**READLIST function does the reading from text fiels, it has two variables, a File, from which data needs to
     *be read and a mode. Mode variable decides whether the data read is appended to the list(mode!=1) or the list contains
     *only the data from the selected file(mode==1)
     */
    void READLIST(File file,int mode)
    {
        String ALLURLS="";
        BufferedReader bufferedReader=null;

        try {
            bufferedReader = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8"));
            String tmp;
            while((tmp=bufferedReader.readLine())!=null){
                ALLURLS+=tmp;
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        ObservableList<mediaForList>items=mediaList.getItems();
        String[]AllMedia=ALLURLS.split("VICTORIQADEBLOIS");

        if(mode==1){
            mediaList.getItems().clear();
            cnt=0;
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
            panel.mediaName=nowMedia.getMediaName();
            panel.setMediaModel(nowMedia.getMediaFile().toURI().toString());
            //System.out.println("NOW PLAYING " + nowPlaying);

            /**the code snippet in below
             *sets the default focus of
             *the tableview(playlist) to
             *currently playing media
             */

            Platform.runLater(()->{
                mediaList.requestFocus();
                mediaList.getFocusModel().focus(nowPlaying);
            });
        }

        else{
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

    /**appendAction function appends medias from the selcted playlist to the
     *current playlist
     */

    @FXML
    void appendAction(ActionEvent event) {
        if(!playListDir.exists())playListDir.mkdir();

        FileChooser fc=new FileChooser();
        fc.getExtensionFilters().add(new FileChooser.ExtensionFilter("textFiles","*.txt"));
        fc.setInitialDirectory(playListDir);

        File file=fc.showOpenDialog(opensaved.getScene().getWindow());
        if(file!=null)READLIST(file,2);

    }

    /**plays the next mediafile from the playlist
     */

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


        //System.out.println("NOW PLAYING "+nowPlaying);
        /**the code snippet in below
         *sets the default focus of
         *the tableview(playlist) to
         *currently playing media
         */
        Platform.runLater(()->{
            mediaList.requestFocus();
            mediaList.getFocusModel().focus(nowPlaying);
        });
    }

    /**Plays the previous mediafile from the playlist
    */
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


        //System.out.println("NOW PLAYING "+nowPlaying);
        /**the code snippet in below
         *sets the default focus of
         *the tableview(playlist) to
         *currently playing media
         */
        Platform.runLater(()->{
            mediaList.requestFocus();
            mediaList.getFocusModel().focus(nowPlaying);
        });

    }

    /**plays the currently playing mediafile from the list (in case of repeating the file)
    */
    void getNOW()
    {
        ObservableList<mediaForList>items=mediaList.getItems();

        int total=items.size();
        nowPlaying=((nowPlaying%total)+total)%total;
        mediaForList nowMedia=items.get(nowPlaying);
        panel.mediaName=nowMedia.getMediaName();
        main.mediaName.setValue("NOW PLAYING"+" "+nowMedia.getMediaName());
        panel.setMediaModel(nowMedia.getMediaFile().toURI().toString());


        //System.out.println("NOW PLAYING "+nowPlaying);
        /**the code snippet in below
         *sets the default focus of
         *the tableview(playlist) to
         *currently playing media
         */
        Platform.runLater(()->{
            mediaList.requestFocus();
            mediaList.getFocusModel().focus(nowPlaying);
        });


    }
    /**Validates the file type of the file f*/

    boolean validated(File f)
    {
        String url=f.getAbsolutePath();
        String ft=url.substring(url.lastIndexOf('.')+1);
        return ft.equals("MP4") || ft.equals("mp4") || ft.equals("mp3") || ft.equals("MP3");
    }

}
