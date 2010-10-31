// COMP 371 Asg1
// Sagar Patel 9356037

// This code uses parts of pilotView.c sample provided in the Lab.
// This usage is mainly limited to camera fucntions.

#include <windows.h>
#include "glut.h"
#include <math.h>
#include <stdio.h>
#include "SOIL.h"

//#include "QuadricObjects.h"
#include "DragonModel.h"

#define PI 3.14159265

GLdouble cam_position[3];	
GLdouble cam_target[3];	
GLdouble cam_up[3];	


GLuint tex_2D;


double cam_theta;
double cam_phi;
double cam_radius;

int h,w;

int Wired_or_Shade = GLU_LINE;

bool orthogonalFlag = false;

float zoom = 0.95;


float Pitch = 0;
float Yaw = 0;
float Roll = 0;

// Function Prototypes
void init(void);
void showReferenceAxis(void);

void orthogonalStart(void);
void orthogonalStop(void);

void display(void);
void reshape (int w, int h);
void keyboard(unsigned char key, int x, int y);
void specialCallbackProc (int key, int x, int y);





//QuadricObjects quadricobjects(&Wired_or_Shade);
DragonModel dragonmodel(&Wired_or_Shade);


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize (800, 800); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);

	init ();

	

	glutDisplayFunc(display); 
	

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialCallbackProc);

	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}




void init(void) 
{

	
	dragonmodel.generateBody();
	dragonmodel.generateTail();
	// Shift values just once
	dragonmodel.animateDragon(&Pitch,&Yaw,&Roll,1.5);

	tex_2D = SOIL_load_OGL_texture
    (
        "dragonscales.jpg",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_NTSC_SAFE_RGB
    );

	cam_radius = 100;

	// Setting cam position to origin
	// It is irreleveant since radius has been set to 10,
	// therefore, thses values will be recalculated later.
	cam_position[0] = 30;
	cam_position[1] = 30;
	cam_position[2] = 30;

	// Point camera to center of dragon
	cam_target[0] = 0;
	cam_target[1] = 30;
	cam_target[2] = 0;

	// Setting camera's Up vector
	// In this case, Up is the +Yaxis
	cam_up[0] = 0;
	cam_up[1] = 1;
	cam_up[2] = 0;

	cam_phi = 0.69;
	cam_theta = -3.99;

	glMatrixMode(GL_PROJECTION);
								
	glLoadIdentity();
								
	gluPerspective(90*zoom, (GLfloat)w/(GLfloat)h, 1.0, 10000.0);

	glMatrixMode(GL_MODELVIEW);	
								
	glLoadIdentity();
								
	//Background Color
		//Cornflower Blue
		//Original Code: 100-149-237
	//glClearColor (0.390625, 0.58203125, 0.92578125, 0.0);
	glClearColor(0,0,0,0);
	 
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);

	
	//Sets lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Allows color on models with lighting
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	//dragonmodel.generateTail();

}




void orthogonalStart(void) 
{
    glMatrixMode(GL_PROJECTION);
    
    glPushMatrix();
    glLoadIdentity();
    
    gluOrtho2D(0, w, 0, h);
    
    glScalef(1, -1, 1);
    glTranslatef(0, -h, 0);
    
    glMatrixMode(GL_MODELVIEW);
}

void orthogonalStop(void) 
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


void drawFloor(void)
	{
		glBindTexture(GL_TEXTURE_2D, tex_2D);

		glBegin(GL_QUADS);					
			glTexCoord2f(1.0f, 1.0f); 
			glVertex3f(200, 0,  200);	
			
			glTexCoord2f(1.0f, 0.0f); 
			glVertex3f( 200, 0,  -200);	
			
			glTexCoord2f(0.0f, 0.0f); 
			glVertex3f(-200, 0,  -200);

			glTexCoord2f(0.0f, 1.0f); 
			glVertex3f( -200,  0,  200);

		glEnd();
	}



void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glMatrixMode(GL_MODELVIEW);
	

	glLoadIdentity();





	if(orthogonalFlag)
	{
		orthogonalStart();
		
	}

	cam_position[0] = cam_radius * sin(cam_phi) * sin(cam_theta);
	cam_position[1] = cam_radius * cos(cam_phi);
	cam_position[2] = cam_radius * sin(cam_phi) * cos(cam_theta);
	
	

	gluLookAt(cam_position[0],cam_position[1],cam_position[2],
			  cam_target[0], cam_target[1], cam_target[2],
			  cam_up[0], cam_up[1], cam_up[2]);



	drawFloor();

	glPushMatrix();
	glScalef(0.5,0.5,0.5);

	dragonmodel.drawTrees();

	glPushMatrix();
	glTranslatef(170,0,110);
	dragonmodel.drawTrees();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(110,0,180);
	dragonmodel.drawTrees();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(105,0,-110);
	dragonmodel.drawTrees();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(180,0,-190);
	dragonmodel.drawTrees();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-105,0,180);
	dragonmodel.drawTrees();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-180,0,190);
	dragonmodel.drawTrees();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-195,0,-110);
	dragonmodel.drawTrees();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-110,0,-170);
	dragonmodel.drawTrees();
	glPopMatrix();



	glPushMatrix();
	glTranslatef(10,0,110);
	dragonmodel.drawTrees();
	glPopMatrix();




	glPopMatrix();


