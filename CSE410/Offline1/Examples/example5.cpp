/*
 * GL05IdleFunc.cpp: Translation and Rotation
 * Transform primitives from their model spaces to world space (Model Transform).
 */
 // for MS Windows
#include <GL/freeglut.h>  // GLUT, include glu.h and gl.h
#include <GL/gl.h>
// Global variable
GLfloat angle = 0.0f;  // Current rotational angle of the shapes
int drawgrid=1;
/* Initialize OpenGL Graphics */
void initGL() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}
 void drawGrid()
{
   int i;
   if(drawgrid==1)
   {
      glColor3f(0.6, 0.6, 0.6);  //grey
      glBegin(GL_LINES);{
         for(i=-8;i<=8;i++){

            if(i==0)
               continue;   //SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*10.0, -90, 0);
            glVertex3f(i*10.0,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*10.0, 0);
            glVertex3f( 90, i*10.0, 0);
         }
      }glEnd();
   }
}

void keyboardListener(unsigned char key, int x,int y){
   switch(key){

      case '1':
         drawgrid=1-drawgrid;
         break;

      default:
         break;
   }
}

/* Called back when there is no other event to be handled */
void idle() {
   glutPostRedisplay();   // Post a re-paint request to activate display()
}
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
   glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
   glLoadIdentity();               // Reset the model-view matrix
   

   drawGrid();

   glPushMatrix();                     // Save model-view matrix setting
   glTranslatef(-0.5f, 0.4f, 0.0f);    // Translate
   glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
   glBegin(GL_QUADS);                  // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex2f(-0.3f, -0.3f);
      glVertex2f( 0.3f, -0.3f);
      glVertex2f( 0.3f,  0.3f);
      glVertex2f(-0.3f,  0.3f);
   glEnd();
   glPopMatrix();                      // Restore the model-view matrix
 
   glPushMatrix();                     // Save model-view matrix setting
   glTranslatef(-0.4f, -0.3f, 0.0f);   // Translate
   glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
   glBegin(GL_QUADS);
      glColor3f(0.0f, 1.0f, 0.0f); // Green
      glVertex2f(-0.3f, -0.3f);
      glVertex2f( 0.3f, -0.3f);
      glVertex2f( 0.3f,  0.3f);
      glVertex2f(-0.3f,  0.3f);
   glEnd();
   glPopMatrix();                      // Restore the model-view matrix
 
   glPushMatrix();                     // Save model-view matrix setting
   glTranslatef(-0.7f, -0.5f, 0.0f);   // Translate
   glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
   glBegin(GL_QUADS);
      glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
      glVertex2f(-0.2f, -0.2f);
      glColor3f(1.0f, 1.0f, 1.0f); // White
      glVertex2f( 0.2f, -0.2f);
      glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
      glVertex2f( 0.2f,  0.2f);
      glColor3f(1.0f, 1.0f, 1.0f); // White
      glVertex2f(-0.2f,  0.2f);
   glEnd();
   glPopMatrix();                      // Restore the model-view matrix
 
   glPushMatrix();                     // Save model-view matrix setting
   glTranslatef(0.4f, -0.3f, 0.0f);    // Translate
   glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
   glBegin(GL_TRIANGLES);
      glColor3f(0.0f, 0.0f, 1.0f); // Blue
      glVertex2f(-0.3f, -0.2f);
      glVertex2f( 0.3f, -0.2f);
      glVertex2f( 0.0f,  0.3f);
   glEnd();
   glPopMatrix();                      // Restore the model-view matrix
 
   glPushMatrix();                     // Save model-view matrix setting
   glTranslatef(0.6f, -0.6f, 0.0f);    // Translate
   glRotatef(180.0f + angle, 0.0f, 0.0f, 1.0f); // Rotate 180+angle degree
   glBegin(GL_TRIANGLES);
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-0.3f, -0.2f);
      glColor3f(0.0f, 1.0f, 0.0f); // Green
      glVertex2f( 0.3f, -0.2f);
      glColor3f(0.0f, 0.0f, 1.0f); // Blue
      glVertex2f( 0.0f,  0.3f);
   glEnd();
   glPopMatrix();                      // Restore the model-view matrix
 
   glPushMatrix();                     // Save model-view matrix setting
   glTranslatef(0.5f, 0.4f, 0.0f);     // Translate
   glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
   glBegin(GL_POLYGON);
      glColor3f(1.0f, 1.0f, 0.0f); // Yellow
      glVertex2f(-0.1f, -0.2f);
      glVertex2f( 0.1f, -0.2f);
      glVertex2f( 0.2f,  0.0f);
      glVertex2f( 0.1f,  0.2f);
      glVertex2f(-0.1f,  0.2f);
      glVertex2f(-0.2f,  0.0f);
   glEnd();
   glPopMatrix();                      // Restore the model-view matrix
 
   glutSwapBuffers();   // Double buffered - swap the front and back buffers
 
   // Change the rotational angle after each display()
   angle += 0.2f;
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();
   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}



 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);          // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);  // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height - non-square
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("Animation via Idle Function");  // Create window with the given title
   
   //glEnable(GL_DEPTH_TEST);   //enable Depth Testing

   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   //glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   glutIdleFunc(idle);             // Register callback handler if no other event
   glutKeyboardFunc(keyboardListener);
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}