
<%@page import="muman.etc.Webpage"%>
<%
   out.print(Webpage.make(Webpage.home, "Home")+" "); 
   out.print(Webpage.make(Webpage.profile, "Profile")+" "); 
   
    out.print(Webpage.make(Webpage.forum, "Forum")+" "); 
    out.print(Webpage.make(Webpage.logout, "Logout")+" "); 

%>
<br>
<br>
<br>


