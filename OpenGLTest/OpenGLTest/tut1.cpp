

#include <windows.h>
#include "glut.h"

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0); 
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
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

	/* everything we draw after this call is translated 6 units into the screen*/
	glTranslatef(0,0.0f,-6.0f);
	/* A glBegin call tells openGL we are drawing something. Since we will just feed the graphics card with vertex coordinates we need
	to tell before we start drawing what those vertexes mean....as in what shape we are drawing
	Even if we specify that we make triangles it doesn't mean we have to give 3 vertexes only....give it 6 vertexes and you get 2 triangles...9 vertexes and you get 3 triangles.*/
	glBegin(GL_POLYGON); 
		/*After setting the drawing color everything that follows will have that color. Yes, normaly you would set one color for the whole object
		but I'm going to show you that you can set individual colors for each vertex your draw. How is the object going to look like then? 
		Well OpenGL will do a gradient between the 2 colors you set for neighbouring vertexes*/
		glColor3f(1.0f,0.0f,0.0f);
		/* This function will put a vertex at the given coordinates */
		glVertex3f( 0.0f, 1.0f, 0.0f); 
		/* we change the color again - note if we didn't change it then openGL would simply use the last color we gave*/
        glColor3f(0.0f,1.0f,0.0f); // Set The Color To Green
		//glVertex3f(-1.0f,-1.0f, 0.0f); 
        glColor3f(0.0f,0.0f,1.0f); // Set The Color To Blue
		glVertex3f( 1.0f,-1.0f, 0.0f);
		glVertex3f(1.0f,2.0f,1.0f); 
		//glVertex3f(2.0f,0.0f,0.0f);
		//glVertex3f(0.0f,0.0f,2.0f);
		glVertex3f(0.0f,4.0f,0.0f);

	glEnd(); // Done Drawing A Triangle

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
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}