#include<GL/glut.h>

float v[5][3]={100,100,1,200,100,1,200,200,1,100,200,1,150,150,1};

float rt[3][3]={0.707106781,0.707106781,0,-0.707106781,0.707106781,0,0,0,1};

struct Color
{
	GLfloat r,g,b;
};

Color oldColor={1,1,1};

Color newColor={0,0,1};

void floodFill(GLint x,GLint y,Color oldc,Color newc)
{
	Color c;
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&c);
	if(c.r==oldc.r&&c.g==oldc.g&&c.b==oldc.b)
	{
		glColor3f(newc.r,newc.g,newc.b);
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		glFlush();
		floodFill(x+1,y,oldc,newc);
		floodFill(x-1,y,oldc,newc);
		floodFill(x,y+1,oldc,newc);
		floodFill(x,y-1,oldc,newc);
	}
}

void rotate()
{
	int i=0,j=0,k=0;
	float temp[5][3];
	for(i=0;i<5;i++)
	{
		for(j=0;j<3;j++)
		{
			v[i][j]-=100;
		}
	}
	for(i=0;i<5;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=0;
			for(k=0;k<3;k++)
			{
				temp[i][j]+=v[i][k]*rt[k][j];
			}
		}
	}
	for(i=0;i<5;i++)
	{
		for(j=0;j<3;j++)
		{
			v[i][j]=temp[i][j];
			v[i][j]+=100;
		}
	}
}

void display()
{	
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		glVertex2f(v[0][0],v[0][1]);
		glVertex2f(v[1][0],v[1][1]);
		glVertex2f(v[1][0],v[1][1]);
		glVertex2f(v[2][0],v[2][1]);
		glVertex2f(v[2][0],v[2][1]);
		glVertex2f(v[3][0],v[3][1]);
		glVertex2f(v[3][0],v[3][1]);
		glVertex2f(v[0][0],v[0][1]);
	glEnd();
	glFlush();
	floodFill(v[4][0],v[4][1],oldColor,newColor);
	return ;
}

void mouse(int,int,int,int)
{
	rotate();
	display();
	return;
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("mouse");
	gluOrtho2D(0,500,0,500);
	display();
	glutMouseFunc(mouse);
	glutMainLoop();
}