//Psuh Dragon up
	glPushMatrix();

	glTranslatef(0,20,0);
	
	dragonmodel.drawDragon();



	glPopMatrix();
    

	if(orthogonalFlag)
	{
		orthogonalStop();
		
	}

	glutSwapBuffers();


}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(90*zoom, (GLfloat) w/(GLfloat) h, 1.0, 800.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{

	
	switch (key) 
	{

		case 'r':
			glLoadIdentity();
			dragonmodel.generateBody();
			dragonmodel.generateTail();


		case 'k':
			Pitch += 1;
			Yaw = 0;
			Roll = 0;
			if(Pitch>90){Pitch = 90;}
			if(Pitch<0){Pitch=0;}
			dragonmodel.animateDragon(&Pitch,&Yaw,&Roll,0);
			break;
		
		case 'i':
			Pitch -= 1;
			Yaw = 0;
			Roll = 0;
			if(Pitch<-90){Pitch = -90;}
			if(Pitch>0){Pitch =0;}
			dragonmodel.animateDragon(&Pitch,&Yaw,&Roll,0);
			break;

		case 'j':
			Yaw += 1;
			Pitch = 0;
			Roll = 0;
			if(Yaw>90){Yaw = 90;}
			if(Yaw<0){Yaw=0;}
			dragonmodel.animateDragon(&Pitch,&Yaw,&Roll,0);
			break;
		
		case 'l':
			Yaw -= 1;
			Pitch = 0;
			Roll = 0;
			if(Yaw<-90){Yaw = -90;}
			if(Yaw>0){Yaw =0;}
			dragonmodel.animateDragon(&Pitch,&Yaw,&Roll,0);
			break;

		case 'u':
			Roll += 1;
			Yaw = 0;
			Pitch =0;
			if(Roll>90){Roll = 90;}
			if(Roll<0){Roll=0;}
			dragonmodel.animateDragon(&Pitch,&Yaw,&Roll,0);
			break;
		
		case 'o':
			Roll -= 1;
			Yaw = 0;
			Pitch =0;
			if(Roll<-90){Roll = -90;}
			if(Roll>0){Roll =0;}
			dragonmodel.animateDragon(&Pitch,&Yaw,&Roll,0);
			break;

		case 'z':
			zoom -= 0.01;
			//printf("%f \n",zoom);
			break;
		
		case 'Z':
			zoom += 0.01;
			break;


		case 'a':
			dragonmodel.animateDragon(&Pitch,&Yaw,&Roll,1.5);
			break;

		case 'f':				// Move Camera forward.
			cam_radius -= 0.5;
			break;

		case 'b' :				// Move Camera backward.
			cam_radius += 0.5;
			break;

		case 'w':
			Wired_or_Shade = GLU_FILL;
			break;

		case 'W':
			Wired_or_Shade = GLU_LINE;
			break;

		case 's':
			Wired_or_Shade = GLU_SILHOUETTE;
			break;

		case 'S':
			Wired_or_Shade = GLU_POINT;
			break;
		
		// case 'o':
		// 	orthogonalFlag = true;
		// 	break;
		// case 'O':
		// 	orthogonalFlag = true;

		case 'p':
			orthogonalFlag = false;
			break;
		case 'P':
			orthogonalFlag = false;
			break;

		case 'c':
			cam_radius = 100;
			cam_phi = 0.69;
			cam_theta = -3.99;
		
		break;

		case 'C':	
			cam_radius = 100;
			cam_phi = 0.69;
			cam_theta = -3.99;
		
		break;


		case 27: // ESC key
		exit(0);
		break; 
	}

	

	glutPostRedisplay();
}


void specialCallbackProc (int key, int x, int y)
					
{
	switch (key)		
	{
		
		case GLUT_KEY_LEFT:		// Rotate Camera in an anticlockwise direction about the Y axis of the At (center) point.
			cam_theta -= 1.0 * (PI/180);
			

			break;

		case GLUT_KEY_RIGHT:	// Rotate Camera in an clockwise direction about the Y axis of the At (center) point.
			cam_theta += 1.0 * (PI/180);
			break;

		case GLUT_KEY_UP :		// Rotate Camera in an anticlockwise direction about the X axis of the At (center) point.
			cam_phi -= 1.0 * (PI/180);
			break;

		case GLUT_KEY_DOWN :	// Rotate Camera in an clockwise direction about the X axis of the At (center) point.
			cam_phi += 1.0 * (PI/180);
			break;
	}

	glutPostRedisplay();
}



void showReferenceAxis(void)
							
	{

		 glBegin(GL_LINES);
							// X axis red
	      glColor3f(1, 0, 0);
	      glVertex3f(0, 0, 0);
	      glVertex3f(20, 0, 0);
							// Y axis green
	      glColor3f(0, 1, 0);
	      glVertex3f(0, 0, 0);
	      glVertex3f(0, 20, 0);
							// Z axis blue
	      glColor3f(0, 0, 1);
	      glVertex3f(0, 0, 0);
	      glVertex3f(0, 0, 20);
		  glEnd();
		
	}

