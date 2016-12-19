<%-- 
    Document   : logout
    Created on : Dec 6, 2016, 2:25:17 AM
    Author     : ab9ma
--%>

<%@page import="muman.etc.Webpage"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Logout</title>
    </head>
    <body>
        <%
            session.invalidate();
            
                RequestDispatcher rd = request.getRequestDispatcher(Webpage.login);
                rd.forward(request, response);
            
        %>
       
    </body>
</html>
