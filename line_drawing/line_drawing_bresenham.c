#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>

#define WINDOW_LENGTH 1600
#define WINDOW_BREADTH 900
#define WINDOW_INIT_X 0
#define WINDOW_INIT_Y 0

int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

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
	printf("\nDrawing line from (%d,%d) to (%d,%d)",x1,y1,x2,y2);
	printf("\ndx = %d , dy = %d",dx,dy);
	glBegin(GL_POINTS);
	if(dx>=dy)
	{
		glVertex2i(x, y);
		for (i = 0; i < dx; i++)
		{
			if(p>0)
			{
				y+=y_inc;
				p-=2*dx;
			}
			x+=x_inc;
			p+=2*dy;
			glVertex2i(x, y);
		}
	}
	else
	{
		glVertex2i(x, y);
		for (i = 0; i < dy; i++)
		{
			if(p>0)
			{
				x+=x_inc;
				p-=2*dy;
			}
			y+=y_inc;
			p+=2*dx;
			glVertex2i(x, y);
		}
	}
	glEnd();
}

void draw_axis()
{
	draw_line(-(WINDOW_LENGTH/2),0,(WINDOW_LENGTH/2),0);
	draw_line(0,-(WINDOW_BREADTH/2),0,(WINDOW_BREADTH/2));
}


void display_figure()
{
	gluOrtho2D(-(WINDOW_LENGTH/2), (WINDOW_LENGTH/2), -(WINDOW_BREADTH/2), (WINDOW_BREADTH/2));
	draw_axis();
	//draw outer square
	draw_line(x1, y1, x1, y2);
	draw_line(x1, y1, x2, y1);
	draw_line(x1, y2, x2, y2);
	draw_line(x2, y1, x2, y2);
	//draw inner diamond
	draw_line(x1, (y1+y2)/2, (x1+x2)/2, y2);
	draw_line(x2,(y1+y2)/2,(x1+x2)/2,y2);
	draw_line((x1+x2)/2,y1,x2,(y1+y2)/2);
	draw_line( (x1+x2)/2, y1,x1,(y1+y2)/2);
	//draw inner square
	draw_line((3*x1+x2)/4,(3*y1+y2)/4,(3*x1+x2)/4,(3*y2+y1)/4);
	draw_line((3*x1+x2)/4,(3*y2+y1)/4,(3*x2+x1)/4,(3*y2+y1)/4);
	draw_line((3*x2+x1)/4,(3*y1+y2)/4,(3*x2+x1)/4,(3*y2+y1)/4);
	draw_line((3*x1+x2)/4,(3*y1+y2)/4,(3*x2+x1)/4,(3*y1+y2)/4);
	glFlush();
}

int main(int argc, char** argv)
{
	printf("Enter the co-ordinates of the first point: ");
	scanf("%d%d", &x1, &y1);
	printf("Enter the co-ordinates of the second point: ");
	scanf("%d%d", &x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(WINDOW_LENGTH, WINDOW_BREADTH);
	glutInitWindowPosition(WINDOW_INIT_X,WINDOW_INIT_Y);
	glutCreateWindow("Assignment 1 using Bresenham's algorithm");
	glutDisplayFunc(display_figure);
	glutMainLoop();
	return 0;
}
