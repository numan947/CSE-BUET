#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#include <GL/freeglut.h>
#include <GL/gl.h>
 

#define pi (2*acos(0.0))

#define SPEED 1
#define ROTATION 2
#define BOUNDARY 120
#define ARROWSIZE 2.5


struct point
{
	double x,y,z;
};

struct vect
{
	double x,y,z;
};




double dotProduct(vect a, vect b)
{
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

point movePointAlongvect(point pos,vect r, double scale)
{
	point tmp={pos.x+scale*r.x,pos.y+scale*r.y,pos.z+scale*r.z};
	return tmp;
}
vect scaleVector(vect a, double scale)
{
	vect tmp = {a.x*scale,a.y*scale,a.z*scale};
	return tmp;
}

vect vectSum(vect a, vect b)
{
	vect tmp={a.x+b.x,a.y+b.y,a.z+b.z};
	return tmp;
}

vect rotate2Dvect(vect a, double angle)
{
	vect perp = {a.y,-a.x,0};
	return vectSum(scaleVector(a,cos(pi*angle/180.0)),scaleVector(perp,sin(pi*angle/180.0)));
}

vect reflect2Dvect(vect a,vect perp)
{
	double d = sqrt(perp.x*perp.x+perp.y*perp.y);
	vect p = {1.0*perp.x/d,1.0*perp.y/d,0};
	vect r = vectSum(a,scaleVector(scaleVector(p,2*dotProduct(a,p)),-1));
	return r;
}

int drawBoundary;
point pos;
vect v;
vect X,Y;


void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}


void drawArrow()
{
	point tail = movePointAlongvect(pos,v,5);
	vect perp = {v.y,-v.x,0};
	point head1=movePointAlongvect(tail,v,ARROWSIZE);
	point head2=movePointAlongvect(tail,perp,ARROWSIZE);
	point head3=movePointAlongvect(tail,scaleVector(perp,-1),ARROWSIZE);
	

	glColor3f(1,1,1);
	glBegin(GL_LINES);{
		glVertex3f(pos.x,pos.y,pos.z);
		glVertex3f(head1.x,head1.y,head1.z);
	}glEnd();

	glColor3f(1,0,0);
	glBegin(GL_TRIANGLES);{
		glVertex3f(head1.x,head1.y,head1.z);
		glVertex3f(head2.x,head2.y,head2.z);
		glVertex3f(head3.x,head3.y,head3.z);
	}glEnd();
	glColor3f(1,1,1);
	
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			//.drawgrid=1-drawgrid;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			break;
		case GLUT_KEY_UP:		// up arrow key
			
			break;

		case GLUT_KEY_RIGHT:
			v = rotate2Dvect(v,ROTATION);
			break;
		case GLUT_KEY_LEFT:
			v = rotate2Dvect(v,-ROTATION);
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
				drawBoundary=1-drawBoundary;
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
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	if(drawBoundary)
		drawSquare(120);
	
	drawArrow();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	pos = movePointAlongvect(pos,v,SPEED);
	
	//if(drawBoundary){
		if(pos.x>=BOUNDARY){
			v=reflect2Dvect(v,scaleVector(X,-1));
		}
		if(pos.y>=BOUNDARY){
			v=reflect2Dvect(v,scaleVector(Y,-1));
		}

		if(pos.x<=-BOUNDARY){
			v=reflect2Dvect(v,scaleVector(X,1));
		}
		if(pos.y<=-BOUNDARY){
			v=reflect2Dvect(v,scaleVector(Y,1));
		}
	//}
	glutPostRedisplay();
}

void init(){
	//initializing arrow
	pos.x=0;
	pos.y=0;
	pos.z=0;

	v.x=1;
	v.y=1;
	v.z=0;

	X.x=1;X.y=X.z=0;
	Y.y=1;Y.x=Y.z=0;

	drawBoundary=1;

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

	glutCreateWindow("Task 3");

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
