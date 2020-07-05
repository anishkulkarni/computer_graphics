#include<GL/glut.h>
#include<stdio.h>
#include<unistd.h>

float l[4][3];
float r=100;

void plot(int x,int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}

void drawCircleMidpoint(int xc,int yc,int r)
{
	int d=(5/4)*r-1,x=0,y=r;
	plot(xc+x,yc+y);
	plot(xc+x,yc-y);
	plot(xc-x,yc+y);
	plot(xc-x,yc-y);
	plot(xc+y,yc+x);
	plot(xc+y,yc-x);
	plot(xc-y,yc+x);
	plot(xc-y,yc-x);
	while(y>x)
	{
		if(d>0)
		{
			d-=2*y;
			y--;
		}
		d=d+2*x-1;
		x++;
		plot(xc+x,yc+y);
		plot(xc+x,yc-y);
		plot(xc-x,yc+y);
		plot(xc-x,yc-y);
		plot(xc+y,yc+x);
		plot(xc+y,yc-x);
		plot(xc-y,yc+x);
		plot(xc-y,yc-x);
	}
}

void rr()
{
	int i=0,j=0,k=0;
	float rm[3][3]={0.999847695,-0.017452406,0,0.017452406,0.999847695,0,0,0,1};
	float temp[2][3];
	l[2][0]-=300;
	l[2][1]-=300;
	l[3][0]-=300;
	l[3][1]-=300;
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=0;
			for(k=0;k<3;k++)
			{
				temp[i][j]+=l[i+2][k]*rm[k][j];
			}
		}
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			l[i+2][j]=temp[i][j];
		}
	}
	l[2][0]+=300;
	l[2][1]+=300;
	l[3][0]+=300;
	l[3][1]+=300;
}

void rl()
{
	int i=0,j=0,k=0;
	float rm[3][3]={0.999847695,0.017452406,0,-0.017452406,0.999847695,0,0,0,1};
	float temp[2][3];
	l[2][0]-=300;
	l[2][1]-=300;
	l[3][0]-=300;
	l[3][1]-=300;
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=0;
			for(k=0;k<3;k++)
			{
				temp[i][j]+=l[i+2][k]*rm[k][j];
			}
		}
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			l[i+2][j]=temp[i][j];
		}
	}
	l[2][0]+=300;
	l[2][1]+=300;
	l[3][0]+=300;
	l[3][1]+=300;
}

void rotateHand()
{
	int i=0,j=0,k=0;
	float rm[3][3]={0.999847695,-0.017452406,0,0.017452406,0.999847695,0,0,0,1};
	float temp[2][3];
	l[0][0]-=300;
	l[0][1]-=300;
	l[1][0]-=300;
	l[1][1]-=300;
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=0;
			for(k=0;k<3;k++)
			{
				temp[i][j]+=l[i][k]*rm[k][j];
			}
		}
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			l[i][j]=temp[i][j];
		}
	}
	l[0][0]+=300;
	l[0][1]+=300;
	l[1][0]+=300;
	l[1][1]+=300;
}

void generateVertices()
{
	l[0][0]=300;
	l[0][1]=300;
	l[0][2]=1;
	l[1][0]=300;
	l[1][1]=400;
	l[1][2]=1;
	l[2][0]=300;
	l[2][1]=200;
	l[2][2]=1;
	l[3][0]=300;
	l[3][1]=100;
	l[3][2]=1;
}

void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,1);
	drawCircleMidpoint(l[0][0],l[0][1],r);
	drawCircleMidpoint(l[3][0],l[3][1],20);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex2f(l[0][0],l[0][1]);
		glVertex2f(l[1][0],l[1][1]);
		glVertex2f(l[2][0],l[2][1]);
		glVertex2f(l[3][0],l[3][1]);
	glEnd();
	glFlush();
}

void handle()
{
	generateVertices();
	int i=0;
	display();
	while(1)
	{
		for(i=0;i<25;i++)
		{
			rr();
			usleep(10000);
			display();
		}
		for(i=0;i<50;i++)
		{
			rl();
			usleep(10000);
			display();
		}
		for(i=0;i<25;i++)
		{
			rr();
			usleep(10000);
			display();
		}
		rotateHand();
		display();
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("5");
	gluOrtho2D(0,800,0,800);
	glutDisplayFunc(handle);
	glutMainLoop();
}
