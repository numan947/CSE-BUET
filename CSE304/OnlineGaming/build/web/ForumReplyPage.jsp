<%@page import="muman.db.DataAccess"%>
<%@page import="muman.etc.Webpage"%>
<%@ page import="muman.models.forum.PostReply"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="muman.models.forum.ForumPost"%>

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Reply Page</title>
</head>
<body>

    <jsp:include page = "navigation.jsp"/>

<%
    String username = (String) session.getAttribute("username");
        if(username==null) request.getRequestDispatcher(Webpage.login).forward(request, response);

    String post_id=request.getParameter("post_id");

    //use the post id to get the related reply from database

    ForumPost p=(new DataAccess()).getThePost(post_id);
   if(p==null) request.getRequestDispatcher(Webpage.forum).forward(request, response);


    %>
    <h3><%=p.getTitle()%></h3>
    <small>Posted by: <%=p.getPosted_by()%><br>
        Posted on: <%=p.getDate()%><br></small>
        Content:<br>
        <%=p.getContent()%><br><br>
    <form method="post" action="FlagPost.do"><!--change the action to a servlet, also after updating the flag redirect to this page-->
        <button name="post_id" type="submit" value="<%=p.getId()%>">FLAG POST</button><small><%=" ("+p.getPflag()+")"%></small><br>
        
    </form>


    <br><br><br>

    <textarea required name="replybody" form="replyform" rows="4" cols="50" style="resize:none" placeholder="Reply....."></textarea>

    <form method="post" id="replyform" action="ForumReplyPage.jsp" > <!--MAY NEED TO CHANGE HERE-->
        <input type="hidden" name="post_id" value="<%=post_id%>">
        
        <input type="submit">
    </form><br><br>
    <%
        String replybody = request.getParameter("replybody");
        if(replybody!= null && !replybody.equals("")) (new DataAccess()).insertForumReply(post_id, username, replybody);
    %>




    <h4>REPLY SECTION: </h4><br>



  <!--place for reply-->
  <%
    ArrayList<PostReply>replies=(new DataAccess().getReplyList(post_id));//.generateReply(post_id); //get replies from database
    
    if(replies!=null)
    for(int i=0;i<replies.size();i++){
        PostReply cur=replies.get(i);
  
  %>

        <small>Reply NO: <%=i+1%>&nbsp&nbsp
        Replied by: <%=cur.getReplied_by()%><br>
        Replied on: <%=cur.getDate()%><br></small>
        Content: <%=cur.getContent()%><br><br>
        <form method="post" action="FlagReply.do"><!--change the action to a servlet, also after updating the flag redirect to this page-->
            <input type="hidden" name="post_id" value="<%=cur.getPost_id()%>">
            <input type="hidden" name="reply_id" value="<%=cur.getReply_id()%>">
            
            <input type="submit" value="Flag Reply"><small><%=" ("+cur.getRflag()+")"%></small><!--give reply an id-->
        </form>
        <br><br><br>
        
    <%}%>



</body>
</html>
