#include<GL/glut.h>
#include<stdio.h>

int xl1=25,yl1=25,xl2=250,yl2=250,xb1=50,yb1=50,xb2=200,yb2=200,displayLine=1,xc=0,yc=0,r=50,mode=0,k[4]={10,10,5,10};

void plot(int x,int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

int abs(int a)
{
	if(a<0)
		return -a;
	else
		return a;
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

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	drawCircleMidpoint(xc,yc,r);
	drawCircleMidpoint(xc+2*r,yc,r);
	drawCircleMidpoint(xc-2*r,yc,r);
	drawCircleMidpoint(xc+r,yc+(1.732050808*r),r);
	drawCircleMidpoint(xc+r,yc-(1.732050808*r),r);
	drawCircleMidpoint(xc-r,yc+(1.732050808*r),r);
	drawCircleMidpoint(xc-r,yc-(1.732050808*r),r);
	drawCircleMidpoint(xc,yc,2*r);
	drawCircleMidpoint(xc,yc,3*r);
	drawCircleMidpoint(xc,yc,r);
	drawCircleMidpoint(xc+r,yc,r);
	drawCircleMidpoint(xc-r,yc,r);
	drawCircleMidpoint(xc,yc+r,r);
	drawCircleMidpoint(xc,yc-r,r);
	drawCircleMidpoint(xc+r/1.414213562,yc+r/1.414213562,r);
	drawCircleMidpoint(xc+r/1.414213562,yc-r/1.414213562,r);
	drawCircleMidpoint(xc-r/1.414213562,yc+r/1.414213562,r);
	drawCircleMidpoint(xc-r/1.414213562,yc-r/1.414213562,r);
	drawCircleMidpoint(xc,yc,2*r);
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DDA");
	gluOrtho2D(-500,500,-500,500);
	display();
	glutMainLoop();
}
