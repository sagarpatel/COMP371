
			// Glut objects exmaple

/****************************************************************************************/
/* 
/* Drawing some of the glut objects using OpenGL.
/* DATED 4th May 2004		RAMGOPAL R		r_rajago@cs.concordia.ca
/* 
/****************************************************************************************/
#include <windows.h>
#include "glut.h"
#include <stdio.h>

#define SIZE 600	
#define NEAR_Z 1.0
#define FAR_Z 100.0	// For the frustum size.

#define  GLUT_WIRE_CUBE 11
#define  GLUT_SOLID_CUBE 12
#define  GLUT_WIRE_SPHERE 13
#define  GLUT_SOLID_SPHERE 14
#define  GLUT_WIRE_OCT 15
#define  GLUT_SOLID_OCT 16
#define  GLUT_WIRE_TORUS 17 
#define  GLUT_SOLID_TORUS 18
#define  GLUT_WIRE_TEAPOT 19
#define  GLUT_SOLID_TEAPOT 110
		

float x_Angle ;		// The rotation angles about x, y and z axis.
float y_Angle ;
float z_Angle ;

int choice;			// Selected glut object is stored in this variable as an identifier.

/****************************************************************************************/
void showMenu(void)
{
	//clear();
	printf("\n\n ********************************************************************");
	printf("\n OpenGL PROGRAM FOR DRAWING SAMPLE GLUT OBJECTS.\n");
	printf("\n DATED 4th MAY 2004 \n");
	printf("********************************************************************\n");
	printf("\n\n Operations: ");
	printf("\n Use the s/S,c/C, t/T, p/P or o/O for different glut shapes.");
	printf("\n Use the x/X,y/Y and z/Z keys for rotations about x,y and z axes.");
	printf("\n Use m or M to see this menu again.");

}

/****************************************************************************************/
	void init (void)
							// Initializes the gl Graphics env and the program variables.
	{
		x_Angle = 45.0;
		y_Angle = 0.0;
		z_Angle = 45.0;
		
		choice = 19;
		glEnable(GL_DEPTH_TEST);	// Enable z-Buffering.
		showMenu();
	}


/****************************************************************************************/
	void keyboardCallbackProc(unsigned char key, int x, int y)
							// This is the callback procedure for capturing OpenGL Keyboard events.
	{
		switch(key)
		{
		case 'x':
			x_Angle += 1;
			break;
		case 'X':
			x_Angle -= 1;
			break;
		case 'y':
			y_Angle += 1;
			break;
		case 'Y':
			y_Angle -= 1;
			break;
		case 'z':
			z_Angle += 1;
			break;
		case 'Z':
			z_Angle -= 1;
			break;

		case 'c':
			choice = GLUT_WIRE_CUBE;
			break;
		case 'C':
			choice = GLUT_SOLID_CUBE;
			break;
		case 's':
			choice = GLUT_WIRE_SPHERE;
			break;
		case 'S':
			choice = GLUT_SOLID_SPHERE;
			break;
		case 'o':
			choice = GLUT_WIRE_OCT;
			break;
		case 'O':
			choice = GLUT_SOLID_OCT;
			break;
		case 't':
			choice = GLUT_WIRE_TORUS;
			break;
		case 'T':
			choice = GLUT_SOLID_TORUS;
			break;
		case 'p':
			choice = GLUT_WIRE_TEAPOT;
			break;
		case 'P':
			choice = GLUT_SOLID_TEAPOT;
			break;
		case 'M' :
		case 'm' :
			showMenu();
			break;
		case 27 :				//ESCAPE Code for exiting program.
			exit(0);
		}
		glutPostRedisplay();
	}

/****************************************************************************************/
	void reShapeCallbackProc(int w, int h)
							// This is the callback procedure for capturing reShape event for window resizing.
	{
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION); 
		glLoadIdentity();
		gluPerspective(60.0, (GLfloat)w/(GLfloat)h, NEAR_Z, FAR_Z);

		glMatrixMode(GL_MODELVIEW);
	}


