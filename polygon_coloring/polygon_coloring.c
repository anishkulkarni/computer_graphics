#include<stdio.h>
#include <GL/glut.h>

bool firstPointFlag=true;

bool fillFlag=false;

struct Point
{
    Point( float x, float y ) : x(x), y(y) {}
    float x, y;
};

Point firstPoint(0,0);
Point previousPoint(0,0);

struct Color
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,640,0,480);
}

Color newColor = {0.0f, 0.0f, 0.0f};

Color oldColor = {1.0f, 1.0f, 1.0f};

Color fillColor = {0.0f, 0.0f, 1.0f};

Color getPixelColor(GLint x, GLint y)
{
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color)
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor)
{
	Color color;
	color = getPixelColor(x, y);

	if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
	{
		setPixelColor(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x, y+1, oldColor, newColor);
		floodFill(x-1, y, oldColor, newColor);
		floodFill(x, y-1, oldColor, newColor);
	}
	return;
}

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

void draw_palette()
{
	draw_line(100,100,450,100);
	draw_line(100,200,450,200);
	draw_line(100,200,100,100);
	draw_line(150,200,150,100);
	draw_line(200,200,200,100);
	draw_line(250,200,250,100);
	draw_line(300,200,300,100);
	draw_line(350,200,350,100);
	draw_line(400,200,400,100);
	draw_line(450,200,450,100);
   	newColor.r=0;
   	newColor.g=0;
   	newColor.b=0;
   	floodFill(125,125,oldColor,newColor);
   	newColor.r=0;
   	newColor.g=0;
   	newColor.b=1;
   	floodFill(175,125,oldColor,newColor);
   	newColor.r=0;
   	newColor.g=1;
   	newColor.b=0;
   	floodFill(225,125,oldColor,newColor);
   	newColor.r=0;
   	newColor.g=1;
   	newColor.b=1;
   	floodFill(275,125,oldColor,newColor);
   	newColor.r=1;
   	newColor.g=0;
   	newColor.b=0;
   	floodFill(325,125,oldColor,newColor);
   	newColor.r=1;
   	newColor.g=0;
   	newColor.b=1;
   	floodFill(375,125,oldColor,newColor);
   	newColor.r=1;
   	newColor.g=1;
   	newColor.b=0;
   	floodFill(425,125,oldColor,newColor);
	glColor3f(0.0f, 0.0f, 0.0f);
}

void mouse( int button, int state, int _x, int _y )
{
	printf("\n%f %f",_x,_y);
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if(_x>100 && _x<450 && (480-_y)>100 && (480-_y)<200)
		{
			printf("getting color");
			fillColor = getPixelColor(_x, 480-_y);
		}
		else
		{
			if(firstPointFlag)
			{
				firstPoint.x=_x;
				firstPoint.y=480-_y;
				previousPoint.x=_x;
				previousPoint.y=480-_y;
				firstPointFlag=false;
			}
			else
			{
				draw_line(_x,480-_y,previousPoint.x,previousPoint.y);
				previousPoint.x=_x;
				previousPoint.y=480-_y;
			}
		}
    }
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if(fillFlag==false)
		{
			draw_line(previousPoint.x,previousPoint.y,firstPoint.x,firstPoint.y);
			fillFlag=true;
		}
		else
		{
   			floodFill(_x,480-_y,oldColor,fillColor);
			fillFlag=false;
		}
	}
	glutPostRedisplay();
}

void draw_figure(void)
{
	glFlush();
	draw_palette();
}

int main( int argc, char **argv )
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow ("Polygon");
	init();
	glutDisplayFunc(draw_figure);
	glutMouseFunc(mouse);
	glutMainLoop();
   	return 0;
}
