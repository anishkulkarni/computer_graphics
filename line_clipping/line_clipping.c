#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>

float xd1,yd1,xd2,yd2,xmax,ymax,xmin,ymin;

int absolute(int x)
{
	if (x >= 0)
		return x;
	else
		return -x;
}

void draw_line(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1, steps = 0, i = 0;
	float x = x1, y = y1, x_inc, y_inc;
	if (absolute(dx)>absolute(dy))
		steps = dx;
	else
		steps = dy;
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	glBegin(GL_POINTS);
	for (i = 1; i <= steps; i++)
	{
		x += x_inc;
		y += y_inc;
		glVertex2i(x, y);
	}
	glEnd();
}

void display_figure()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,1.0f,1.0f);
	draw_line(xmin,ymin,xmax,ymin);
	draw_line(xmax,ymin,xmax,ymax);
	draw_line(xmin,ymax,xmax,ymax);
	draw_line(xmin,ymin,xmin,ymax);
	draw_line(xd1, yd1, xd2, yd2);
	glFlush();
}

int code(float x,float y)
{
	int c=0;
	if(y>ymax)c=8;
	if(y<ymin)c=4;
	if(x>xmax)c=c|2;
	if(x<xmin)c=c|1;
	return c;
}

void cohenLine(float x1,float y1,float x2,float y2)
{
	int c1=code(x1,y1);
	int c2=code(x2,y2);
	float m=(y2-y1)/(x2-x1);
	while((c1|c2)>0)
	{
		if((c1&c2)>0)
		{
			exit(0);
		}
		float xi=x1;
		float yi=y1;
		int c=c1;
		if(c==0)
		{
			c=c2;
			xi=x2;
			yi=y2;
		}
		float x,y;
		if((c&8)>0)
		{
			y=ymax;
			x=xi+(1.0/m)*(ymax-yi);
		}
		else if((c&4)>0)
		{
			y=ymin;
			x=xi+(1.0/m)*(ymin-yi);
		}
		else if((c&2)>0)
		{
			x=xmax;
			y=y1+m*(xmax-xi);
		}
		else if((c&1)>0)
		{
			x=xmin;
			y=yi+m*(xmin-xi);
		}
		if(c==c1)
		{
			xd1=x;
			yd1=y;
			c1=code(xd1,xd2);
		}
		if(c==c2)
		{
			xd2=x;
			yd2=y;
			c2=code(xd1,xd2);
		}
	}
	display_figure();
}

void myKey(unsigned char key,int x,int y)
{
	if(key=='c')
	{
		cohenLine(xd1,yd1,xd2,yd2);
		glFlush();
	}
}

void create()
{
	display_figure();
}

int main(int argc, char** argv)
{
	printf("Enter the co-ordinates of the left bottom: ");
	scanf("%f%f", &xmin, &ymin);
	printf("Enter the co-ordinates of the right top: ");
	scanf("%f%f", &xmax, &ymax);
	printf("Enter the co-ordinates of the first point: ");
	scanf("%f%f", &xd1, &yd1);
	printf("Enter the co-ordinates of the second point: ");
	scanf("%f%f", &xd2, &yd2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment_1");
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(create);
	glutKeyboardFunc(myKey);
	glutMainLoop();
	return 0;
}
