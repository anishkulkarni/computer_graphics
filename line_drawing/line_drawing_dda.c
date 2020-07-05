#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>

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
	int x1 = 0, y1 = 0, x2 = 200, y2 = 200;
	printf("Enter the co-ordinates of the first point: ");
	scanf("%d%d", &x1, &y1);
	printf("Enter the co-ordinates of the second point: ");
	scanf("%d%d", &x2, &y2);
	gluOrtho2D(-250, 250, -250, 250);
	draw_line(x1, y1, x1, y2);
	draw_line(x1, y1, x2, y1);
	draw_line(x1, y2, x2, y2);
	draw_line(x2, y1, x2, y2);
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment_1");
	glutDisplayFunc(display_figure);
	glutMainLoop();
	return 0;
}