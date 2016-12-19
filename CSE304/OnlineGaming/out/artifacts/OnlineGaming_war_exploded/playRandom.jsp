<%-- 
    Document   : playRandom
    Created on : Dec 15, 2016, 10:36:31 AM
    Author     : ab9ma
--%>

<%@page import="muman.etc.Webpage"%>
<%@page import="muman.models.Match"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Play Random</title>
    </head>
    <body>
        <%
            Match match = (Match) session.getAttribute("match");
            if(match==null){
                RequestDispatcher rd =  request.getRequestDispatcher(Webpage.home);
                rd.forward(request, response);
            }
            out.print("Player 1: "+match.getPlayer1());
            out.print("<br>Player 2: "+match.getPlayer2());
        %>
        <br><br>
        <form method="post" action="WinnerProcess.do">
            Player 1 Score<input required type="number" name="score1"></input><br>
            Player 2 Score<input required type="number" name="score2"></input><br>
            <input type="submit" value="End Match"></input>
            
        </form>
            
    </body>
</html>
