/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package muman.db;

import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import javax.servlet.http.HttpSession;
import muman.models.Match;
import muman.models.UserInfo;
import muman.models.forum.ForumPost;
import muman.models.forum.PostReply;

/**
 *
 * @author samsung
 */
public class DataAccess 
{
    String dbURL = "jdbc:oracle:thin:@localhost:1521:ORCL";
    String username = "mamun";
    String password = "mamun";

    Connection conn = null;
    public DataAccess()
    {
      
        try
        {
            Class.forName("oracle.jdbc.OracleDriver");
            conn = DriverManager.getConnection(dbURL, username, password);
            if(conn!=null) System.out.println("Connection successfully established.");
            else System.out.println("Could not establish connection");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
   
    public int createAccount(String username, String user_full_name, String password, 
            String email, String birth_date, String region)
    {
        try
        {
            String insertCommand = "{ ? = call INSERT_USER(?,?,?,?,?,?) }";
            CallableStatement stmt =  conn.prepareCall(insertCommand);
            stmt.setString(2, username);
            stmt.setString(3, user_full_name);
            stmt.setString(4, password);
            stmt.setString(5, email);
            stmt.setString(6, birth_date);
            stmt.setString(7,region);
            
            stmt.registerOutParameter(1, java.sql.Types.INTEGER);  
            stmt.execute();
            
            int id = (int) stmt.getLong(1);
            return id;
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return 0;
        }
        
        
        
    }
    
   
    public boolean existUser(String username,String password)
    {
        try
        {
            String query = "select * from user_table where username = ? and password = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, username);
            stmt.setString(2, password);
            ResultSet rs = stmt.executeQuery();
            if(rs!=null && rs.next())
            {
                return true;
            }
            return false;
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return false;
        }
        
    }
    
    
    
    public UserInfo getUser(String username){
        try
        {
            String query = "select user_full_name, email, register_date,"
                    + "birth_date, region from user_table where username = ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, username);
         
            ResultSet rs = stmt.executeQuery();
            
            if(rs!=null && rs.next())
            {
      
                String user_full_name = rs.getString("user_full_name");
                String email = rs.getString("email");
                String register_date = rs.getString("register_date");
                String birth_date = rs.getString("birth_date");
                String region = rs.getString("region");
                return new UserInfo(username, user_full_name, email, register_date, birth_date, region);
            }
            return null;
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return null;
        }
    }
    
    public String getRandomPlayer(String player1){  ///eventually this will be retrieved from player table
        
         try
        {
            String query = "select username from user_table where username <> ?";
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, player1);
         
            ResultSet rs = stmt.executeQuery();
            
            ArrayList<String> players = new ArrayList<>();
            
            while(rs.next())
            {
      
                String user= rs.getString("username");
                players.add(user);
           
            }
            if(players.size()==0) return null;
            return players.get((int) System.currentTimeMillis()%players.size());
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return null;
        }
    }

    public Match addMatch(String player1, String player2) {
       
    try{
        String sql = "{ ? = call INSERT_MATCH(?,?) }";
        CallableStatement statement = conn.prepareCall(sql);
        statement.setString(2,player1);
        statement.setString(3,player2);
        statement.registerOutParameter(1, java.sql.Types.INTEGER);  

        statement.execute();   
    //this is the main line
    int id =(int) statement.getLong(1);
    
    if (id > 0) {
        return new Match(id, player1, player2);
    } else {
        return null;
    }
    }
        catch(SQLException e){
               return null;
        }
      
    }

    public void updateMatch(Match match, int score1, int score2) {
        String sql = "{ call UPDATE_MATCH(?,?,?,?,?) }";
        try{
        CallableStatement statement = conn.prepareCall(sql);
        statement.setInt(1,match.getId());
        statement.setString(2,match.getPlayer1());
        statement.setInt(3,score1);
        statement.setString(4,match.getPlayer2());
        statement.setInt(5,score2);



        statement.execute();   
        }
        catch(SQLException e){
        }
    }
    
     public ForumPost getThePost(String post_id){
        try
        {
            String query = "SELECT POST_TITLE,POST_ID,POST_CONTENT,POST_DATE,USERNAME,SECTION_NAME FROM\n" +
                "USER_TABLE\n" +
                "JOIN FORUM_POST_TABLE\n" +
                "ON(USER_TABLE.USER_ID=FORUM_POST_TABLE.POSTED_BY_ID)\n" +
                "JOIN SECTION_TABLE\n" +
                "ON(SECTION_TABLE.SECTION_ID=FORUM_POST_TABLE.SECTION_ID)"
                    + "WHERE POST_ID=?";
            
             PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, post_id);
         
            ResultSet rs = stmt.executeQuery();
            
            if(rs.next())
            {
      
                String title = rs.getString("post_title");
                String id = rs.getString("post_id");
                String content = rs.getString("post_content");
                Date date = rs.getDate("post_date");
                String postedby = rs.getString("username");
                String section = rs.getString("section_name");
                ForumPost post =  new ForumPost(title, id, content, date, postedby, section);
                post.setPflag(getPostFlag(post_id));
                
                 System.out.println(post.getPflag());
                
                return post;
            }
            return null;
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return null;
        }
    }
     
