package muman.models.forum;

import java.sql.Date;

/**
 * Created by numan947 on 12/17/16.
 **/
public class ForumPost {
    private String title;
    private String id;
    private String content;
    private Date date;
    private String posted_by;
    private String section;
    private int pflag;

    public int getPflag() {
        return pflag;
    }

    public void setPflag(int pflag) {
        this.pflag = pflag;
    }
    
    public ForumPost(String title, String id, String content, Date date, String posted_by, String section) {
        this.title = title;
        this.id = id;
        this.content = content;
        this.date = date;
        this.posted_by = posted_by;
        this.section = section;
    }

    public String getTitle() {
        return title;
    }

    public String getId() {
        return id;
    }

    public String getContent() {
        return content;
    }

    public Date getDate() {
        return date;
    }

    public String getPosted_by() {
        return posted_by;
    }

    public String getSection() {
        return section;
    }
}
