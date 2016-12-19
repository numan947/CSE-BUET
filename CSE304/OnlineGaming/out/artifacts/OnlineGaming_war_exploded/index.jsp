<%@page import="muman.etc.Webpage"%>
<html>
    <head>
        <title>Welcome</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
        <%
            if(session.getAttribute("username")!=null) 
                request.getRequestDispatcher(Webpage.home).forward(request, response);
        %>
        
       <% out.print(Webpage.make(Webpage.signup, "Sign Up")); %>
        <form method="post" action="LoginProcess.do">
            <h1>Login</h1>
            Enter your username: <input required type="text" name="username" /> <br/>
            Enter your password: <input required type="password" name="password" /> <br/>
            <input type="submit" value="Login" />
        </form>
               
        
    </body>
</html>