/****************************************************************************************/
	void displayCallbackProc (void)
							// This is the callback procedure for capturing OpenGL Display events.
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		
		glTranslatef(2, -1, -5);	// Translate the object by 5 units in -ve z-direction.
		
		glRotatef(x_Angle, 1.0, 0.0, 0.0);	// Rotate the object by x_Angle about x-axis
		glRotatef(y_Angle, 0.0, 1.0, 0.0);	// Rotate the object by y_Angle about y-axis
		glRotatef(z_Angle, 0.0, 0.0, 1.0);	// Rotate the object by z_Angle about z-axis

		switch(choice)
		{
		case GLUT_WIRE_CUBE:
			glutWireCube(1.0);
			break;
		case GLUT_SOLID_CUBE:
			glutSolidCube(1.0);
			break;
		case GLUT_WIRE_SPHERE:
			glutWireSphere(1.0, 15.0, 15.0);
			break;
		case GLUT_SOLID_SPHERE:
			glutSolidSphere(1.0, 15.0, 15.0);
			break;
		case GLUT_WIRE_OCT:
			glutWireOctahedron();
			break;
		case GLUT_SOLID_OCT:
			glutSolidOctahedron();
			break;
		case GLUT_WIRE_TORUS:
			glutWireTorus(0.5, 1.5, 20, 25);
			break;
		case GLUT_SOLID_TORUS:
			glutSolidTorus(0.5, 1.5, 20, 25);
			break;
		case GLUT_WIRE_TEAPOT:
			glutWireTeapot(1.0);
			break;
		case GLUT_SOLID_TEAPOT:
			glutSolidTeapot(1.0);
			break;

		}

		glutSwapBuffers();
	}

/****************************************************************************************/
	int main (int argc, char *argv[])
							// The main program.
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(SIZE, SIZE);
		glutInitWindowPosition(350, 200);

		glutCreateWindow("Sample Glut objects.");

		init();				// Initialize the env. variables and the program global variables.

		/* Callback registrations with the OpenGL env are done here */
		
		glutDisplayFunc(displayCallbackProc);
		glutKeyboardFunc(keyboardCallbackProc);
		glutReshapeFunc(reShapeCallbackProc);

		/* Callback registrations done.*/

		glutMainLoop();
		return 1;
	}

/*************************** END OF PROGRAM ************************************************/





















				// 6 2d faces  = cube example

