#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>

#define WINDOW_LENGTH 1600
#define WINDOW_BREADTH 900
#define WINDOW_INIT_X 0
#define WINDOW_INIT_Y 0

int xb1=0, yb1=0, l=0;

void plot(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

int absolute(int x)
{
	if (x >= 0)
		return x;
	else
		return -x;
}

void draw_line(int x1, int y1, int x2, int y2)
{
	int dx = absolute(x2 - x1), dy = absolute(y2 - y1),x_inc=x2>=x1?1:-1,y_inc=y2>=y1?1:-1,p=2*dy-dx,i=0,x=x1,y=y1;
	printf("\nDrawing line from (%d,%d) to (%d,%d) using Bresenham's algorithm",x1,y1,x2,y2);
	printf("\ndx = %d , dy = %d",dx,dy);
	if(dx>=dy)
	{
		plot(x, y);
		for (i = 0; i < dx; i++)
		{
			if(p>0)
			{
				y+=y_inc;
				p-=2*dx;
			}
			x+=x_inc;
			p+=2*dy;
			plot(x, y);
		}
	}
	else
	{
		plot(x, y);
		for (i = 0; i < dy; i++)
		{
			if(p>0)
			{
				x+=x_inc;
				p-=2*dy;
			}
			y+=y_inc;
			p+=2*dx;
			plot(x, y);
		}
	}
}

void draw_axis()
{
	draw_line(-(WINDOW_LENGTH/2),0,(WINDOW_LENGTH/2),0);
	draw_line(0,-(WINDOW_BREADTH/2),0,(WINDOW_BREADTH/2));
}

void draw_circle(int x_centre, int y_centre, int radius)
{
	printf("\nDrawing circle with centre (%d,%d) and radius (%d) using midpoint algorithm",x_centre,y_centre,radius);
	int x = 0;
	int y = radius;
	float decision = 5/4 - radius;
	plot(x_centre+x, y_centre+y);

	while (y > x)
	{
		if (decision < 0)
		{
			x++; 
			decision += 2*x+1;
		}
		else
		{
			y--;
			x++;
			decision += 2*(x-y)+1;
		}
		plot(x_centre+x, y_centre+y);
		plot(x_centre+x, y_centre-y);
		plot(x_centre-x, y_centre+y);
		plot(x_centre-x, y_centre-y);
		plot(x_centre+y, y_centre+x);
		plot(x_centre-y, y_centre+x);
		plot(x_centre+y, y_centre-x);
		plot(x_centre-y, y_centre-x);
	}

}

void draw_figure(void)
{
	draw_axis();
	//draw triangle
	//Given point (xb1,yb1)
	//Second point (xb1 + l,yb1)
	//Third point (xb1 + l/2 , yb1 + sqrt(3)/2*l) = (xb1 + l/2, yb1 + 0.866025404*l)
	draw_line(xb1,yb1,xb1+l,yb1);
	draw_line(xb1,yb1,xb1+(l/2),yb1+(0.866025404*l));
	draw_line(xb1+l,yb1,xb1+(l/2),yb1+(0.866025404*l));
	//Incentre and Circumcentre coincide
	//Centre co-ordinates are : (xb1 + l/2 , yb1 + l*1/3(sqrt(3)/2)) = (xb1 + l/2 , yb1 + l*sqrt(3)/6) = (xb1 + l/2 , yb1 + 0.288675134*l)
	//draw incircle
	//radius = sqrt(3)/6 * l = 0.288675134*l
	draw_circle(xb1+(l/2),yb1+(0.288675134*l),0.288675134*l);
	//draw circumcircle
	//radius = sqrt(3)/3 * l= 0.577350269*l
	draw_circle(xb1+(l/2),yb1+(0.288675134*l),0.577350269*l);
	glFlush ();
}

int main(int argc, char** argv)
{
	printf("x co-ordinate of base point: ");
	scanf("%d",&xb1);
	printf("y co-ordinate of base point: ");
	scanf("%d",&yb1);
	printf("length of triangle: ");
	scanf("%d",&l);
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_LENGTH, WINDOW_BREADTH);
	glutInitWindowPosition(WINDOW_INIT_X,WINDOW_INIT_Y);
	glutCreateWindow ("Assignment 2");
	glutDisplayFunc(draw_figure);
	gluOrtho2D(-(WINDOW_LENGTH/2), (WINDOW_LENGTH/2), -(WINDOW_BREADTH/2), (WINDOW_BREADTH/2));
	glutMainLoop();
}
