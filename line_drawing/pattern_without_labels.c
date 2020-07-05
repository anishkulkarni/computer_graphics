#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>

#define WINDOW_LENGTH 1600
#define WINDOW_BREADTH 900
#define WINDOW_INIT_X 0
#define WINDOW_INIT_Y 0

float x1 = 0, y1 = 0, x2 = 0, y2 = 0;

int absolute(int x)
{
	if (x >= 0)
		return x;
	else
		return -x;
}

void draw_line(float x1, float y1, float x2, float y2)
{
	int dx = x2 - x1, dy = y2 - y1, steps = 0, i = 0;
	printf("\nDrawing line from (%f,%f) to (%f,%f)",x1,y1,x2,y2);
	printf("\ndx = %d , dy = %d",dx,dy);
	float x = x1, y = y1, x_inc, y_inc;
	if (absolute(dx)>absolute(dy))
		steps = absolute(dx);
	else
		steps = absolute(dy);
	x_inc = dx / (float)steps;
	printf("\nx increment is: %f",x_inc);
	y_inc = dy / (float)steps;
	printf("\ny increment is: %f",y_inc);
	glBegin(GL_POINTS);
	for (i = 1; i <= steps; i++)
	{
		x += x_inc;
		y += y_inc;
		glVertex2i(x, y);
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
	//glutMainLoop();
}

int main(int argc, char** argv)
{
	printf("Enter the co-ordinates of the first point: ");
	scanf("%f%f", &x1, &y1);
	printf("Enter the co-ordinates of the second point: ");
	scanf("%f%f", &x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(WINDOW_LENGTH, WINDOW_BREADTH);
	glutInitWindowPosition(WINDOW_INIT_X,WINDOW_INIT_Y);
	glutCreateWindow("Assignment_1");
	glutDisplayFunc(display_figure);
	glutMainLoop();
	return 0;
}