//
//
//
///****************************************************************************************/
///* 
///* Drawing a cube using OpenGL.
///* DATED 4th May 2004		RAMGOPAL R		r_rajago@cs.concordia.ca
///* 
///****************************************************************************************/
//
//	#include "glut.h"
//	#include <stdio.h>
//
//	#define SIZE 600	
//	#define NEAR_Z 1.0
//	#define FAR_Z 100.0	// For the frustum size.
//
//	float x_Angle ;		// The rotation angles about x, y and z axis.
//	float y_Angle ;
//	float z_Angle ;
//
//	typedef GLfloat Point[3];
//
//	Point pt[] = {
//	{ -3.0, -3.0, 3.0 },
//	{ -3.0, 3.0, 3.0 },
//	{ 3.0, 3.0, 3.0 },
//	{ 3.0, -3.0, 3.0 },
//	{ -3.0, -3.0, -3.0 },
//	{ -3.0, 3.0, -3.0 },
//	{ 3.0, 3.0, -3.0 },
//	{ 3.0, -3.0, -3.0 } };	// Definition of the vertices of the cube.
//
//	typedef GLfloat COLOR[3];
//	COLOR arrColor[] = {
//	{ 1.0, 0.0, 0.0 },
//	{ 0.0, 1.0, 0.0 },
//	{ 0.0, 0.0, 1.0 },
//	{ 1.0, 0.0, 1.0 },
//	{ 0.0, 1.0, 1.0 },
//	{ 1.0, 1.0, 0.0 }
//	};						// Definition of the RGB color codes for each side of the cube.
//
//
///****************************************************************************************/
//	void drawSide (int v0, int v1, int v2, int v3,int iColor)
//							// Draws one side of the cube and colors it.
//	{
//		glColor3fv(arrColor[iColor]);
//							// Specifying color
//		glBegin(GL_POLYGON);
//		glVertex3fv(pt[v0]);
//		glVertex3fv(pt[v1]);
//		glVertex3fv(pt[v2]);
//		glVertex3fv(pt[v3]);
//		glEnd();
//	}
//
///****************************************************************************************/
//	void drawCube (void)
//							// Draws the color cube.
//	{
//		drawSide(0, 3, 2, 1, 0);
//		drawSide(2, 3, 7, 6, 1);
//		drawSide(0, 4, 7, 3, 2);
//		drawSide(1, 2, 6, 5, 3);
//		drawSide(4, 5, 6, 7, 4);
//		drawSide(0, 1, 5, 4, 5);
//	}
//
///****************************************************************************************/
//void showMenu(void)
//{
//	//clear();
//	printf("\n\n ********************************************************************");
//	printf("\n OpenGL PROGRAM FOR DRAWING A CUBE \n");
//	printf("\n DATED 4th MAY 2004 \n");
//	printf("********************************************************************\n");
//	printf("\n\n Operations: ");
//	printf("\n Use the x/X,y/Y and z/Z keys for rotations about x,y and z axes.");
//	printf("\n Use m or M to see this menu again.");
//
//}
//
///****************************************************************************************/
//	void init (void)
//							// Initializes the gl Graphics env and the program variables.
//	{
//		x_Angle = 45.0;
//		y_Angle = 0.0;
//		z_Angle = 45.0;
//		
//		glEnable(GL_DEPTH_TEST);	// Enable z-Buffering.
//		showMenu();
//	}
//
//
///****************************************************************************************/
//	void keyboardCallbackProc(unsigned char key, int x, int y)
//							// This is the callback procedure for capturing OpenGL Keyboard events.
//	{
//		switch(key)
//		{
//		case 'x':
//			x_Angle += 0.1;
//			break;
//		case 'X':
//			x_Angle -= 0.1;
//			break;
//		case 'y':
//			y_Angle += 0.1;
//			break;
//		case 'Y':
//			y_Angle -= 0.1;
//			break;
//		case 'z':
//			z_Angle += 0.1;
//			break;
//		case 'Z':
//			z_Angle -= 0.1;
//			break;
//		case 'M' :
//		case 'm' :
//			showMenu();
//			break;
//		case 27 :				//ESCAPE Code for exiting program.
//			exit(0);
//		}
//		glutPostRedisplay();
//	}
//
///****************************************************************************************/
//	void reShapeCallbackProc(int w, int h)
//							// This is the callback procedure for capturing reShape event for window resizing.
//	{
//		glViewport(0, 0, w, h);
//		glMatrixMode(GL_PROJECTION); 
//		glLoadIdentity();
//		gluPerspective(60.0, GLfloat(w)/GLfloat(h), NEAR_Z, FAR_Z);
//
//		glMatrixMode(GL_MODELVIEW);
//	}
//
//
///****************************************************************************************/
//	void displayCallbackProc (void)
//							// This is the callback procedure for capturing OpenGL Display events.
//	{
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glMatrixMode(GL_MODELVIEW);
//
//		glLoadIdentity();
//
//		glTranslatef(0, 0, -10.0);	// Translate the object by 10 units in -ve z-direction.
//		
//		glRotatef(x_Angle, 1.0, 0.0, 0.0);	// Rotate the object by x_Angle about x-axis
//		glRotatef(y_Angle, 0.0, 1.0, 0.0);	// Rotate the object by y_Angle about y-axis
//		glRotatef(z_Angle, 0.0, 0.0, 1.0);	// Rotate the object by z_Angle about z-axis
//
//		drawCube();		// Draw the cube.
//
//		glutSwapBuffers();
//	}
//
///****************************************************************************************/
//	int main (int argc, char *argv[])
//							// The main program.
//	{
//		glutInit(&argc, argv);
//		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//		glutInitWindowSize(SIZE, SIZE);
//		glutInitWindowPosition(350, 200);
//
//		glutCreateWindow("Primitive Operations on a Colored Cube using Perspective Projection.");
//
//		init();				// Initialize the env. variables and the program global variables.
//
//		/* Callback registrations with the OpenGL env are done here */
//		
//		glutDisplayFunc(displayCallbackProc);
//		glutKeyboardFunc(keyboardCallbackProc);
//		glutReshapeFunc(reShapeCallbackProc);
//
//		/* Callback registrations done.*/
//
//		glutMainLoop();
//		return 1;
//	}
//
///*************************** END OF PROGRAM ************************************************/
//
//
//
//
//
//
//
//

















					// 2D Line example




//#include "glut.h"      // (or others, depending on the system in use)
//
//void init (void)
//{
//    glClearColor (1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
//
//    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
//    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
//}
//
//void lineSegment (void)
//{
//    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.
//
//    glColor3f (0.0, 0.0, 1.0);      // Set line segment color to red.
//    glBegin (GL_LINES);
//        glVertex2i (180, 15);       // Specify line-segment geometry.
//        glVertex2i (100, 145);
//    glEnd ( );
//
//    glFlush ( );     // Process all OpenGL routines as quickly as possible.
//}
//
//void main (int argc, char** argv)
//{
//    glutInit (&argc, argv);                         // Initialize GLUT.
//    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
//    glutInitWindowPosition (50, 100);   // Set top-left display-window position.
//    glutInitWindowSize (400, 300);      // Set display-window width and height.
//    glutCreateWindow ("An Example OpenGL Program"); // Create display window.
//
//    init ( );                            // Execute initialization procedure.
//    glutDisplayFunc (lineSegment);       // Send graphics to display window.
//    glutMainLoop ( );                    // Display everything and wait.
//}
