#include<stdio.h>
#include <GL/glut.h>
#include <unistd.h>

float vertices[18][3];

float transform[3][3]={1,0,0,0,1,0,1,0,1};

float r_transform[3][3]={0.999390827,0.034899497,0,-0.034899497,0.999390827,0,0,0,1};

void setVertices()
{
	int i=0;
	//car vertices
	vertices[0][0]=100;
	vertices[0][1]=100;
	vertices[0][2]=1;
	vertices[1][0]=200;
	vertices[1][1]=100;
	vertices[1][2]=1;
	vertices[2][0]=200;
	vertices[2][1]=120;
	vertices[2][2]=1;
	vertices[3][0]=175;
	vertices[3][1]=120;
	vertices[3][2]=1;
	vertices[4][0]=175;
	vertices[4][1]=130;
	vertices[4][2]=1;
	vertices[5][0]=125;
	vertices[5][1]=130;
	vertices[5][2]=1;
	vertices[6][0]=125;
	vertices[6][1]=120;
	vertices[6][2]=1;
	vertices[7][0]=100;
	vertices[7][1]=120;
	vertices[7][2]=1;
	//left wheel centre
	vertices[8][0]=125;
	vertices[8][1]=90;
	vertices[8][2]=1;
	//right wheel centre
	vertices[9][0]=175;
	vertices[9][1]=90;
	vertices[9][2]=1;
	//left wheel vertical spoke top
	vertices[10][0]=125;
	vertices[10][1]=100;
	vertices[10][2]=1;
	//left wheel vertical spoke bottom
	vertices[11][0]=125;
	vertices[11][1]=80;
	vertices[11][2]=1;
	//left wheel horizontal spoke left
	vertices[12][0]=115;
	vertices[12][1]=90;
	vertices[12][2]=1;
	//left wheel horizontal spoke right
	vertices[13][0]=135;
	vertices[13][1]=90;
	vertices[13][2]=1;
	//right wheel vertical spoke top
	vertices[14][0]=175;
	vertices[14][1]=100;
	vertices[14][2]=1;
	//right wheel vertical spoke bottom
	vertices[15][0]=175;
	vertices[15][1]=80;
	vertices[15][2]=1;
	//right wheel horizontal spoke left
	vertices[16][0]=165;
	vertices[16][1]=90;
	vertices[16][2]=1;
	//right wheel horizontal spoke right
	vertices[17][0]=185;
	vertices[17][1]=90;
	vertices[17][2]=1;
}

void setPixel(GLint x,GLint y)
{
  	glBegin(GL_POINTS);
  	glVertex2i(x,y);
  	glEnd();
}

void Circle(int xCenter,int yCenter, int r)
{
  	int x=0,y=r;
  	int p = 3/2 - r;    
  	while(x<=y)
	{
    		setPixel(xCenter+x,yCenter+y);
    		setPixel(xCenter+y,yCenter+x);  
    		setPixel(xCenter-x,yCenter+y);
    		setPixel(xCenter+y,yCenter-x);
    		setPixel(xCenter-x,yCenter-y);
    		setPixel(xCenter-y,yCenter-x);
    		setPixel(xCenter+x,yCenter-y);
    		setPixel(xCenter-y,yCenter+x);
		if (p<0)
  			p += (2*x)+3;
		else 
		{
 			p += (2*(x-y))+5;
 			y -= 1;
    		}
    		x++;
  	}
}

void translate()
{
	int i=0,j=0,k=0;
	float temp[18][3]={0};
	for(i=0;i<18;i++)
		for(j=0;j<3;j++)
			for(k=0;k<3;k++)
				temp[i][j]+=vertices[i][k]*transform[k][j];
	for(i=0;i<18;i++)
		for(j=0;j<3;j++)
			vertices[i][j]=temp[i][j];
}

void rotate()
{
	int i=0,j=0,k=0;
	for(i=10;i<14;i++)
	{
		vertices[i][0]-=vertices[8][0];
		vertices[i][1]-=vertices[8][1];
	}
	for(i=14;i<18;i++)
	{
		vertices[i][0]-=vertices[9][0];
		vertices[i][1]-=vertices[9][1];
	}
	float temp[8][3]={0};
	for(i=10;i<18;i++)
		for(j=0;j<3;j++)
			for(k=0;k<3;k++)
				temp[i-10][j]+=vertices[i][k]*r_transform[k][j];
	for(i=10;i<18;i++)
		for(j=0;j<3;j++)
			vertices[i][j]=temp[i-10][j];
	for(i=10;i<14;i++)
	{
		vertices[i][0]+=vertices[8][0];
		vertices[i][1]+=vertices[8][1];
	}
	for(i=14;i<18;i++)
	{
		vertices[i][0]+=vertices[9][0];
		vertices[i][1]+=vertices[9][1];
	}
}

void init() 
{	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,640,0,480);
}

void car()
{
	if(vertices[0][0]+50>=500)
	{
		transform[2][0]=-1;
		r_transform[0][1]*=-1;
		r_transform[1][0]*=-1;
	}
	if(vertices[0][0]<=100)
	{
		transform[2][0]=1;
		r_transform[0][1]*=-1;
		r_transform[1][0]*=-1;
	}
  	glClearColor(1.0f,1.0f,1.0,0.0f);
  	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
		glVertex2i(vertices[0][0],vertices[0][1]);
		glVertex2i(vertices[1][0],vertices[1][1]);
		glVertex2i(vertices[2][0],vertices[2][1]);
		glVertex2i(vertices[3][0],vertices[3][1]);
		glVertex2i(vertices[4][0],vertices[4][1]);
		glVertex2i(vertices[5][0],vertices[5][1]);
		glVertex2i(vertices[6][0],vertices[6][1]);
		glVertex2i(vertices[7][0],vertices[7][1]);
		glVertex2i(vertices[0][0],vertices[0][1]);
	glEnd();
  	glColor3f(0.0,0.0,0.0);
	Circle(vertices[8][0],vertices[8][1],10);
	Circle(vertices[9][0],vertices[9][1],10);
	glBegin(GL_LINES);
		glVertex2i(vertices[10][0],vertices[10][1]);
		glVertex2i(vertices[11][0],vertices[11][1]);
		glVertex2i(vertices[12][0],vertices[12][1]);
		glVertex2i(vertices[13][0],vertices[13][1]);
		glVertex2i(vertices[14][0],vertices[14][1]);
		glVertex2i(vertices[15][0],vertices[15][1]);
		glVertex2i(vertices[16][0],vertices[16][1]);
		glVertex2i(vertices[17][0],vertices[17][1]);
	glEnd();
	glFlush();
	usleep(10000);
	translate();
	rotate();
	car();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(640,480);
 	glutInitWindowPosition(0,0);
	setVertices();
  	glutCreateWindow("Car");
  	init();
  	glutDisplayFunc(car);
  	glutMainLoop();
}
