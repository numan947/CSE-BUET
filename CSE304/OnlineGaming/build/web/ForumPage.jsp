<%@page import="muman.etc.Webpage"%>
<%@page import="muman.db.DataAccess"%>
<%@ page import="java.util.Objects" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="muman.models.forum.ForumPost" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Forum</title>
</head>
<body>
    <jsp:include page = "navigation.jsp"/>
<h1>WELCOME TO FORUM</h1><br>
<h3>POST NOW!!</h3>

<input required form="postform" type="text" name="posttitle" placeholder="Title of the post" size="81"><br>
<textarea required name="postbody" form="postform" rows="4" cols="50" style="resize:none" placeholder="Enter your post....."></textarea>
<br>
<select required form="postform" name="postsection">

    <%
        String username = (String) session.getAttribute("username");
        if(username==null) request.getRequestDispatcher(Webpage.login).forward(request, response);
     
    //get the sections from database
        ArrayList<String>sections=(new DataAccess().getSections());
//        sections.add("now");
//        Collections.addAll(sections, new String[]{
//                "then", "how", "kow"});


        for(int i=0;i<sections.size();i++){

    %>
    <option values="<%=sections.get(i)%>"><%=sections.get(i)%></option>
    <%}%>


</select>
<br><br>

<form method="post" id="postform" action="ForumPage.jsp" > <!--MAY NEED TO CHANGE HERE-->
    <input type="submit">
</form><br><br>

<%
    String inTitle=request.getParameter("posttitle");
    String inBody=request.getParameter("postbody");
    String section = request.getParameter("postsection");

    if(inTitle!=null&& !Objects.equals(inTitle, "")&&inBody!=null&& !Objects.equals(inBody, "")){
        //place for database insert
        (new DataAccess()).insertForumPost(inTitle, inBody, section, username);
    }

    ArrayList<ForumPost> forumPosts = (new DataAccess().getPostList());
   // ArrayList<ForumPost>forumPosts= GENERATOR.getPostList();//get the forum posts from database
    if(forumPosts==null) out.print("No posts");
    else
    for(int i=0;i<forumPosts.size();i++){

        ForumPost cur=forumPosts.get(i);
        %>
        <form method="post" action="ForumReplyPage.jsp">
            Title: <%=cur.getTitle()%>&nbsp&nbsp&nbsp&nbsp
            <button name="post_id" type="submit" value="<%=cur.getId()%>">View</button><br>
            <small> 
            Section: <%=cur.getSection()%><br>
            Posted by:&nbsp<%=cur.getPosted_by()%><br>
            Posted on:&nbsp<%=cur.getDate()%><br>
            </small>
        </form>
    <%}%>

</body>
</html>
