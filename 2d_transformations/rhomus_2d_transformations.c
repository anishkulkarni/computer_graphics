#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>
#include<math.h>

int xbase,ybase,length;
int rhombus[4][3];
int rhombusBackup[4][3];
float transformMatrix[3][3];

void draw_line(int,int,int,int);

void transform()
{
	int i=0,j=0,k=0;
	int temp[4][3]={0};
	for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=0;
			for(k=0;k<3;k++)
			{
				temp[i][j]+=rhombus[i][k]*transformMatrix[k][j];
			}
		}
	}
	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
			rhombus[i][j]=temp[i][j];
}

void display()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
		glVertex2i(rhombus[0][0],rhombus[0][1]);
		glVertex2i(rhombus[1][0],rhombus[1][1]);
	
		glVertex2i(rhombus[1][0],rhombus[1][1]);
		glVertex2i(rhombus[2][0],rhombus[2][1]);
		
		glVertex2i(rhombus[2][0],rhombus[2][1]);
		glVertex2i(rhombus[3][0],rhombus[3][1]);

		glVertex2i(rhombus[3][0],rhombus[3][1]);
		glVertex2i(rhombus[0][0],rhombus[0][1]);
	glEnd();
	glFlush();
}

void generateRhombus()
{
	rhombus[0][0]=xbase;
	rhombus[0][1]=ybase;
	rhombus[0][2]=1;
	rhombus[1][0]=xbase+(length/1.414);
	rhombus[1][1]=ybase+(length/1.414);
	rhombus[1][2]=1;
	rhombus[2][0]=xbase+(2*length/1.414);
	rhombus[2][1]=ybase;
	rhombus[2][2]=1;
	rhombus[3][0]=xbase+(length/1.414);
	rhombus[3][1]=ybase-(length/1.414);
	rhombus[3][2]=1;
}

void backupRhombus()
{
	int i=0,j=0;
	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
			rhombusBackup[i][j]=rhombus[i][j];
}

void restoreRhombus()
{
	int i=0,j=0;
	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
			rhombus[i][j]=rhombusBackup[i][j];
}

void translate()
{
	printf("Enter the translation distance in x direction: ");
	scanf("%f",&transformMatrix[2][0]);
	printf("Enter the translation distance in y direction: ");
	scanf("%f",&transformMatrix[2][1]);
	transformMatrix[0][0]=1;
	transformMatrix[0][1]=0;
	transformMatrix[0][2]=0;
	transformMatrix[1][0]=0;
	transformMatrix[1][1]=1;
	transformMatrix[1][2]=0;
	transformMatrix[2][2]=1;
	transform();
}

void scale()
{
	printf("Enter the scaling factor in x direction: ");
	scanf("%f",&transformMatrix[0][0]);
	printf("Enter the scaling factor in y direction: ");
	scanf("%f",&transformMatrix[1][1]);
	transformMatrix[0][1]=0;
	transformMatrix[0][2]=0;
	transformMatrix[1][0]=0;
	transformMatrix[1][2]=0;
	transformMatrix[2][0]=0;
	transformMatrix[2][1]=0;
	transformMatrix[2][2]=1;
	transform();
}

void rotate()
{
	float angle;
	int i=0,j=0;
	printf("Enter the angle of rotation: ");
	scanf("%f",&angle);
	angle=angle*(3.14/180);
	transformMatrix[0][0]=cos(angle);
	transformMatrix[0][1]=sin(angle);
	transformMatrix[1][0]=-sin(angle);
	transformMatrix[1][1]=cos(angle);
	transformMatrix[1][2]=0;
	transformMatrix[2][0]=0;
	transformMatrix[2][1]=0;
	transformMatrix[2][2]=1;
	for(i=0;i<4;i++)
	{
		rhombus[i][0]-=xbase;
		rhombus[i][1]-=ybase;
	}
	transform();
	for(i=0;i<4;i++)
	{
		rhombus[i][0]+=xbase;
		rhombus[i][1]+=ybase;
	}
}

void shear()
{
	printf("Enter the shear factor in x direction: ");
	scanf("%f",&transformMatrix[1][0]);
	printf("Enter the shear factor in y direction: ");
	scanf("%f",&transformMatrix[0][1]);
	transformMatrix[0][0]=1;
	transformMatrix[0][2]=0;
	transformMatrix[1][1]=1;
	transformMatrix[1][2]=0;
	transformMatrix[2][0]=0;
	transformMatrix[2][1]=0;
	transformMatrix[2][2]=1;
	transform();
}

int main(int argc, char** argv)
{
	int choice;
	glutInit(&argc, argv);
	printf("Enter the co-ordinates of the left bottom of rhombus: ");
	scanf("%d%d", &xbase, &ybase);
	printf("Enter the length of rhombus: ");
	scanf("%d",&length);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Transformation");
	gluOrtho2D(-960,960,-540,540);
	generateRhombus();
	backupRhombus();
	display();
	do
	{
		printf("\nMenu\n1. Translate\n2. Scale\n3. Rotate\n4. Shear\n5. Restore\n6. Exit\nChoice: ");
		scanf("%d",&choice);
		switch(choice)
		{
		case 1:
			translate();
			display();
			break;
		case 2:
			scale();
			display();
			break;
		case 3:
			rotate();
			display();
			break;
		case 4:
			shear();
			display();
			break;
		case 5:
			restoreRhombus();
			display();
			break;
		case 6:
			return 0;
		}
	}while(1);
}
