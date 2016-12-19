package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import muman.etc.Webpage;
import muman.db.DataAccess;
import java.util.Objects;
import java.util.ArrayList;
import muman.models.forum.ForumPost;

public final class ForumPage_jsp extends org.apache.jasper.runtime.HttpJspBase
    implements org.apache.jasper.runtime.JspSourceDependent {

  private static final JspFactory _jspxFactory = JspFactory.getDefaultFactory();

  private static java.util.List<String> _jspx_dependants;

  private org.glassfish.jsp.api.ResourceInjector _jspx_resourceInjector;

  public java.util.List<String> getDependants() {
    return _jspx_dependants;
  }

  public void _jspService(HttpServletRequest request, HttpServletResponse response)
        throws java.io.IOException, ServletException {

    PageContext pageContext = null;
    HttpSession session = null;
    ServletContext application = null;
    ServletConfig config = null;
    JspWriter out = null;
    Object page = this;
    JspWriter _jspx_out = null;
    PageContext _jspx_page_context = null;

    try {
      response.setContentType("text/html;charset=UTF-8");
      pageContext = _jspxFactory.getPageContext(this, request, response,
      			null, true, 8192, true);
      _jspx_page_context = pageContext;
      application = pageContext.getServletContext();
      config = pageContext.getServletConfig();
      session = pageContext.getSession();
      out = pageContext.getOut();
      _jspx_out = out;
      _jspx_resourceInjector = (org.glassfish.jsp.api.ResourceInjector) application.getAttribute("com.sun.appserv.jsp.resource.injector");

      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("<html>\n");
      out.write("<head>\n");
      out.write("    <title>Forum</title>\n");
      out.write("</head>\n");
      out.write("<body>\n");
      out.write("<h1>WELCOME TO FORUM</h1><br>\n");
      out.write("<h3>POST NOW!!</h3>\n");
      out.write("\n");
      out.write("<input required form=\"postform\" type=\"text\" name=\"posttitle\" placeholder=\"Title of the post\" size=\"81\"><br>\n");
      out.write("<textarea required name=\"postbody\" form=\"postform\" rows=\"4\" cols=\"50\" style=\"resize:none\" placeholder=\"Enter your post.....\"></textarea>\n");
      out.write("<br>\n");
      out.write("<select required form=\"postform\" name=\"postsection\">\n");
      out.write("\n");
      out.write("    ");

        String username = (String) session.getAttribute("username");
        if(username==null) request.getRequestDispatcher(Webpage.login).forward(request, response);
     
    //get the sections from database
        ArrayList<String>sections=(new DataAccess().getSections());
//        sections.add("now");
//        Collections.addAll(sections, new String[]{
//                "then", "how", "kow"});


        for(int i=0;i<sections.size();i++){

    
      out.write("\n");
      out.write("    <option values=\"");
      out.print(sections.get(i));
      out.write('"');
      out.write('>');
      out.print(sections.get(i));
      out.write("</option>\n");
      out.write("    ");
}
      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("</select>\n");
      out.write("<br><br>\n");
      out.write("\n");
      out.write("<form method=\"post\" id=\"postform\" action=\"ForumPage.jsp\" > <!--MAY NEED TO CHANGE HERE-->\n");
      out.write("    <input type=\"submit\">\n");
      out.write("</form><br><br>\n");
      out.write("\n");

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
        
      out.write("\n");
      out.write("        <form method=\"post\" action=\"ForumReplyPage.jsp\">\n");
      out.write("            ");
      out.print(cur.getTitle());
      out.write("&nbsp&nbsp&nbsp&nbsp\n");
      out.write("            <button name=\"post_id\" type=\"submit\" value=\"");
      out.print(cur.getId());
      out.write("\">GO TO REPLY</button><br>\n");
      out.write("            ");
      out.print(cur.getSection());
      out.write("<br>\n");
      out.write("            posted by:&nbsp");
      out.print(cur.getPosted_by());
      out.write("<br>\n");
      out.write("            posted on:&nbsp");
      out.print(cur.getDate());
      out.write("<br>\n");
      out.write("        </form>\n");
      out.write("    ");
}
      out.write("\n");
      out.write("\n");
      out.write("</body>\n");
      out.write("</html>\n");
    } catch (Throwable t) {
      if (!(t instanceof SkipPageException)){
        out = _jspx_out;
        if (out != null && out.getBufferSize() != 0)
          out.clearBuffer();
        if (_jspx_page_context != null) _jspx_page_context.handlePageException(t);
        else throw new ServletException(t);
      }
    } finally {
      _jspxFactory.releasePageContext(_jspx_page_context);
    }
  }
}
