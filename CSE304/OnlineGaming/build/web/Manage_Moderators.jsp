<%@ page import="java.util.ArrayList" %>
<%@ page import="forum.Moderator" %>
<%@ page import="com.sun.org.apache.xpath.internal.operations.Mod" %><%--
  Created by IntelliJ IDEA.
  User: numan947
  Date: 12/18/16
  Time: 2:01 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Manage Moderator</title>
</head>
<body>
<h1>MANAGE MODERATORS</h1>

<%
// add new moderators here
%>
<%
//get all the moderators from db, also get the sections from db, also all the users
    ArrayList<Moderator>moderatorArrayList=new ArrayList<>();
    ArrayList<Moderator>userArrayList=new ArrayList<>();
    ArrayList<String>sections=new ArrayList<>();
    moderatorArrayList.add(new Moderator("ASDASDASDAS","FDFDFDFDF"));
    moderatorArrayList.add(new Moderator("ASDASDASDAS","FDFDFDFDF"));
    moderatorArrayList.add(new Moderator("ASDASDASDAS","FDFDFDFDF"));
    userArrayList.addAll(moderatorArrayList);


    for(int i=0;i<moderatorArrayList.size();i++){
        Moderator cur=moderatorArrayList.get(i);
%>
<%=cur.getUserName()%>&nbsp&nbsp<%=cur.getFullName()%>
<form style="display: inline" method="post" action="#servlet">
    <button name="section" type="submit" value="<%=cur.getUserName()%>">DELETE</button>
</form>
<br><br>
<%}%>


<form action="Manage_Moderators.jsp" method="post">

    <select name="#giveuseridhere">
        <% for(int i=0;i<userArrayList.size();i++){
            Moderator cur=userArrayList.get(i);
        %>
        <option value="<%=cur.getUserName()%>"><%=cur.getUserName()+"---"+cur.getFullName()%></option>
        <%}%>
    </select>


    <select required  name="#assignname">
            <%

        for(int i=0;i<sections.size();i++){

        %>
        <option values="<%=sections.get(i)%>"><%=sections.get(i)%></option>
                    <%}%>
    </select>
    &nbsp&nbsp<input type="submit" value="create">
</form>





</body>
</html>
