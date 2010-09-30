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

	cam_radius = 100;

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
	

}

void drawCylindre(float TopRadius, float BotRadius, float Height)
{

	int CylindreDetailRadius = 20;
	int CylindreDetailHeight = 8;

	GLUquadricObj* CylindrePointer;

	glPushMatrix();		

	CylindrePointer = gluNewQuadric();
							
	gluQuadricDrawStyle(CylindrePointer, Wired_or_Shade);

	gluCylinder(CylindrePointer, TopRadius, BotRadius, Height, CylindreDetailRadius, CylindreDetailHeight);
							
	gluDeleteQuadric(CylindrePointer);
							
	glPopMatrix();

}	


void drawCylindre(float TopRadius, float BotRadius, float Height, int CylindreDetailRadius,int CylindreDetailHeight)
{

	GLUquadricObj* CylindrePointer;

			

	CylindrePointer = gluNewQuadric();
							
	gluQuadricDrawStyle(CylindrePointer, Wired_or_Shade);

	gluCylinder(CylindrePointer, TopRadius, BotRadius, Height, CylindreDetailRadius, CylindreDetailHeight);
							
	gluDeleteQuadric(CylindrePointer);
							
	

}	

void drawCone(float BaseRadius, float Height)
{

	drawCylindre(BaseRadius,0, Height,10,2);
}

void drawSpikes(float BaseRadius, float Height)
{
	//Transform Cones to make spikes on back of dragon


	glPushMatrix();
	//glColor3f(0,0,0); //Black spikes
		
		// Gold
		// Original Code: 255-215-0
		//glColor3f(0.99609375, 0.83984375, 0);
	// Moded gold
	//glColor3f(0.99609375, 0.83984375, 0.45);

	// Dark Green
	// Original Code: 0-100-0
	//glColor3f(0.0, 0.390625, 0.0);

	//Manually tweaked value
	glColor3f(0,0.25,0.05);

	glScalef(1,1,4);

	glRotatef(-90,1,0,0); // Rotation to dragon's back
		
	glTranslatef(0,-0.5,0);  
	
	glRotatef(45,0,1,0); //Rotate to side anlge

	

	drawCone(BaseRadius,Height);

	glRotatef(-90,0,1,0);
	drawCone(BaseRadius,Height);


	glPopMatrix();

		//Return to Body Color

		glColor3f(0.15625, 0.54296875, 0.236328125);
	


}


void drawSphere(float Radius, GLint Slices, GLint Rings)
{


	GLUquadricObj* SpherePointer;

	glPushMatrix();		

	SpherePointer = gluNewQuadric();
							
	gluQuadricDrawStyle(SpherePointer, Wired_or_Shade);

	gluSphere(SpherePointer, Radius, Slices, Rings);
							
	gluDeleteQuadric(SpherePointer);
							
	glPopMatrix();

}


