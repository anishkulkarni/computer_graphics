#include<GL/glut.h>
#include<stdio.h>
#include<unistd.h>

float tv[12][3];
float v[5][3];
float r;
int c=0;

struct Color
{
	GLfloat r,g,b;
};

Color oldColor={1,1,1};
Color newColor={0,0,1};

float rm[3][3]={0.996194698,0.087155743,0,-0.087155743,0.996194698,0,0,0,1};

void floodFill(int x,int y,Color oldc,Color newc)
{
	Color color;
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&color);
	if(color.r==oldc.r&&color.g==oldc.g&&color.b==oldc.b)
	{
		glColor3f(newc.r,newc.g,newc.b);
		floodFill(x+1,y,oldc,newc);
		floodFill(x-1,y,oldc,newc);
		floodFill(x,y+1,oldc,newc);
		floodFill(x,y-1,oldc,newc);
	}
}

void rotate()
{
	float temp[12][3];
	int i=0,j=0,k=0;
	for(i=0;i<12;i++)
	{
		tv[i][0]-=210;
		tv[i][1]-=140;
	}
	
	for(i=0;i<12;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=0;
			for(k=0;k<3;k++)
			{
				temp[i][j]+=tv[i][k]*rm[k][j];
			}
		}
	}
	for(i=0;i<12;i++)
	{
		temp[i][0]+=210;
		temp[i][1]+=140;
	}
	for(i=0;i<12;i++)
	{
		tv[i][0]=temp[i][0];
		tv[i][1]=temp[i][1];
	}
	
}

void generateVertices()
{
	int i=0,j=0,k=0;
	v[0][0]=200;
	v[0][1]=50;
	v[0][2]=1;
	v[1][0]=220;
	v[1][1]=50;
	v[1][2]=1;
	v[2][0]=220;
	v[2][1]=150;
	v[2][2]=1;
	v[3][0]=200;
	v[3][1]=150;
	v[3][2]=1;
	v[4][0]=210;
	v[4][1]=140;
	v[4][2]=1;
	r=10;
	tv[0][0]=210;
	tv[0][1]=140;
	tv[0][2]=1;
	tv[1][0]=195;
	tv[1][1]=90;
	tv[1][2]=1;
	tv[2][0]=225;
	tv[2][1]=90;
	tv[2][2]=1;
	tv[3][0]=210;
	tv[3][1]=110;
	tv[3][2]=1;
	
	float m[3][3]={-0.5,0.866025404,0,-0.866025404,-0.5,0,0,0,1};
	
	for(i=0;i<4;i++)
	{
		tv[i][0]-=210;
		tv[i][1]-=140;
	}
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			tv[i+4][j]=0;
			for(k=0;k<3;k++)
			{
				tv[i+4][j]+=tv[i][k]*m[k][j];
			}
		}
	}
	for(i=0;i<4;i++)
	{
		tv[i][0]+=210;
		tv[i][1]+=140;
		tv[i+4][0]+=210;
		tv[i+4][1]+=140;
	}
	
	for(i=0;i<4;i++)
	{
		tv[i+4][0]-=210;
		tv[i+4][1]-=140;
	}
	
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			tv[i+8][j]=0;
			for(k=0;k<3;k++)
			{
				tv[i+8][j]+=tv[i+4][k]*m[k][j];
			}
		}
	}
	
	for(i=0;i<4;i++)
	{
		tv[i+4][0]+=210;
		tv[i+4][1]+=140;
		tv[i+8][0]+=210;
		tv[i+8][1]+=140;
	}
}

void display()
{
	c++;
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
		glVertex2i(v[0][0],v[0][1]);
		glVertex2i(v[1][0],v[1][1]);
		glVertex2i(v[1][0],v[1][1]);
		glVertex2i(v[2][0],v[2][1]);
		glVertex2i(v[2][0],v[2][1]);
		glVertex2i(v[3][0],v[3][1]);
		glVertex2i(v[3][0],v[3][1]);
		glVertex2i(v[0][0],v[0][1]);
	glEnd();
	if(c%3==0)
		glColor3f(0,0,1);
	if(c%3==1)
		glColor3f(0,1,0);
	if(c%4==2)
		glColor3f(1,0,0);
	glBegin(GL_POLYGON);
		glVertex2i(tv[0][0],tv[0][1]);
		glVertex2f(tv[1][0],tv[1][1]);
		glVertex2f(tv[1][0],tv[1][1]);
		glVertex2f(tv[2][0],tv[2][1]);
		glVertex2f(tv[2][0],tv[2][1]);
		glVertex2f(tv[0][0],tv[0][1]);
	glEnd();	
	glBegin(GL_POLYGON);	
		glVertex2i(tv[4][0],tv[4][1]);
		glVertex2f(tv[5][0],tv[5][1]);
		glVertex2f(tv[5][0],tv[5][1]);
		glVertex2f(tv[6][0],tv[6][1]);
		glVertex2f(tv[6][0],tv[6][1]);
		glVertex2f(tv[4][0],tv[4][1]);
	glEnd();	
	glBegin(GL_POLYGON);	
		glVertex2i(tv[8][0],tv[8][1]);
		glVertex2f(tv[9][0],tv[9][1]);
		glVertex2f(tv[9][0],tv[9][1]);
		glVertex2f(tv[10][0],tv[10][1]);
		glVertex2f(tv[10][0],tv[10][1]);
		glVertex2f(tv[8][0],tv[8][1]);
	glEnd();
	glFlush();
	usleep(10000);
	rotate();
	display();
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("4");
	gluOrtho2D(0,500,0,500);
	generateVertices();
	glutDisplayFunc(display);
	glutMainLoop();
}