     public ArrayList<ForumPost> getPostList(){
         
         try
        {
            String query = "SELECT POST_TITLE,POST_ID,POST_CONTENT,POST_DATE,USERNAME,SECTION_NAME FROM\n" +
                "USER_TABLE\n" +
                "JOIN FORUM_POST_TABLE\n" +
                "ON(USER_TABLE.USER_ID=FORUM_POST_TABLE.POSTED_BY_ID)\n" +
                "JOIN SECTION_TABLE\n" +
                "ON(SECTION_TABLE.SECTION_ID=FORUM_POST_TABLE.SECTION_ID)";
            
            PreparedStatement stmt = conn.prepareStatement(query);
         
            ResultSet rs = stmt.executeQuery();
            ArrayList<ForumPost> posts = new ArrayList<>();
            
            while(rs.next())
            {
      
                String title = rs.getString("post_title");
                String id = rs.getString("post_id");
                String content = rs.getString("post_content");
                Date date = rs.getDate("post_date");
                String postedby = rs.getString("username");
                String section = rs.getString("section_name");
                posts.add(new ForumPost(title, id, content, date, postedby, section));
                System.out.println(posts.size());
            }
            return posts;
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return null;
        }
         
         
     }
     
     public ArrayList<String> getSections(){
         
         try
        {
            String query = "SELECT SECTION_NAME"
                    + " FROM SECTION_TABLE";
            
            PreparedStatement stmt = conn.prepareStatement(query);
         
            ResultSet rs = stmt.executeQuery();
            ArrayList<String> sections = new ArrayList<>();
            
            while(rs.next())
            {
      
                String section = rs.getString("section_name");
               
                sections.add(section);
               // System.out.println(posts.size());
            }
            return sections;
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return null;
        }
         
         
     }
    
     
     public int insertForumPost(String title, String content, String section, String posted_by) {
       
    try{
        String sql = "{ ? = call INSERT_FORUM_POST(?,?,?,?) }";
        CallableStatement statement = conn.prepareCall(sql);
        statement.setString(2,title);
        statement.setString(3,content);
        statement.setString(4,section);
        statement.setString(5,posted_by);
        
        statement.registerOutParameter(1, java.sql.Types.INTEGER);  

        statement.execute();   
    //this is the main line
    int id =(int) statement.getLong(1);
    
    return id;
    
    }
        catch(SQLException e){
               return 0;
        }
      
    }
     
      public int insertForumReply(String post_id, String replyd_by,String content) {
       
    try{
        String sql = "{ ? = call INSERT_FORUM_REPLY(?,?,?) }";
        CallableStatement statement = conn.prepareCall(sql);
        statement.setString(2,post_id);
        statement.setString(3,replyd_by);
        statement.setString(4,content);
        
        statement.registerOutParameter(1, java.sql.Types.INTEGER);  

        statement.execute();   
    //this is the main line
    int id =(int) statement.getLong(1);
    
    return id;
    
    }
        catch(SQLException e){
               return 0;
        }
      
    }
    
    
     public ArrayList<PostReply> getReplyList(String post_id){
         
         try
        {
            String query = "SELECT POST_ID,REPLY_ID,USERNAME,REPLY_DATE,REPLY_CONTENT FROM\n" +
                "USER_TABLE\n" +
                "JOIN FORUM_REPLY_TABLE\n" +
                "ON(USER_TABLE.USER_ID=FORUM_REPLY_TABLE.REPLIED_BY)"
                    + "WHERE POST_ID = ?";
            
            PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, post_id);
         
            ResultSet rs = stmt.executeQuery();
            ArrayList<PostReply> replies = new ArrayList<>();
            
            while(rs.next())
            {
                String reply_id = rs.getString("reply_id");
                String replied_by = rs.getString("username");
                Date date = rs.getDate("reply_date");
                String content = rs.getString("reply_content");
                
                PostReply reply = new PostReply(post_id, reply_id, replied_by, date, content);
                reply.setRflag(getReplyFlag(post_id, reply_id));
               
                System.out.println(reply.getRflag());
               
                replies.add(reply);
                //System.out.println(replies.size());
            }
            return replies;
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return null;
        }
         
         
     }

    public void flagPost(String post_id, String username) {
        String sql = "{ call FLAG_POST(?,?) }";
        try{
        CallableStatement statement = conn.prepareCall(sql);
        statement.setInt(1,Integer.parseInt(post_id));
        statement.setString(2,username);



        statement.execute();   
        }
        catch(SQLException e){
        }
    }

    public void flagReply(String post_id, String reply_id, String username) {
        String sql = "{ call FLAG_REPLY(?,?,?) }";
        try{
        CallableStatement statement = conn.prepareCall(sql);
        statement.setInt(1,Integer.parseInt(post_id));
        statement.setInt(2, Integer.parseInt(reply_id));
        statement.setString(3,username);



        statement.execute();   
        }
        catch(SQLException e){
        }
    }

    public int getPostFlag(String post_id) {
         try
        {
            String query = "SELECT COUNT(*) TOTAL "
                    + "FROM POST_FLAG_TABLE "
                    + "WHERE POST_ID=? ";
            
             PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, post_id);
         
            ResultSet rs = stmt.executeQuery();
            
            if(rs.next())
            {
                int count = rs.getInt("TOTAL");
                return count;
            }
            return 0;
        }
        catch(Exception e)
        {
            return 0;
        }
    }
    
    public int getReplyFlag(String post_id, String reply_id) {
         try
        {
            String query = "SELECT COUNT(*) TOTAL "
                    + "FROM REPLY_FLAG_TABLE "
                    + "WHERE POST_ID=? AND REPLY_ID=? ";
            
             PreparedStatement stmt = conn.prepareStatement(query);
            stmt.setString(1, post_id);
            stmt.setString(2, reply_id);
         
            ResultSet rs = stmt.executeQuery();
            
            if(rs.next())
            {
                int count = rs.getInt("TOTAL");
                return count;
            }
            return 0;
        }
        catch(Exception e)
        {
            return 0;
        }
    }
   
    
}
