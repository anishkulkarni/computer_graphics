#include <GL/glut.h>
#include<stdio.h>

int xb=0, yb=0, l=0;
int points[10][4];
int in_points[16][2];
float tf[4][4]={0.707106781,0.707106781,0,0,-0.707106781,0.707106781,0,0,0,0,0.707106781,0.707106781,0,0,-0.707106781,0.707106781};
float in_tf[2][2]={0.707106781,0.707106781,-0.707106781,0.707106781};
int res[10][4]={0};
int in_res[16][2]={0};

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
	

void transform()
{
	int i,j,k;
	for(i=0;i<10;i++)
	{
		for(j=0;j<4;j++)
		{
			res[i][j]=0;
			for(k=0;k<4;k++)
			{
				res[i][j]+=points[i][k]*tf[k][j];
			}
		}
	}
}

void transform_in()
{
	int i,j,k;
	for(i=0;i<16;i++)
	{
		for(j=0;j<2;j++)
		{
			in_res[i][j]=0;
			for(k=0;k<2;k++)
			{
				in_res[i][j]+=in_points[i][k]*in_tf[k][j];
			}
		}
	}
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

void draw_axis()
{
	draw_line(-320,0,320,0);
	draw_line(0,-240,0,240);
}

void set_points()
{
	int i;
	int x=xb,y=yb;
	//horizontal lines
	for(i=0;i<5;i++)
	{
		points[i][0]=x+l;
		points[i][1]=y;
		points[i][2]=x;
		points[i][3]=y;
		y+=l/4;
	}
	x=xb;
	y=yb;
	//vertical lines
	for(i=5;i<10;i++)
	{
		points[i][0]=x;
		points[i][1]=y;
		points[i][2]=x;
		points[i][3]=y+l;
		x+=l/4;
	}
}

void draw_board()
{
	int i=0;
	for(i=0;i<10;i++)
	{
		draw_line(points[i][0],points[i][1],points[i][2],points[i][3]);
	}
}

void draw_rotated_board()
{
	int i;
	for(i=0;i<10;i++)
	{
		draw_line(res[i][0],res[i][1],res[i][2],res[i][3]);
	}
}

void shift()
{
	int i;
	for(i=0;i<10;i++)
	{
		points[i][0]-=xb;
		points[i][1]-=yb;
		points[i][2]-=xb;
		points[i][3]-=yb;
	}	
}

void in_shift()
{
	int i;
	for(i=0;i<16;i++)
	{
		in_points[i][0]-=xb;
		in_points[i][1]-=yb;
	}
}

void shift_back()
{
	int i;
	for(i=0;i<10;i++)
	{
		points[i][0]+=xb;
		points[i][1]+=yb;
		points[i][2]+=xb;
		points[i][3]+=yb;
		res[i][0]+=xb;
		res[i][1]+=yb;
		res[i][2]+=xb;
		res[i][3]+=yb;
	}
}

void in_shift_back()
{
	int i;
	for(i=0;i<16;i++)
	{
		in_points[i][0]+=xb;
		points[i][1]+=yb;
		in_res[i][0]+=xb;
		in_res[i][1]+=yb;
	}
}

void generate_in_points()
{
	
	int i,j,x=xb,y=yb,k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			in_points[k][0]=x+2;
			in_points[k][1]=y+2;
			printf("\nAdded %d %d",in_points[i][0],in_points[i][1]);
			y+=(l/4);
			k++;
		}
		y=yb;
		x+=l/4;
	}
}

void draw_figure(void)
{
	int i=0;
	//draw axis
	draw_axis();
	//generate point matrix
	set_points();
	//shift origin to base point
	shift();
	//rotate chessboard
	transform();
	// shift back to previous origin
	shift_back();
	//draw chess board
	draw_board();
	floodFill(xb+2,yb+2,oldColor,newColor);
	floodFill(xb+(l/2)+2,yb+2,oldColor,newColor);
	floodFill(xb+2+(l/4),yb+(l/4)+2,oldColor,newColor);
	floodFill(xb+2+(3*l/4),yb+(l/4)+2,oldColor,newColor);
	floodFill(xb+2,yb+(l/2)+2,oldColor,newColor);
	floodFill(xb+2+(l/2),yb+(l/2)+2,oldColor,newColor);
	floodFill(xb+2+(l/4),yb+2+(3*l/4),oldColor,newColor);
	floodFill(xb+2+(3*l/4),yb+2+(3*l/4),oldColor,newColor);
	generate_in_points();
	in_shift();
	transform_in();
	in_shift_back();
	glFlush();
}

void onMouseClick(int,int,int,int)
{
	int i=0;
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	draw_rotated_board();
	while(i<16)
	{
		floodFill(in_res[i][0],in_res[i][1],oldColor,newColor);
		i+=2;
		floodFill(in_res[i][0],in_res[i][1],oldColor,newColor);
		i+=3;
		floodFill(in_res[i][0],in_res[i][1],oldColor,newColor);
		i+=2;
		floodFill(in_res[i][0],in_res[i][1],oldColor,newColor);
		i+=1;
	}
	glFlush();
}

int main(int argc, char** argv)
{
	printf("x co-ordinate of base point: ");
	scanf("%d",&xb);
	printf("y co-ordinate of base point: ");
	scanf("%d",&yb);
	printf("length of chessboard: ");
	scanf("%d",&l);
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow ("Assignment 3");
	init();
	glutMouseFunc(onMouseClick);
	glutDisplayFunc(draw_figure);
	glutMainLoop();
}
