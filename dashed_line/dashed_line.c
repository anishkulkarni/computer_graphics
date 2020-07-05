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

void drawLineDDA(float x1,float y1,float x2,float y2)
{
	int dx=x2-x1,dy=y2-y1,steps=0,i=0,kc=0;
	printf("%d %d",dx,dy);
	float x=x1,y=y1,xinc=0,yinc=0;
	if(abs(x2-x1)>abs(y2-y1))
		steps=abs(dx);
	else
		steps=abs(dy);
	xinc=float(dx)/steps;
	yinc=float(dy)/steps;
	printf("%d %f %f",steps,xinc,yinc);
	kc=0;
	mode=0;
	for(i=0;i<steps;i++)
	{
		if(kc>=k[mode])
		{
			kc=0;
			mode=(mode+1)%4;
		}
		kc++;
		if(mode==0 || mode==2)
			plot(x,y);
		x+=xinc;
		y+=yinc;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	drawLineDDA(xb1,yb1,xb1,yb2);
	drawLineDDA(xb1,yb2,xb2,yb2);
	drawLineDDA(xb2,yb2,xb2,yb1);
	drawLineDDA(xb2,yb1,xb1,yb1);
	if(displayLine==1)
		drawLineDDA(xl1,yl1,xl2,yl2);
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
