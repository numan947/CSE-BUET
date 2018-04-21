#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#include <GL/freeglut.h>
#include <GL/gl.h>
 

#define pi (2*acos(0.0))
#define ANGLE 5



double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;



struct point
{
	double x,y,z;
};

struct vect
{
	double x,y,z;
};






double rot1;//w,q
double rot2;//1,2
double rot3;//3,4
double rot4;//5,6
double rot5;//7,8
double rot6;//9,0


void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}
void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			if(rot2<45)rot2+=ANGLE;
			break;
		case '2':
			if(rot2>-45)
				rot2-=ANGLE;
			break;
		case '3':
			if(rot3<90)
				rot3+=ANGLE;
			break;
		case '4':
			if(rot3>0)
				rot3-=ANGLE;
			break;
		case '5':
			if(rot4>0)
				rot4-=ANGLE;
			break;

		case '6':
			if(rot4<90)
				rot4+=ANGLE;
			break;
		case '7':
			if(rot5>0)
				rot5-=ANGLE;
			break;
		case '8':
			if(rot5<90)
				rot5+=ANGLE;
			break;
		case '9':
			if(rot6>0)
				rot6-=ANGLE;
			break;
		case '0':
			if(rot6<90)
				rot6+=ANGLE;
			break;

		case 'w':
			if(rot1<90)rot1+=ANGLE;
			break;
		case 'q':
			if(rot1>0)rot1-=ANGLE;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}


void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawEllipsoid(20,20,30,40,50);
	//glPushMatrix();
	//{
		glRotatef(rot1,0,1,0);//w,q
		glRotatef(rot2,1,0,0);//1,2
		glScalef(1,1,5);
	    glTranslatef(0,0,-10);
	    glutWireSphere(10,10,10);
	//}glPopMatrix();
    

    //glTranslatef(0,0,-80);

    glRotatef(rot3,1,0,0);//3,4
    glTranslatef(0,0,-16.8);
    glutWireSphere(7,10,10);


    glTranslatef(0,0,-6);
    glRotatef(180,1,0,0);
    glRotatef(rot4,0,0,1);
    glBegin(GL_TRIANGLES);{
    	glVertex3f(0,0,0);
    	glVertex3f(5,0,6);
    	glVertex3f(-5,0,6);
    }glEnd();
    glRotatef(-180,1,0,0);
    
    glPushMatrix();{
   	glRotatef(rot6,-1,0,0);
    glTranslatef(5,0,-7);
    glutWireSphere(3,10,10);
	}glPopMatrix();


    glPushMatrix();{
    glTranslatef(-5,0,-7);
    glRotatef(rot5,0,0,1);
    glutWireSphere(3,10,10);
	}glPopMatrix();
    

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;


	rot1=0;
	rot2=0;
	rot3=0;

	rot4=rot5=rot6=0;




	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Task 4");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
