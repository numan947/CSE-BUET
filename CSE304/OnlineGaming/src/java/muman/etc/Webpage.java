/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package muman.etc;
/**
 *
 * @author ab9ma
 */
public class Webpage {
    public final static String login = "index.jsp";
    public final static String logout = "logout.jsp";
    public final static String signup = "createAccount.jsp";
    public final static String home = "home.jsp";
    public final static String profile = "profile.jsp";
    public final static String playrandom = "playRandom.jsp";
    public final static String forum = "ForumPage.jsp";
    public final static String forumreply = "ForumReplyPage.jsp";
    
    public static String make(String link, String description){
        return "<a href=\""+link+"\""+">"+description+"</a>";
    }
}
