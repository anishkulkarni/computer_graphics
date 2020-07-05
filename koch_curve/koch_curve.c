#include <GL/glut.h>
#include <math.h>

GLfloat oldx=0,oldy=0;

void drawkoch(GLfloat direction,GLfloat length,GLint level)
{
	GLdouble dirRad = 0.0174533 * direction;
	GLfloat newX = oldx + length * cos(dirRad);
	GLfloat newY = oldy + length * sin(dirRad);
	if (level==0)
	{
		glBegin(GL_LINES);
			glVertex2f(oldx, oldy);
			glVertex2f(newX, newY);
	 
	 	glEnd();
		oldx = newX;
		oldy = newY;
	}
	else
	{
		level--;
		drawkoch(direction, length, level);
		direction += 60.0;
		drawkoch(direction, length, level);
		direction -= 120.0;
		drawkoch(direction, length, level);
		direction += 60.0;
		drawkoch(direction, length, level);
	}
}

void mydisplay()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f(1.0, 1.0, 1.0);
	drawkoch(0.0,0.001,5);
	drawkoch(-120.0, 0.001,5);
	drawkoch(120.0,0.001,5);
	glFlush(); 
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);      
	glutInitWindowSize(1000,1000);
	gluOrtho2D(-500,500,-500,500);
	glutInitWindowPosition(0,0); 
	glutCreateWindow("Koch Snowflake");     
	glutDisplayFunc(mydisplay);  
	glutMainLoop();
}
