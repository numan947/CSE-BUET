<%-- 
    Document   : profile
    Created on : Dec 15, 2016, 10:18:41 AM
    Author     : ab9ma
--%>

<%@page import="muman.db.DataAccess"%>
<%@page import="muman.models.UserInfo"%>
<%@page import="muman.etc.Webpage"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Profile</title>
    </head>
    <body>
        <jsp:include page = "navigation.jsp"/>
        <%
            String username = (String) session.getAttribute("username");
          
            if(username==null)
            {
                RequestDispatcher rd = request.getRequestDispatcher(Webpage.login);
                rd.forward(request, response);
            }
           
        
        out.print("<h1>Your Account Info</h1>");
        
    
        UserInfo user = (new DataAccess()).getUser(username);
        if(user==null){
            out.print("No data found");
        }
        else {
            out.print(user.toTable());
        }
         %>
    </body>
</html>
