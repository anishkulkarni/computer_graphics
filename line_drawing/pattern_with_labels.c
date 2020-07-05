#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>
#include<string.h>

#define WINDOW_LENGTH 1600
#define WINDOW_BREADTH 900
#define WINDOW_INIT_X 0
#define WINDOW_INIT_Y 0

float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
char buffer[50]={'\0'};

 
void renderBitmapString(float x,float y,char *text)
{  
  char *c;
  glRasterPos2f(x,y);
  for (c=text; *c != '\0'; c++)
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *c);
}

void print_point(float x,float y)
{
	int x_dec=x,y_dec=y;
	float x_frac=x-x_dec,y_frac=y-y_dec;
	glRasterPos2f(x,y);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'(');
	do
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,((int)x_dec%10)+48);
		x_dec/=10;
	}while(x_dec>0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,',');
	do
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,((int)y_dec%10)+48);
		y_dec/=10;
	}while(x_dec>0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,')');
}

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
	glRasterPos2f(-20,-20);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'O');
	glRasterPos2f((WINDOW_LENGTH/2)-20,-20);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'X');
	glRasterPos2f(-(WINDOW_LENGTH/2),-20);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'X');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'\'');
	glRasterPos2f(-20,(WINDOW_BREADTH/2)-20);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'Y');
	glRasterPos2f(-30,-(WINDOW_BREADTH/2));
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'Y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'\'');
	draw_line(-(WINDOW_LENGTH/2),0,(WINDOW_LENGTH/2),0);
	draw_line(0,-(WINDOW_BREADTH/2),0,(WINDOW_BREADTH/2));
}


void display_figure()
{
	gluOrtho2D(-(WINDOW_LENGTH/2), (WINDOW_LENGTH/2), -(WINDOW_BREADTH/2), (WINDOW_BREADTH/2));
	draw_axis();
	sprintf(buffer, "(%0.2f,%0.2f)",x1,y1); 
	renderBitmapString(x1-20,y1-20,buffer);
	sprintf(buffer, "(%0.2f,%0.2f)",x2,y2); 
	renderBitmapString(x2-20,y2-20,buffer);
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
