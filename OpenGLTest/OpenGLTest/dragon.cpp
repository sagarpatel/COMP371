

#include <windows.h>
#include "glut.h"

void init(void) 
{
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
	gluQuadricDrawStyle(pObj, GLU_LINE);

	gluCylinder(pObj, TopR, BotR, Height, 20, 20);
							// Draw the cylinder with a radius : fRadius.
	gluDeleteQuadric(pObj);
							// Free the Quadric
	glPopMatrix();

}	

void display(void)
	{
	/* First of all we clear both the screen (The color buffer) and the depth buffer on your video card
	The depth buffer can tell us the depth of each pixel on the screen, so when we draw something object in the back will
	no overwrite object in the front :)
	We want this information gone too since we now render a new frame*/

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* Loading the Identity matrix means we reset the screen coordinate system to XYZ axis of lenght 1:
	The screen starts at z=0, x=-1 to x=1 and y=-1 to y=1 */
	glLoadIdentity ();

	glTranslatef(0.0,0, -20.0);
	glRotatef(90,1,0,0);

	for(int i =0; i<10;i++)
	{

		glTranslatef(0.1*i , 0 , 0);

		drawCylindre(2.0,1.0,3);
		
	}

	gluLookAt(0,10,0,0,0,0,0,0,0);


	//Sleep(5);
	glutSwapBuffers();


}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
		case 27: // ESC key
		exit(0);
		break; 
	}
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
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}