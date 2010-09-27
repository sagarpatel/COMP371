// COMP 371 Asg1
// Sagar Patel 9356037

// This code uses parts of pilotView.c sample provided in the Lab.
// This usage is mainly limited to camera fucntions.

#include <windows.h>
#include "glut.h"
#include <math.h>


#define PI 3.14159265

GLdouble cam_position[3];	
GLdouble cam_target[3];	
GLdouble cam_up[3];		

double cam_theta;
double cam_phi;
double cam_radius;

int h,w;

int Wired_or_Shade = GLU_LINE;


void init(void) 
{

	cam_radius = 15;

	// Setting cam position to origin
	// It is irreleveant since radius has been set to 10,
	// therefore, thses values will be recalculated later.
	cam_position[0] = 5;
	cam_position[1] = 5;
	cam_position[2] = -5;

	// Point camera to origin
	cam_target[0] = 0;
	cam_target[1] = 0;
	cam_target[2] = 0;

	// Setting camera's Up vector
	// In this case, Up is the +Yaxis
	cam_up[0] = 0;
	cam_up[1] = 1;
	cam_up[2] = 0;

	cam_phi = 18;//90.0 * (PI/180);
	cam_theta = -15.0;

	glMatrixMode(GL_PROJECTION);
								// Set the current openGL matrix to GL_PROJECTION ie projection matrix.
	glLoadIdentity();
								// Load identitiy values in the above.
	gluPerspective(90, (GLfloat)w/(GLfloat)h, 1.0, 200.0);

	glMatrixMode(GL_MODELVIEW);	
								// Change the current matrix mode to Model-View matrix.
	glLoadIdentity();
								

		glClearColor (0.0, 0.0, 0.0, 0.0);


	glClearColor (0.0, 0.0, 0.0, 0.0); 
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
}

void drawCylindre(float TopR, float BotR, float Height)
{

	GLUquadricObj* pObj;
	glPushMatrix();
							// To keep the original texture intact we need to set the current color to WHITE.

	pObj = gluNewQuadric();
							// Creates a new quadrics object and returns a pointer to it.
	gluQuadricDrawStyle(pObj, Wired_or_Shade);

	gluCylinder(pObj, TopR, BotR, Height, 20, 20);
							// Draw the cylinder with a radius : fRadius.
	gluDeleteQuadric(pObj);
							// Free the Quadric
	glPopMatrix();

}	

void showReferenceAxis(void)
						
{

	 glBegin(GL_LINES);
						// X axis red
      glColor3f(1, 0, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(10, 0, 0);
						// Y axis green
      glColor3f(0, 1, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 10, 0);
						// Z axis blue
      glColor3f(0, 0, 1);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, 10);
	  glEnd();
	
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cam_position[0] = cam_radius * sin(cam_phi) * sin(cam_theta);
	cam_position[1] = cam_radius * cos(cam_phi);
	cam_position[2] = cam_radius * sin(cam_phi) * cos(cam_theta);
	
	

	gluLookAt(cam_position[0],cam_position[1],cam_position[2],
			  cam_target[0], cam_target[1], cam_target[2],
			  cam_up[0], cam_up[1], cam_up[2]);

	showReferenceAxis();

	glColor3f(0.15, .75, 0.5);


	glPushMatrix();

	//glTranslatef(0.0,0, -2.0);
	glRotatef(90,0,1,0);

	glRotatef(-90,1,0,0);

	int height_increment;

	for(int i =0; i<100;i++)
	{

		height_increment = i;

		if (i>40)
		{
			height_increment = 40;
		}



		glTranslatef(0 , 0 , 0.5);

		glRotatef(-0.2*height_increment,1,0,0);

		glRotatef(2,0,1,0);

		glRotatef(2,0,0,1);

		drawCylindre(2.0,1.0,3);

				
		
		
		
		
	}

	glPopMatrix();

	
	


	//Sleep(5);
	glutSwapBuffers();


}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{

		case 'z':				// Move Camera forward.
			cam_radius -= 0.1;
			break;

		case 'Z' :				// Move Camera backward.
			cam_radius += 0.1;
			break;

		case 'w':
			Wired_or_Shade = GLU_FILL;
			break;

		case 'W':
			Wired_or_Shade = GLU_LINE;
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