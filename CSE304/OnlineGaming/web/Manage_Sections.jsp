<%@ page import="java.util.ArrayList" %>
<%@ page import="java.util.Collections" %><%--
  Created by IntelliJ IDEA.
  User: numan947
  Date: 12/18/16
  Time: 2:01 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Manage Section</title>
</head>
<body>
<h1>SECTION MANAGEMENT</h1>

<%
    String sectionName=request.getParameter("new_section");
    //add the new section to database


%>


<%
    //get the sections from database
    ArrayList<String>sections=new ArrayList<>();
    sections.add("now");
    Collections.addAll(sections, new String[]{
            "then", "how", "kow"});


    for(int i=0;i<sections.size();i++){


%>
<%=sections.get(i)%>&nbsp
<form style="display: inline" method="post" action="#servlet" >
<input type="text" name="new_section_name" placeholder="new name">&nbsp<input type="submit" value="update">
</form>
<form style="display: inline" method="post" action="#servlet">
    <button name="section" type="submit" value="<%=sections.get(i)%>">DELETE</button>
</form>

<br>

<%}%>

<form action="Manage_Sections.jsp" method="post">
    <input type="text" name="new_section" placeholder="name">&nbsp<input type="submit" value="create">
</form>



</body>
</html>
