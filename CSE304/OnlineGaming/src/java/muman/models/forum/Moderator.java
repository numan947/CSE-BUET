package forum;

/**
 * Created by numan947 on 12/18/16.
 **/
public class Moderator {

    private String userName;
    private String fullName;

    public Moderator( String userName, String fullName) {
        this.userName = userName;
        this.fullName = fullName;
    }



    public String getUserName() {
        return userName;
    }

    public String getFullName() {
        return fullName;
    }
}
