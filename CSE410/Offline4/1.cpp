#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "base_shape.hpp"
#include "bitmap_image.hpp"

#define MOVESPEED 2
#define ROTATIONSPEED 1.5

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500


#define AXIS_SIZE 400

#define FOVY 80.0
#define ASPECT 1.0
#define ZNEAR 1.0
#define ZFAR 1000.0

#define INF 99999999



//GLOBAL VARIABLES: Offline1
double cameraHeight;
double cameraAngle;
int drawaxes;
double angle;
point camPos;
vect u,r,l;


//GLOBAL VARIABLES: Offline4
vector<BaseObject*> objects;
vector<vect> lights;
int image_width,image_height;
bitmap_image *image;


void drawAxes()
{
	if(drawaxes==1)
	{
		//glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glColor3f(1, 0, 0);
			glVertex3f( AXIS_SIZE,0,0);
			glVertex3f(-AXIS_SIZE,0,0);
			

			glColor3f(0, 1.0, 0);
			glVertex3f(0,-AXIS_SIZE,0);
			glVertex3f(0, AXIS_SIZE,0);
			

			glColor3f(0,0 , 1.0);
			glVertex3f(0,0, AXIS_SIZE);
			glVertex3f(0,0,-AXIS_SIZE);
		}glEnd();
	}
}






void capture(){
	
	cout<<camPos.x<<" "<<camPos.y<<" "<<camPos.z<<endl;

	image = new bitmap_image(image_width,image_height);

    for(int i=0;i<image_width;i++){
        for(int j=0;j<image_height;j++){
            image->set_pixel(i,j,0,0,0); //initialized to black
        }
    }


    double plane_distance = (1.0*WINDOW_HEIGHT/2.0)/tan(1.0*FOVY*pi/360.0);


    vect tmp = vectSum(vectSum(
    							scaleVector(l,1.0*plane_distance), //l*plane_distance
    							scaleVector(
    										scaleVector(r,1.0*WINDOW_WIDTH/2.0), //r*WINDOW_WIDTH/2.0
    									-1.0) // minus
    						),
    					scaleVector(u,1.0*WINDOW_HEIGHT/2.0) //u*WINDOW_HEIGHT/2.0
    				); //final addition

    //cout<<tmp.x<<" "<<tmp.y<<" "<<tmp.z<<" "<<endl;
    vect topLeft = vectSum({camPos.x,camPos.y,camPos.z},tmp);



    double du = 1.0 * WINDOW_WIDTH/image_width;
    double dv = 1.0* WINDOW_HEIGHT/image_height;


   // cout<<topLeft.x<<" "<<topLeft.y<<" "<<topLeft.z<<endl;
    //cout<<" DU DV "<<du<<", "<<dv<<endl;


    for(int i=0;i<image_width;i++){
    	for(int j=0;j<image_height;j++){

    		vect ttmp = vectSum(scaleVector(r,j*du),scaleVector(scaleVector(u,i*dv),-1));
    		vect corner = vectSum(topLeft,ttmp);

    		//cout<<corner.x<<" "<<corner.y<<" "<<corner.z<<endl;
    		//break;

    		LightRay* ray = new LightRay(camPos,vectSum(corner,scaleVector({camPos.x,camPos.y,camPos.z},-1)));

    		

    		//cout<<"RAY"<<endl;
    		//cout<<ray->start.x<<" "<<ray->start.y<<" "<<ray->start.z<<endl;
    		//cout<<ray->dir.x<<" "<<ray->dir.y<<" "<<ray->dir.z<<endl;
    		
    	

    		int nearest = -1;
    		double colorAt[3];
    		double t_min = INF;
    		

    		for(int k=0;k<objects.size();k++){
    			double t = objects[k]->intersect(ray,colorAt,0);

    			//
    			if(t<=0)continue;
    			else if(t<t_min){
    				t_min = t;
    				nearest = k;
    				//printf("%d\n",k );
    			}
    			cout<<t<<endl;
    		}

    		if(nearest!=-1){
    			double t = objects[nearest]->intersect(ray,colorAt,1);

    			image->set_pixel(j,i,colorAt[0]*255.0,colorAt[1]*255.0,colorAt[2]*255.0);
    		}
    	}
    }


    image->save_image("1.bmp");

    printf("DONE\n");
}




