package geass;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.media.MediaView;

/**Controller for our MediaView which contains the mediaView
 * Double clicking on the mediaView makes the primary stage fullscreen & vice versa depending on the current stage status
 * It also handles the size of the mediaview using platform.Runlater
 * It also binds mediaview's widthproperty with mainscene's widthproperty
 */

public class mediaViewController {
    CODE main;

    public CODE getMain() {
        return main;
    }

    public void setMain(CODE main) {
        this.main = main;
    }

    @FXML
    protected MediaView mediaView;


    void INITIALIZE()
    {
        mediaView.fitWidthProperty().bind(main.mainScene.widthProperty());
        mediaView.setPreserveRatio(false);
        mediaView.addEventFilter(MouseEvent.MOUSE_PRESSED, e -> {
            if (e.getButton().equals(MouseButton.PRIMARY)) {
                if (e.getClickCount() == 2) {
                    if (main.stage.isFullScreen() && main.bp.getCenter() == mediaView) {
                        main.stage.setFullScreen(false);
                        /**
                         * The code snippet below, resizes the mediaview once gone in fullScreen mode or vice versa, as the
                         * size of mediaView can't be changed from javafx's thread, we used Platform.Runlater to complete this task
                         * as a part of javafx application thread, as it's just some simple logic code, it doesn't BLOCK javafx's application thread
                         */
                        Platform.runLater(() -> {
                            int h = (int) main.stage.getHeight();
                            mediaView.setFitHeight(h - 110);
                            System.out.println("IN MVC:: eventFilters");
                        });
                    } else {
                        if (main.bp.getCenter() == mediaView) {
                            /**
                             * The code snippet below, resizes the mediaview once gone in fullScreen mode or vice versa, as the
                             * size of mediaView can't be changed from javafx's thread, we used Platform.Runlater to complete this task
                             * as a part of javafx application thread, as it's just some simple logic code, it doesn't BLOCK javafx's application thread
                             */
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
