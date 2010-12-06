#include <windows.h>
#include "glut.h"
#include <math.h>
#include <stdio.h>
 


class QuadricObjects
{


	
public:

	int *Wired_or_Shade; //= GLU_LINE;

	// Constructor
	QuadricObjects(void)//int *wired_or_shade )
	{

		// Put initialiazation here
		//Wired_or_Shade = wired_or_shade;
	}

	void SetWoS(int *wired_or_shade)
	{
		
		Wired_or_Shade = wired_or_shade;
	}


	void drawCylindre(float TopRadius, float BotRadius, float Height)
	{

		int CylindreDetailRadius = 8;
		int CylindreDetailHeight = 3;

		GLUquadricObj* CylindrePointer;

		glPushMatrix();		

		CylindrePointer = gluNewQuadric();
								
		gluQuadricDrawStyle(CylindrePointer, *Wired_or_Shade);

		gluCylinder(CylindrePointer, TopRadius, BotRadius, Height, CylindreDetailRadius, CylindreDetailHeight);
								
		gluDeleteQuadric(CylindrePointer);
								
		glPopMatrix();

	}	
		
	void drawCylindre(float TopRadius, float BotRadius, float Height, GLuint *Tex)
	{


	glPushAttrib(GL_ALL_ATTRIB_BITS); 

	//glColor4f(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	
//	glBindTexture(GL_TEXTURE_2D, *Tex );

		int CylindreDetailRadius = 8;
		int CylindreDetailHeight = 3;

		GLUquadricObj* CylindrePointer;

		glPushMatrix();		

		CylindrePointer = gluNewQuadric();
		
		gluQuadricNormals(CylindrePointer,GLU_SMOOTH);
							
	gluQuadricOrientation(CylindrePointer, GLU_OUTSIDE);
	gluQuadricTexture(CylindrePointer, GLU_TRUE);		
		
		
								
		gluQuadricDrawStyle(CylindrePointer, *Wired_or_Shade);

		gluCylinder(CylindrePointer, TopRadius, BotRadius, Height, CylindreDetailRadius, CylindreDetailHeight);
								
		gluDeleteQuadric(CylindrePointer);
	
		glDisable(GL_TEXTURE_2D);
									
		glPopMatrix();

			glPopAttrib();

	}	


	void drawCylindre(float TopRadius, float BotRadius, float Height, int CylindreDetailRadius,int CylindreDetailHeight)
	{

		GLUquadricObj* CylindrePointer;

				

		CylindrePointer = gluNewQuadric();
								
		gluQuadricDrawStyle(CylindrePointer, *Wired_or_Shade);

		gluCylinder(CylindrePointer, TopRadius, BotRadius, Height, CylindreDetailRadius, CylindreDetailHeight);
								
		gluDeleteQuadric(CylindrePointer);


	// int SLICES = CylindreDetailRadius;  
	//  int STACKS = CylindreDetailHeight;
	//  float SCALE_X =1 ;
	//  float SCALE_Y = 1;
	//  float SCALE_Z = 1;

	// 	  glEnable(GL_NORMALIZE);
	    
	//     //top of cylinder
	//     glBegin(GL_TRIANGLE_FAN);
	//         glNormal3f(0.0f, 0.0f, -1.0f);
	//         glVertex3f(0.0f, 0.0f, 0.0f);
	//         for (int i=0; i<=SLICES; ++i) {
	//             float x = SCALE_X * sin(i*2*M_PI/SLICES);
	//             float y = SCALE_Y * cos(i*2*M_PI/SLICES);
	//             glVertex3f(x, y, 0.0f);
	//         }
	//     glEnd();
	    
	//     //main part of cylinder
	//     for (int j=0; j<STACKS; ++j) {
	//         glBegin(GL_TRIANGLE_STRIP);
	//             for (int i=0; i<=SLICES; ++i) {
	//                 float x = SCALE_X * sin(i*2*M_PI/SLICES);
	//                 float y = SCALE_Y * cos(i*2*M_PI/SLICES);
	//                 float z = j * SCALE_Z / STACKS;
	//                 glNormal3f(x, y, 0.0f);
	//                 glVertex3f(x, y, z);
	//                  z = (j+1) * SCALE_Z / STACKS;
	//                 glVertex3f(x, y, z);
	//             }
	//         glEnd();
	//     }
	    
	//     //bottom of cylinder
	//     glBegin(GL_TRIANGLE_FAN);
	//         glNormal3f(0.0f, 0.0f, 1.0f);
	//         glVertex3f(0.0f, 0.0f, SCALE_Z);
	//         for (int i=0; i<=SLICES; ++i) 
	//         {
	//             float x = SCALE_X * sin(i*2*M_PI/SLICES);
	//             float y = SCALE_Y * cos(i*2*M_PI/SLICES);
	//             glVertex3f(x, y, SCALE_Z);
	//         }
	//     glEnd();					
		

	}	



	void drawSphere(float Radius, GLint Slices, GLint Rings)
	{


		GLUquadricObj* SpherePointer;

		glPushMatrix();		

		SpherePointer = gluNewQuadric();
								
		gluQuadricDrawStyle(SpherePointer, *Wired_or_Shade);

		gluSphere(SpherePointer, Radius, Slices, Rings);
								
		gluDeleteQuadric(SpherePointer);
								
		glPopMatrix();

	}






};
