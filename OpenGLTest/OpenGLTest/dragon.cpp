// COMP 371 Asg1
// Sagar Patel 9356037

// This code uses parts of pilotView.c sample provided in the Lab.
// This usage is mainly limited to camera fucntions.

// Texture code from http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=06



#include <windows.h>
#include "glut.h"
#include <math.h>
#include <stdio.h>


#define PI 3.14159265

GLdouble cam_position[3];	
GLdouble cam_target[3];	
GLdouble cam_up[3];	



double cam_theta;
double cam_phi;
double cam_radius;

int h,w;

int Wired_or_Shade = GLU_LINE;

bool orthogonalFlag = false;


void init(void) 
{

	cam_radius = 100;

	// Setting cam position to origin
	// It is irreleveant since radius has been set to 10,
	// therefore, thses values will be recalculated later.
	cam_position[0] = 15;
	cam_position[1] = 15;
	cam_position[2] = -15;

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
								
	gluPerspective(90, (GLfloat)w/(GLfloat)h, 1.0, 200.0);

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



AUX_RGBImageRec LoadBMP(char *Filename)
{
	FILE *File=NULL;
	if (!Filename)
	{
		return NULL;
	}

	File=fopen(Filename,"r");

	if (File)
	{
		fclose(File);
		return auxDIBImageLoad(Filename);
	}

	return NULL;
}

void LoadTextures(void)
{
	
	AUX_RGBImageRec *TextureArray[1];

	memset(TextureImage,0,sizeof(void *)*1);

	TextureImage[0]=LoadBMP("GroundTex.bmp")

	// -> points the size of image,H and W
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->256, TextureImage[0]->256, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

	// Linear filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


	if (TextureImage[0])							// If Texture Exists
	{
		if (TextureImage[0]->data)					// If Texture Image Exists
		{
			free(TextureImage[0]->data);				// Free The Texture Image Memory
		}

		free(TextureImage[0]);						// Free The Image Structure
	}

}












void drawCylindre(float TopRadius, float BotRadius, float Height)
{

	int CylindreDetailRadius = 8;
	int CylindreDetailHeight = 3;

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

void drawCone(float BaseRadius, float Height)
{

	drawCylindre(BaseRadius,0, Height,8,2);
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
		drawSphere(3.0,15,15);
		glPopMatrix();

		//Return to Body Color

		glColor3f(0.15625, 0.54296875, 0.236328125);
	
}

void drawBelly(float Radius)
{

	//Draw Belly/Underside
		//Wheat
		//Orignal Code : 245-222-179
			glColor3f(0.95703125, 0.8671875, 0.69921875);

		glPushMatrix();
		glTranslatef(0,-1.0,0);
		drawSphere(Radius,15,15);
		glPopMatrix();

		//Return to Body Color

		glColor3f(0.15625, 0.54296875, 0.236328125);
	
}

void drawLeftWing(void)
{
	glPushMatrix();

	glTranslatef(0,2,0);

//	drawCylindre(float TopRadius, float BotRadius, float Height, int CylindreDetailRadius,int CylindreDetailHeight)
	
//Orignal Wing code
	glPushMatrix();
	glRotatef(60,0,1,0);
	glRotatef(-35,1,0,0);


	//First part of wing, stuck to back of body
	glPushMatrix();
	glScalef(1,0.15,1);
	drawCylindre(1, 3, 6, 5,3);
	glPopMatrix();


	//Second part of wing, widest

	glTranslatef(0,0,5);
	
	glRotatef(15,0,1,0);
	glRotatef(-25,1,0,0);
	//glRotatef(180,0,0,1);
	
	glPushMatrix();
	glScalef(1,0.15,1);
	drawCylindre(3,5,7,5,3);
	glPopMatrix();

	//Last part of wing

	
	glTranslatef(0,0,6.75);

	glRotatef(-25,1,0,0);
	glScalef(1,0.15,1);
	//showReferenceAxis();
	drawCylindre(5,1,4,5,3);
	
	glPopMatrix();

	glPopMatrix();



}

void drawWings()
{
	
	//showReferenceAxis();


	//glColor3f(0,0.2,0);
glPushAttrib(GL_CURRENT_BIT);

//Draw Left Wing
	drawLeftWing();

//Draw Right Wing
	glScalef(-1,1,1); //Does mirror image
	drawLeftWing();
	
glPopAttrib();


}

void drawTail(void)
{

	glPushAttrib(GL_CURRENT_BIT);

	glPushMatrix();

	glTranslatef(0,0,1);

	int height_increment;

	for(int i = 0; i<60; i++)
	{

		//showReferenceAxis();

		height_increment = i;

		glTranslatef(0 , 0 , -1.5);
		//glRotatef(-0.2*height_increment,-1,0,0);
		
		if (i <30)
		{
			glRotatef(4,1,0,0);

			glRotatef(-0.5*height_increment,0,1,0);
		}

		if (i>=30 && i < 45)
		{
			glRotatef(4,0,1,0);
			glRotatef(-9,1,0,0);
			glRotatef(4,0,0,1);
		}


		if (i>=50)
		{
			glRotatef(4,0,0,1);
			glRotatef(7,1,0,0);
		}

		drawSpikes(1,4);

		if(i<57)
		{
			drawCylindre(3.0,1.5,5);
		}

		if (i<=42)
		{
			drawBelly();
		}

		if( i>42 && i<53)
		{
			drawBelly(3-0.01*i);

		}

		if(i>50)
		{
			glPushMatrix();

			glTranslatef(0,4,5);
			glScalef(1,-2,1);

			drawSpikes(2,4.5);
			glPopMatrix();

		}

		if(i>=57)
		{
			glPushMatrix();
			glTranslatef(0,2,0);
			glScalef(1.25,-1.25,1.25);			
			drawSpikes(2,4);
			glPopMatrix();
		}
	}

	glPopMatrix();

	glPopAttrib();

}

void drawRightArm(void)
{

	int	bicep_length = 8;
	int forearm_length = 7;

	glPushAttrib(GL_CURRENT_BIT);

	glPushMatrix();
	glRotatef(35,0,1,0);
	drawCylindre(1,1,bicep_length);

	glTranslatef(0,0,bicep_length);
	

	drawSphere(1.15,10,10);

	glRotatef(130,0 ,1,0);
	drawCylindre(1,1,forearm_length);

	glTranslatef(0,0,forearm_length);

//Draw hand
	glPushMatrix();

	//showReferenceAxis();
	glScalef(1.1,1.1,1.5);
	drawSphere(1.2,10,10);

	glPopMatrix();

//Draw fingers
	
	glScalef(1.15,1.15,1.15);

	glColor3f(0,0,0);
	
	glTranslatef(0.15,0,0.1);

	glPushMatrix();
	glRotatef(60,0,1,0);
	drawCylindre(1,0,2);
	glPopMatrix();

	glTranslatef(0,-0.4,0.5);
	glRotatef(30,1,0,0);
	drawCylindre(0.75,0,1.5);

	glTranslatef(-0.5,0,0.2);
	glRotatef(-30,0,1,0);
	glTranslatef(0,0.2,-0.5);
	drawCylindre(1,0,1.5);

	glPopMatrix();
	

	glPopAttrib();

}


void drawArms()
{

	drawRightArm();
	
	glPushMatrix();

	glScalef(-1,1,1);
	drawRightArm();

	glPopMatrix();

}

void drawLeftLeg()
{
	
	int	bicep_length = 7;
	int forearm_length = 5;

	glPushAttrib(GL_CURRENT_BIT);

	glPushMatrix();
	glTranslatef(2,0,0);
	glRotatef(111,0,1,0);
	glRotatef(-45,0,0,1);
	//showReferenceAxis();
	drawCylindre(1,1,bicep_length);

	glTranslatef(0,0,bicep_length);
	

	drawSphere(1.15,10,10);

	glRotatef(100,0 ,1,0); // joint angle
	drawCylindre(1,1,forearm_length);

	glTranslatef(0,0,forearm_length);

//Draw hand
	glPushMatrix();

	//showReferenceAxis();
	glScalef(1.1,1.1,1.5);
	drawSphere(1.2,10,10);

	glPopMatrix();

//Draw fingers
	
	glScalef(1.15,1.15,1.15);

	glColor3f(0,0,0);
	
	glTranslatef(0.15,0,0.1);

	glPushMatrix();
	glRotatef(60,0,1,0);
	drawCylindre(1,0,2);
	glPopMatrix();

	glTranslatef(0,-0.4,0.5);
	glRotatef(30,1,0,0);
	drawCylindre(0.75,0,1.5);

	glTranslatef(-0.5,0,0.2);
	glRotatef(-30,0,1,0);
	glTranslatef(0,0.2,-0.5);
	drawCylindre(1,0,1.5);

	glPopMatrix();
	

	glPopAttrib();



}

void drawLegs()
{

	drawLeftLeg();

	glPushMatrix();

	glScalef(-1,1,1);

	drawLeftLeg();

	glPopMatrix();
	

}
void drawBody(void)
{
	

	int height_increment;

	for(int i =0; i<100;i++)
	{

		if(i==1)
		{
			drawLegs();
		}		

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

		if(m == 5)
		{
			drawWings();
		}
		
	}

	drawArms();

	for(int m =0; m<14; m++)
	{

		glTranslatef(0 , 0 , 1.5);

		glRotatef(15,1,0,0);

		drawCylindre(3.0,1.5,5);	
		
		drawBelly();
		
		if(m<12)
		{
			drawSpikes(1,5);		
		}
	}

	glTranslatef(0 , 0 , 1.5);

	glRotatef(-15,1,0,0);

	drawCylindre(3.0,1.5,5);	
		
	drawBelly();



	glTranslatef(0 , 0 , 1.5);

	glRotatef(-15,1,0,0);

	drawCylindre(3.0,1.5,5);	
		
	//drawBelly();




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

	//showReferenceAxis();

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

	drawTail();

	drawBody();


	

//Head Code

	glPushMatrix();

	glTranslatef(0,0,-2);
	drawCylindre(5,1.20,9.3,20,20);

	glPopMatrix();

//Mouth Code

glColor3f(0, 0.4, 0);

	glPushMatrix();
	glTranslatef(0,0,5);
	glRotatef(15,1,0,0);
	//glColor3f(0,0,1);
	glScalef(0.75,0.75,1);
	drawSphere(3.2,20,20);
	glPopMatrix();



//Eyes code

	//showReferenceAxis();

	glColor3f(0.5,0,0);
	glTranslatef(0,3,2);
	

	glPushMatrix();
	glTranslatef(-2,0,0);
	glRotatef(-40,0,1,0);
	glScalef(1,0.4,0.5);
	//showReferenceAxis();
	drawSphere(1.5,10,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2,0,0);
	glRotatef(40,0,1,0);
	glScalef(1,0.4,0.5);
	//showReferenceAxis();
	drawSphere(1.5,10,10);
	glPopMatrix();



//Ears code

	//showReferenceAxis();

	glColor3f(0,0.1,0);
	glTranslatef(0,-2,-3);
	

	glPushMatrix();
	glTranslatef(-4,0,0);
	glRotatef(-40,0,1,0);
	glScalef(0.5,1,0.2);
	//showReferenceAxis();
	drawSphere(3,10,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,0,0);
	glRotatef(40,0,1,0);
	glScalef(0.5,1,0.2);
	//showReferenceAxis();
	drawSphere(3,10,10);
	glPopMatrix();



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
	gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{

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
		
		case 'o':
			orthogonalFlag = true;
			break;
		case 'O':
			orthogonalFlag = true;

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