#include<stdio.h>
#include<GL/glut.h>

void display();
void specialKeys();

double rotate_x=0;
double rotate_y=0;

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutCreateWindow("Cube");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glRotatef(rotate_x,1.0,0.0,0.0);
	glRotatef(rotate_y,0.0,1.0,0.0);
	
	//front-blue
	glBegin(GL_POLYGON);
	glColor3f(0.0,0.0,1.0);
  	glVertex3f(  0.5, -0.5, -0.5 );
 	glVertex3f(  0.5,  0.5, -0.5 );
 	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5, -0.5, -0.5 ); 
	glEnd();
	
	//back-red+green=
 	glBegin(GL_POLYGON);
 	glColor3f(   1.0,  1.0, 0.0 );
 	glVertex3f(  0.5, -0.5, 0.5 );
 	glVertex3f(  0.5,  0.5, 0.5 );
 	glVertex3f( -0.5,  0.5, 0.5 );
 	glVertex3f( -0.5, -0.5, 0.5 );
 	glEnd();

	//right-green
	glBegin(GL_POLYGON);
	glColor3f(  0.0,  1.0,  0.0 );
	glVertex3f( 0.5, -0.5, -0.5 );
	glVertex3f( 0.5,  0.5, -0.5 );
	glVertex3f( 0.5,  0.5,  0.5 );
	glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();
	 
	//left-green+blue=
	glBegin(GL_POLYGON);
	glColor3f(   0.0,  1.0,  1.0 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
	 
	//top-red
	glBegin(GL_POLYGON);
	glColor3f(   1.0,  0.0,  0.0 );
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();
	 
	//bottom-violet
	glBegin(GL_POLYGON);
	glColor3f(   1.0,  0.0,  1.0 );
	glVertex3f(  0.5, -0.5, -0.5 );
	glVertex3f(  0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
	 
	glFlush();
	glutSwapBuffers();
}

void specialKeys(int key,int x,int y)
{
	if(key==GLUT_KEY_RIGHT)
		rotate_y+=5;
	if(key==GLUT_KEY_LEFT)
		rotate_y-=5;
	if(key==GLUT_KEY_UP)
		rotate_x+=5;
	if(key==GLUT_KEY_DOWN)
		rotate_x-=5;
	glutPostRedisplay();
}
