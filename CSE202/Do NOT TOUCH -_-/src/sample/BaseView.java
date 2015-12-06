package sample;

import javafx.scene.Node;

/**
 * Created by numan947 on 2015-12-03.
 */
public abstract class BaseView {
    protected final MediaModel mediaModel;
    protected final Node viewNode;

    public BaseView(MediaModel mediaModel)
    {
        this.mediaModel=mediaModel;
        viewNode=initializeNode();
    }
    public Node getViewNode()
    {
        return this.viewNode;
    }

    public abstract javafx.scene.Node initializeNode();
}
