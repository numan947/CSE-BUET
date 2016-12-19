<%-- 
    Document   : home
    Created on : Dec 6, 2016, 12:34:36 AM
    Author     : ab9ma
--%>

<%@page import="muman.models.UserInfo"%>
<%@page import="muman.etc.Webpage"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Home Page</title>
        
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
         %>
         <form action="PlayRandom.do">
             <input type="submit" value="Play Random"></input>
         </form>
        
    </body>
</html>
