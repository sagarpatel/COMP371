
#include <windows.h>
#include "glut.h"
#include <math.h>
#include <stdio.h>

#include "QuadricObjects.h"
 


class DragonModel : public QuadricObjects
{
public:

	

	DragonModel(int *wired_or_shade) : QuadricObjects()
	{
		// Initiliazation Code Here
		SetWoS(wired_or_shade);

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

	void drawWings(void)
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


	void drawArms(void)
	{

		drawRightArm();
		
		glPushMatrix();

		glScalef(-1,1,1);
		drawRightArm();

		glPopMatrix();

	}

	void drawLeftLeg(void)
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

	void drawLegs(void)
	{

		drawLeftLeg();

		glPushMatrix();

		glScalef(-1,1,1);

		drawLeftLeg();

		glPopMatrix();
		

	}


	void drawHead(void)
	{
			

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


	void drawDragon(void)
	{
		

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
	//		glColor3f(0.15625, 0.54296875, 0.236328125);
		

		glPushMatrix();

		//glTranslatef(0.0,0, -2.0);
		glRotatef(90,0,1,0);

		glRotatef(-90,1,0,0);

		drawTail();

		drawBody();

		drawHead();


		glPopMatrix();


	}

	


};