void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '0':
			capture();
			break;
		case '1':
			l=rotateVector(l,u,ROTATIONSPEED);
			r=rotateVector(r,u,ROTATIONSPEED);
			break;
		case '2':
			l=rotateVector(l,u,-ROTATIONSPEED);
			r=rotateVector(r,u,-ROTATIONSPEED);
			break;
		case '3':
			l=rotateVector(l,r,ROTATIONSPEED);
			u=rotateVector(u,r,ROTATIONSPEED);
			break;
		case '4':
			l=rotateVector(l,r,-ROTATIONSPEED);
			u=rotateVector(u,r,-ROTATIONSPEED);
			break;
		case '5':
			u=rotateVector(u,l,ROTATIONSPEED);
			r=rotateVector(r,l,ROTATIONSPEED);
			break;
		case '6':
			u=rotateVector(u,l,-ROTATIONSPEED);
			r=rotateVector(r,l,-ROTATIONSPEED);
			break;
		
		default:
			break;
	}
}
void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			camPos=movePointAlongvect(camPos,l,-MOVESPEED);
			break;
		case GLUT_KEY_UP:		// up arrow key
			camPos=movePointAlongvect(camPos,l,MOVESPEED);
			break;

		case GLUT_KEY_RIGHT:
			camPos=movePointAlongvect(camPos,r,MOVESPEED);
			break;
		case GLUT_KEY_LEFT:
			camPos=movePointAlongvect(camPos,r,-MOVESPEED);
			break;

		case GLUT_KEY_PAGE_UP:
			camPos=movePointAlongvect(camPos,u,MOVESPEED);
			break;
		case GLUT_KEY_PAGE_DOWN:
			camPos=movePointAlongvect(camPos,u,-MOVESPEED);
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
			if(state == GLUT_DOWN){

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
	gluLookAt(camPos.x,camPos.y,camPos.z, camPos.x+l.x,camPos.y+l.y,camPos.z+l.z,u.x,u.y,u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects


    drawAxes();

	for(int i=0;i<objects.size();i++){
		objects[i]->draw();
	}

	glColor3f(1.0, 0.0, 1.0);
	glPointSize(2);
	glBegin(GL_POINTS);	
	for(int i=0;i<lights.size();i++){
		glVertex3f(lights[i].x,lights[i].y,lights[i].z);
    }
    glEnd();


	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}
void animate(){
	angle+=1;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}
void init(){
	//initializing camera params
	camPos.x=100;
	camPos.y=100;
	camPos.z=10;
	drawaxes=1;



	u.x=u.y=0;
	u.z=1;
	
	r.x=-1.0/(sqrt(2));
	r.y=1.0/(sqrt(2));
	r.z=0;
	
	l.x=-1.0/(sqrt(2));
	l.y=-1.0/(sqrt(2));
	l.z=0;


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
	gluPerspective(FOVY,ASPECT,ZNEAR,ZFAR);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}



void loadTestData()
{	
	image_width = image_height = 768;

	point aa = {20,20,10};
	BaseObject* tmp = new Sphere(aa,10);
	tmp->setColor(1,0,0);
	tmp->setCoeffs(0.4,0.2,0.2,0.2);
	tmp->setShine(1);
	objects.push_back(tmp);

	aa = {0,15,15};
	tmp = new Sphere(aa,5);
	tmp->setColor(0,1,0);
	tmp->setCoeffs(0.4,0.2,0.2,0.2);
	tmp->setShine(1);
	objects.push_back(tmp);

/*	BaseObject* tmp2 = new Floor(1000,20);
	tmp2->setCoeffs(0.4,0.2,0.2,0.2);
	tmp2->setShine(1);
	//tmp2->setColor(1,0,0);
	objects.push_back(tmp2);
*/


	vect light1 = {-50,50,50};

	lights.push_back(light1);


}






int main(int argc, char **argv){
	
	//freopen("out.txt", "w", stdout);
	loadTestData();



	glutInit(&argc,argv);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Task 1 & 2");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);


	vect aa = {100,200,300};

	aa = normalizeVector(aa);

	cout<<aa.x<<" "<<aa.y<<" "<<aa.z<<endl;


	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
