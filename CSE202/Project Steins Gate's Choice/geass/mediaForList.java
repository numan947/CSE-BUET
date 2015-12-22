package geass;

import java.io.File;


/**Basically it is The media file. It stores each media as file
 *with it's name & it's position in the table view
 *It's used for supporting positioning in the tableview
 */

public class mediaForList {
    File mediaFile;
    String mediaName;
    String mediaPos;

    public File getMediaFile() {
        return mediaFile;
    }

    public void setMediaFile(File mediaFile) {
        this.mediaFile = mediaFile;
    }

    public String getMediaName() {
        return mediaName;
    }

    public void setMediaName(String mediaName) {
        this.mediaName = mediaName;
    }

    public String getMediaPos() {
        return mediaPos;
    }

    public void setMediaPos(String mediaPos) {
        this.mediaPos = mediaPos;
    }
}
