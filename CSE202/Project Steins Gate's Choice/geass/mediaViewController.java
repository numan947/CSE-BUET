package geass;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.input.Dragboard;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.TransferMode;
import javafx.scene.layout.StackPane;
import javafx.scene.media.MediaView;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

public class mediaViewController {
    CODE main;
    Stage tempControl=new Stage();

    public CODE getMain() {
        return main;
    }

    public void setMain(CODE main) {
        this.main = main;
    }

    boolean fullScreen=false;
    @FXML
    protected MediaView mediaView;

    @FXML
    private StackPane stackPane;

    void INITIALIZE()
    {
        tempControl.initStyle(StageStyle.UTILITY);
        mediaView.addEventFilter(MouseEvent.MOUSE_PRESSED,e->{
            if(e.getButton().equals(MouseButton.PRIMARY)){
                if(e.getClickCount()==2){
                    if(main.stage.isFullScreen()&&main.bp.getCenter()==mediaView){
                        main.stage.setFullScreen(false);
                        Platform.runLater(() -> {
                            int h= (int) main.stage.getHeight();
                            mediaView.setFitHeight(h-110);
                            System.out.println("IN MVC:: eventFilters");
                        });
                    }
                    else{
                        if(main.bp.getCenter()==mediaView) {
                            Platform.runLater(() -> {
                                int h = (int) main.stage.getHeight();
                                mediaView.setFitHeight(h - 80);
                                System.out.println("IN MVC::eventFilters");
                            });
                        }
                        main.stage.setFullScreen(true);
                    }
                }
            }
        });


    }

}