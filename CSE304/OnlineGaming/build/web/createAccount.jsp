<%-- 
    Document   : createAccount
    Created on : Dec 6, 2016, 1:15:27 AM
    Author     : ab9ma
--%>

<%@page import="muman.etc.Webpage"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Register</title>
    </head>
    <body>
        <%
            if(session.getAttribute("username")!=null) 
                request.getRequestDispatcher(Webpage.home).forward(request, response);
        %>
        
        <% out.print(Webpage.make(Webpage.login, "Login")); %>
        
        <form method="post" action="CreateAccount.do">
            <h1>Create Account</h1>
        Username <input required type="text" name="username"/><br>
        Full Name <input required type="text" name="user_full_name"/><br>
        Password <input required type="password" name="password"/><br>
        Email <input required type="email" name="email"/><br>
        Date of Birth <input required type="text" name="birth_date"/> (dd/mon/yyyy)<br>
        Region <select required name="region">
            <option value="Dhaka">Dhaka</option>
            <option value="Chittagong">Chittagong</option>
            <option value="Rajshahi">Rajshahi</option>
            <option value="Sylhet">Sylhet</option>
        </select><br>
        <input type="submit" value="Create Account"/>
        </form>
        
        
</html>
