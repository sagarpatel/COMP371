#include <windows.h>
#include <stdlib.h>
#include "glut.h"

static float shoulder_angle = 0; 
static float elbow_angle = 0;

static float arm1_length = 3.0f;
static float arm2_length = 2.0f;

static float finger1_angle = 30.0f;
static float finger2_angle = 40.0f;
static float finger_length = 0.5f;

void init(void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix();

        glTranslatef(-arm1_length/2, 0.0, 0.0);
        glRotatef((float)shoulder_angle, 0.0, 0.0, 1.0);
        glTranslatef(arm1_length/2, 0.0, 0.0); 
        glPushMatrix();
            glScalef(arm1_length, 2.0, 1.0);
            glutWireCube (1.0);
        glPopMatrix();

        glTranslatef(arm1_length/2, 0.0, 0.0);
        glRotatef((float)elbow_angle, 0.0, 0.0, 1.0);
        glTranslatef(arm2_length/2, 0.0, 0.0);
        glPushMatrix();
            glScalef(arm2_length, 0.4, 1.0);
            glutWireCube (1.0);
        glPopMatrix();
        
        //@Practice:
        //Add more fingers
        glTranslatef(arm2_length/2,0.0f,0.0f);        
        glPushMatrix();
            glRotatef(finger1_angle,0.0f,0.0f,1.0f);
            glTranslatef(finger_length/2,0.0f,0.0f);
            glPushMatrix();
                glScalef(finger_length,0.1f,0.1f);
                glutWireCube(1.0f);
            glPopMatrix();
        glPopMatrix();
        
    glPopMatrix();
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f,0.0f,7.0f,0.0f,0.0f,-1.0f,0.0f,1.0f,0.0f);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
    case 's':
        shoulder_angle = (int)(shoulder_angle + 5.0f) % 360;
        glutPostRedisplay();
        break;
    case 'S':
        shoulder_angle = (int)(shoulder_angle - 5.0f) % 360;
        glutPostRedisplay();
        break;
    case 'e':
        elbow_angle = (int)(elbow_angle + 5.0f) % 360;
        glutPostRedisplay();
        break;
    case 'E':
        elbow_angle = (int)(elbow_angle - 5.0f) % 360;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    // Init glut
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    // Create window
    glutCreateWindow (argv[0]);
    init ();
    // Register callback functions
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    // Enter the main loop
    glutMainLoop();
    return 0;
}

