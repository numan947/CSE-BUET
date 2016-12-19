package muman.models.forum;

import java.sql.Date;

/**
 * Created by numan947 on 12/17/16.
 **/
public class PostReply {
    private String post_id;
    private String reply_id;
    private String replied_by;
    private Date date;
    private String content;
    private int rflag;

    public int getRflag() {
        return rflag;
    }

    public void setRflag(int rflag) {
        this.rflag = rflag;
    }

    public PostReply(String post_id, String reply_id, String replied_by, Date date, String content) {
        this.post_id = post_id;
        this.reply_id = reply_id;
        this.replied_by = replied_by;
        this.date = date;
        this.content = content;
    }

    public String getPost_id() {
        return post_id;
    }

    public void setPost_id(String post_id) {
        this.post_id = post_id;
    }

    public String getReply_id() {
        return reply_id;
    }

    public void setReply_id(String reply_id) {
        this.reply_id = reply_id;
    }

    public String getReplied_by() {
        return replied_by;
    }

    public void setReplied_by(String replied_by) {
        this.replied_by = replied_by;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }
    
    
    
    
}