void drawBelly(void)
{

	//Draw Belly/Underside
		//Wheat
		//Orignal Code : 245-222-179
			glColor3f(0.95703125, 0.8671875, 0.69921875);

		glPushMatrix();
		glTranslatef(0,-1.0,0);
		drawSphere(3.0,10,10);
		glPopMatrix();

		//Return to Body Color

		glColor3f(0.15625, 0.54296875, 0.236328125);
	
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

	// Orignal Color (hand tweaked)
	//	glColor3f(0.15, .75, 0.5);

	// Forest Green (http://www.tayloredmktg.com/rgb/)
	// Original code : 34-139-34
	//	glColor3f(0.1328125, 0.54296875, 0.1328125);

	// Sea Green
	// Original Code : 46-139-87
	//	glColor3f(0.1796875, 0.54296875, 0.33984375);

	//Average of Forest and Sea
		glColor3f(0.15625, 0.54296875, 0.236328125);
	

	glPushMatrix();

	//glTranslatef(0.0,0, -2.0);
	glRotatef(90,0,1,0);

	glRotatef(-90,1,0,0);

	int height_increment;

	for(int i =0; i<100;i++)
	{

		height_increment = i;

		if (i>20)
		{
			height_increment = 20;
		}
		if (i>40)
		{
			height_increment = 40;
		}

		if (i>100)
		{
			height_increment = 10;
		}

	
		glTranslatef(0 , 0 , 1.5);
		glRotatef(-0.2*height_increment,1,0,0);
		glRotatef(2,0,1,0);
		glRotatef(2,0,0,1);

		drawCylindre(3.0,1.5,5);

		drawBelly();

	//	showReferenceAxis();

		if(i<50)
		{
		drawSpikes(1,4);
		}
		if(i>=50)
		{
			
			drawSpikes(1,4.5);
		}				
		
	}



	for(int j =0; j<50; j++)
	{

		height_increment = j;

		if (j>20)
		{
			height_increment = 20;
		}
	
		glTranslatef(0 , 0 , 1.5);

		glRotatef(0.235*height_increment,1,0,0);

		glRotatef(2,0,1,0);

		glRotatef(2,0,0,1);

		drawCylindre(3.0,1.5,5);
		
		drawBelly();
		
		drawSpikes(1,4.7);	
		
	}



	for(int k =0; k<50; k++)
	{

		height_increment = k;

		if (k>10)
		{
			height_increment = 40;
		}

	
		glTranslatef(0 , 0 , 1.5);

		glRotatef(0.2*height_increment,1,0,0);

		glRotatef(2,0,1,0);

		glRotatef(4,0,0,1);

		drawCylindre(3.0,1.5,5);
		
		drawBelly();
		
		drawSpikes(1,4.6);		
		
	}


	for(int l =0; l<30; l++)
	{

		height_increment = l;

		if (l>1)
		{
			height_increment = 40;
		}

	
		glTranslatef(0 , 0 , 1.5);

		glRotatef(-0.2*height_increment,1,0,0);

		//glRotatef(2,0,1,0);

		glRotatef(4,0,0,1);

		drawCylindre(3.0,1.5,5);
		
		drawBelly();

		drawSpikes(1,4.7);			
		
	}

	for(int m =0; m<10; m++)
	{

		glTranslatef(0 , 0 , 1.5);

		drawCylindre(3.0,1.5,5);	
		
		drawBelly();
		
		drawSpikes(1,4.75);	
		
	}


	for(int n =0; n<15; n++)
	{
	
		glTranslatef(0 , 0 , 1.5);

		glRotatef(4,0,1,0);

		glRotatef(4,1,0,0);

		//Fix rotation for neck/head
		glRotatef(5,0,0,1);
		glRotatef(-1,0,1,0);
	//	showReferenceAxis();

		drawCylindre(3.0,1.5,5);	
		
		drawBelly();

		drawSpikes(1,4.8);
		
	}

	glRotatef(-17,0,0,1);


	for(int m =0; m<15; m++)
	{

		glTranslatef(0 , 0 , 1.5);

		glRotatef(-10,1,0,0);

		drawCylindre(3.0,1.5,5);	

		drawBelly();

		drawSpikes(1,4.85);
		
	}

	for(int m =0; m<14; m++)
	{

		glTranslatef(0 , 0 , 1.5);

		glRotatef(15,1,0,0);

		drawCylindre(3.0,1.5,5);	
		
		drawBelly();
		
		drawSpikes(1,5);		
		
	}

	glTranslatef(0 , 0 , 1.5);

	glRotatef(-15,1,0,0);

	drawCylindre(3.0,1.5,5);	
		
	drawBelly();



	glTranslatef(0 , 0 , 1.5);

	glRotatef(-15,1,0,0);

	drawCylindre(3.0,1.5,5);	
		
	drawBelly();


	drawCylindre(5.0,1.0,10);





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
			cam_radius -= 0.5;
			break;

		case 'Z' :				// Move Camera backward.
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

		case 'p':
			Wired_or_Shade = GLU_POINT;
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