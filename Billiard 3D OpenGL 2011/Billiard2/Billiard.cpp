#define _WIN32_WINDOWS 0x0410
#include <windows.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include "table.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "glaux.h"
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib,"glaux.lib")
static	HGLRC hRC;		
static	HDC hDC;	

struct Ball
{
	double x,z; //координаты
	int angle; //угол (направление)
	float acceleration; //начальное ускорение
};
double animation[29][2]=
		{
			0.004,-1.932,
			0.008,-1.932,
			0.012,-1.932,
			0.016,-1.932,
			0.020,-1.932,
			0.024,-1.932,
			0.028,-1.932,
			0.032,-1.932,
			0.036,-1.932,
			0.040,-1.932,
			0.044,-1.932,
			0.048,-1.932,
			0.052,-1.932,
			0.056,-1.932,
			0.058,-1.933,
			0.069,-1.936,
			0.080,-1.941,
			0.090,-1.948,
			0.098,-1.956,
			0.105,-1.966,
			0.110,-1.978,
			0.113,-1.988,
			0.114,-2.000,
			0.114,-2.011,
			0.114,-2.023,
			0.114,-2.034,
			0.114,-2.045,
			0.114,-2.056,
			0.114,-2.068
		};
Ball ball[16];
POINT xm;
int wheel,selected, inc, Anim[6],score; 
int newx, newy,RotateY,RotateX;//угол камеры
double x,z,Aa,Bb,xi,yi,xj,yj,force,scale; //координаты камеры
bool menu1,menu2,menu3,new1,cont,exit1,yes,no,menu11,menu22,menu33;
GLuint	texture[6];
bool ifcross[120],showball[16],overforce,ifblack[6],rkm,LKM,lkm,blw,bls,bla,bld; 

GLuint  base;    
GLYPHMETRICSFLOAT gmf[256];
GLfloat LightDiffuse[]= { 0.8f, 0.8f, 0.8f, 0.0f };
GLfloat LightPosition[]= { 0.0f, 4.0f, -3.2f, 0.0f }; 
GLfloat LightDirection[]= { 0.0f, 0.0f, 0.0f, 0.0f };

GLvoid Initial(GLsizei Width, GLsizei Height);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
GLvoid Resize(GLsizei Width, GLsizei Height);
GLvoid Draw();
void DefaultPosition();

GLsizei Width, Height;
GLUquadricObj *quadratic;

GLvoid BuildFont(GLvoid)  
{
	HFONT  font;         
	base = glGenLists(96); 
	font = CreateFont(  -200,        // Высота фонта
						0,        // Ширина фонта
						0,        // Угол отношения
						0,        // Угол наклона
						1000,      // Ширина шрифта
						FALSE,        // Курсив
						FALSE,        // Подчеркивание
						FALSE,        // Перечеркивание
						RUSSIAN_CHARSET,      // Идентификатор набора символов
						OUT_TT_PRECIS,      // Точность вывода
						CLIP_DEFAULT_PRECIS,    
						ANTIALIASED_QUALITY,   
						FF_DONTCARE|DEFAULT_PITCH,  // Семейство и шаг
							L"Times New Roman");      // Имя шрифта

  SelectObject(hDC, font);      
  wglUseFontOutlines( hDC,      
						0,       
						256,        
						base,        
						0.0f,      
						0.3f,       //Толщина шрифта по оси Z
						WGL_FONT_POLYGONS,      
						gmf);     
}

GLvoid KillFont(GLvoid)           
{
   glDeleteLists(base, 96);        
}

GLvoid glPrint(const char *fmt, ...)      
{
	char    text[256];    
	va_list    ap;       
	if (fmt == NULL)     
	return;          
	va_start(ap, fmt);         
	vsprintf(text, fmt, ap); 
	va_end(ap);                
	glPushAttrib(GL_LIST_BIT);    
	glListBase(base);         
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib(); 
}

void DefaultPosition()
{
	for(int i = 0; i < 6; i++)
	{
		Anim[i]=30;
		ifblack[i]=false;
	}
	for(int i = 0; i < 16; i++)
	{
		ball[i].acceleration=0;
		showball[i]=true;
	}
		ball[0].x=0.0f;
		ball[0].z=-1.6f;

		ball[1].x=0.0f;
		ball[1].z=-4.8f;

		ball[2].x=-0.069f;
		ball[2].z=-4.919f;
		ball[3].x=0.069f;
		ball[3].z=-4.919f;

		ball[4].x=-0.137f;
		ball[4].z=-5.038f;
		ball[5].x=0.0f;
		ball[5].z=-5.038f;
		ball[6].x=0.137f;
		ball[6].z=-5.038f;

		ball[7].x=-0.206f;
		ball[7].z=-5.156f;
		ball[8].x=-0.069f;
		ball[8].z=-5.156f;
		ball[9].x=0.069f;
		ball[9].z=-5.156f;
		ball[10].x=0.206f;
		ball[10].z=-5.156f;

		ball[11].x=-0.274f;
		ball[11].z=-5.275f;
		ball[12].x=-0.137f;
		ball[12].z=-5.275f;
		ball[13].x=0.0f;
		ball[13].z=-5.275f;
		ball[14].x=0.137f;
		ball[14].z=-5.275f;
		ball[15].x=0.274f;
		ball[15].z=-5.275f;
		
		selected=0;
		x=-ball[0].x;
		z=-ball[0].z;
		RotateY=0;
		RotateX=0;
}

inline GLvoid BallPosition(double x, double z)
{
	glTranslatef(x,-1.932f,z);
	gluSphere(quadratic, 0.068f,24,24);
	glTranslatef(0,-0.0678f,0);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.3f, 0.6f, 0.3f);
	gluDisk(quadratic,0.0f,0.055f,16,16);
}

inline GLvoid Animation(int N)
{
	if(N==0)
	{
		glTranslatef(1.532,0,-3.2);
	}
	if(N==1)
	{
		glTranslatef(1.532,0,-0.068);
		glRotatef(315, 0, 1, 0);
	}
	if(N==2)
	{
		glTranslatef(-1.532,0,-0.068);
		glRotatef(225, 0, 1, 0);
	}
	if(N==3)
	{
		glTranslatef(-1.532,0,-3.2);
		glRotatef(180, 0, 1, 0);
	}
	if(N==4)
	{
		glTranslatef(-1.532,0,-6.332);
		glRotatef(135, 0, 1, 0);
	}
	if(N==5)
	{
		glTranslatef(1.532,0,-6.332);
		glRotatef(45, 0, 1, 0);
	}
	glTranslatef(animation[Anim[N]][0],animation[Anim[N]][1],0);
	gluSphere(quadratic, 0.068f,16,16);
	glTranslatef(0,-0.0678f,0);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.3f, 0.6f, 0.3f);
	gluDisk(quadratic,0.0f,0.055f,16,16);
	Anim[N]++;
}

inline GLvoid CameraPosition(double x, double z)
{
	glLoadIdentity();
	glTranslatef( 0, 0+scale*0.3, -2.8+scale );
	glRotatef(RotateX, 1, 0, 0);
	glRotatef(RotateY, 0, 1, 0);
	glTranslatef( x, 0.8, z );
}

GLvoid Initial()
{ 
	AUX_RGBImageRec *texture1;
	glGenTextures(5, &texture[0]);

	texture1 = auxDIBImageLoad("table/sukno.bbp");
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("table/bort.bbp");
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("table/nogi.bbp");
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("table/pol.bbp");
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("table/stena.bbp");
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("table/menu.bbp");
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	quadratic=gluNewQuadric();    
    gluQuadricNormals(quadratic, GLU_SMOOTH); 
    gluQuadricTexture(quadratic, GL_TRUE);    

	glEnable(GL_LIGHTING);
	
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(150.0f, (GLfloat)Width / (GLfloat)Height, 0.01f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_COLOR_MATERIAL);
	 glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	BuildFont(); 
}

GLvoid Resize(GLsizei Width, GLsizei Height)
{
	if(Height==0)
	Height = 1;
	glViewport(0, 0, Width, Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65.0f, (GLfloat)Width /(GLfloat)Height, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
GLvoid DrawMenu1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	LightPosition[0]=  0.0f;
	LightPosition[1]=  0.0f;
	LightPosition[2]=  -4.0f;
	LightPosition[3]=  0.0f;
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, LightDirection);
	glEnable(GL_LIGHT1);
	
	glLoadIdentity();
	LightPosition[0]=  0.0f;
	LightPosition[1]=  0.0f;
	LightPosition[2]=  1.0f;
	LightPosition[3]=  1.0f;
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION, LightDirection);
	glEnable(GL_LIGHT2);
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	if(!new1)
	{glTranslatef(-2.3f,0.0f,-2.95f);glColor3f(0.9f, 0.65f, 0.0f);}
	else
	glTranslatef(-2.3f,0.0f,-2.7f);
	glPrint ("новая игра");

	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	if(!exit1)
	{glTranslatef(-1.3f,-0.8f,-2.95f);glColor3f(0.9f, 0.65f, 0.0f);}
	else
	glTranslatef(-1.3f,-0.8f,-2.7f);
	glPrint ("выход");

	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0.0f,0.5f,-6.4f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);m();
		glTexCoord2f(1.0f, 1.0f);l();
		glTexCoord2f(1.0f, 0.0f);L();
		glTexCoord2f(0.0f, 0.0f);M();
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

GLvoid DrawMenu2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	LightPosition[0]=  0.0f;
	LightPosition[1]=  0.0f;
	LightPosition[2]=  -4.0f;
	LightPosition[3]=  0.0f;
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, LightDirection);
	glEnable(GL_LIGHT1);
	
	glLoadIdentity();
	LightPosition[0]=  0.0f;
	LightPosition[1]=  0.0f;
	LightPosition[2]=  1.0f;
	LightPosition[3]=  1.0f;
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION, LightDirection);
	glEnable(GL_LIGHT2);
	
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	if(!cont)
	{glTranslatef(-2.5f,0.8f,-2.95f);glColor3f(0.9f, 0.65f, 0.0f);}
	else
	glTranslatef(-2.5f,0.8f,-2.7f);
	glPrint ("продолжить");

	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	if(!new1)
	{glTranslatef(-2.3f,0.0f,-2.95f);glColor3f(0.9f, 0.65f, 0.0f);}
	else
	glTranslatef(-2.3f,0.0f,-2.7f);
	glPrint ("новая игра");

	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	if(!exit1)
	{glTranslatef(-1.3f,-0.8f,-2.95f);glColor3f(0.9f, 0.65f, 0.0f);}
	else
	glTranslatef(-1.3f,-0.8f,-2.7f);
	glPrint ("выход");

	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0.0f,0.5f,-6.4f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);m();
		glTexCoord2f(1.0f, 1.0f);l();
		glTexCoord2f(1.0f, 0.0f);L();
		glTexCoord2f(0.0f, 0.0f);M();
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

GLvoid DrawMenu3()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	LightPosition[0]=  0.0f;
	LightPosition[1]=  0.0f;
	LightPosition[2]=  0.0f;
	LightPosition[3]=  0.0f;
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, LightDirection);
	glEnable(GL_LIGHT1);
	
	glLoadIdentity();
	LightPosition[0]=  0.0f;
	LightPosition[1]=  0.0f;
	LightPosition[2]=  1.0f;
	LightPosition[3]=  1.0f;
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION, LightDirection);
	glEnable(GL_LIGHT2);
	
	glLoadIdentity();
	glColor3f(0.9f, 0.65f, 0.0f);
	glTranslatef(-1.6f,0.8f,-2.95f);
	glPrint ("Уверен?");

	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	if(!no)
	{glTranslatef(-0.6f,-0.8f,-2.95f);glColor3f(0.9f, 0.65f, 0.0f);}
	else
	glTranslatef(-0.6f,-0.8f,-2.7f);
	glPrint ("нет");

	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	if(!yes)
	{glTranslatef(-0.4f,0.0f,-2.95f);glColor3f(0.9f, 0.65f, 0.0f);}
	else
	glTranslatef(-0.4f,0.0f,-2.7f);
	glPrint ("да");

	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0.0f,0.5f,-6.4f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);m();
		glTexCoord2f(1.0f, 1.0f);l();
		glTexCoord2f(1.0f, 0.0f);L();
		glTexCoord2f(0.0f, 0.0f);M();
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

GLvoid Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	glDisable(GL_LIGHT2);
	CameraPosition(x, z);
	glTranslatef(0,-0.5,6.8);
	LightPosition[0]=  0.0f;
	LightPosition[1]=  1.0f;
	if(RotateX<375)
	LightPosition[2]=  -4.2f;
	else
	LightPosition[2]=  -2.5f;
	LightPosition[3]=  0.3f;
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);//отсвечивание
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);//положение
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, LightDirection);//направление
	glEnable(GL_LIGHT1);

	////////индикатор силы/////
	glLoadIdentity();
	glEnable(GL_LIGHT2);
	glTranslatef(0,0,-0.3);
	glBegin(GL_QUADS);
	glColor3f(force, 1-force, 0.0f);

		glVertex3f(	0.17f,-0.15f+force*0.16, 0.0f);
		glVertex3f( 0.20f,-0.15f+force*0.16, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);

		glVertex3f( 0.20f,-0.15f, 0.0f);
		glVertex3f( 0.17f,-0.15f, 0.0f);

	glEnd();
	////кий//////
	CameraPosition(x, z);
	glTranslatef(0-x,-1.932, 0-z);
	glRotatef(-RotateY, 0, 1, 0);
	glRotatef(347,1,0,0);
	glTranslatef(0,0, 0.068+force*0.6);
	glColor3f(0.737f, 0.353f, 0.094f);
	gluCylinder(quadratic,0.015f,0.03f,3.5,16,16);
	glDisable(GL_LIGHT2);
		/////////лампы/////////
	if(RotateX<375)
	{CameraPosition(x, z);
	//крепление

	glTranslatef(0,0.5,-0.75);
	glRotatef(180,1,0,0);
	glColor3f(0.7f, 0.3f, 0.5f);
	gluCylinder(quadratic,0.03f,0.03f,4.9,4,4);
	glRotatef(180,1,0,0);

	//светильники
	
	glRotatef(90,1,0,0);

	glTranslatef(0,-4.7f,0);
	glColor3f(0.3f, 0.7f, 0.5f);
	gluCylinder(quadratic,0.2f,0.7f,0.6f,16,16);
	glColor3f(1.0f, 1.0f, 1.0f);
	gluCylinder(quadratic,0.19f,0.69f,0.6f,16,16);

	glTranslatef(0,1.5,0);
	glColor3f(0.3f, 0.7f, 0.5f);
	gluCylinder(quadratic,0.2f,0.7f,0.6f,16,16);
	glColor3f(1.0f, 1.0f, 1.0f);
	gluCylinder(quadratic,0.19f,0.69f,0.6f,16,16);

	glTranslatef(0,1.5,0);
	glColor3f(0.3f, 0.7f, 0.5f);
	gluCylinder(quadratic,0.2f,0.7f,0.6f,16,16);
	glColor3f(1.0f, 1.0f, 1.0f);
	gluCylinder(quadratic,0.19f,0.69f,0.6f,16,16);

	glTranslatef(0,1.5,0);
	glColor3f(0.3f, 0.7f, 0.5f);
	gluCylinder(quadratic,0.2f,0.7f,0.6f,16,16);
	glColor3f(1.0f, 1.0f, 1.0f);
	gluCylinder(quadratic,0.19f,0.69f,0.6f,16,16);}
	///////////стол///////////
	CameraPosition(x, z);
	glColor3f(1.0f, 1.0f, 1.0f);
	Table(texture, quadratic);

	/////////////шарик 1 (чёрный)//////////////
	if(showball[0])
	{
		CameraPosition(x, z);
		glColor3f(0.5f, 0.3f, 0.3f);
		BallPosition(ball[0].x,ball[0].z);
	}
	
	/////////////шарик 2//////////////
	if(showball[1])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[1].x,ball[1].z);
	}

	/////////////шарик 3//////////////
	if(showball[2])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[2].x,ball[2].z);
	}
	
	/////////////шарик 4//////////////
	if(showball[3])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[3].x,ball[3].z);
	}
	
	/////////////шарик 5//////////////
	if(showball[4])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[4].x,ball[4].z);
	}
	
	/////////////шарик 6//////////////
	if(showball[5])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[5].x,ball[5].z);
	}
	
	/////////////шарик 7//////////////
	if(showball[6])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[6].x,ball[6].z);
	}

	/////////////шарик 8//////////////
	if(showball[7])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[7].x,ball[7].z);
	}

	/////////////шарик 9//////////////
	if(showball[8])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[8].x,ball[8].z);
	}

	/////////////шарик 10//////////////
	if(showball[9])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[9].x,ball[9].z);
	}

	/////////////шарик 11//////////////
	if(showball[10])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[10].x,ball[10].z);
	}

	/////////////шарик 12//////////////
	if(showball[11])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[11].x,ball[11].z);
	}

	/////////////шарик 13//////////////
	if(showball[12])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[12].x,ball[12].z);
	}

	/////////////шарик 14//////////////
	if(showball[13])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[13].x,ball[13].z);
	}

	/////////////шарик 15//////////////
	if(showball[14])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[14].x,ball[14].z);
	}

	/////////////шарик 16//////////////
	if(showball[15])
	{
		CameraPosition(x, z);
		glColor3f(1.0f, 1.0f, 1.0f);
		BallPosition(ball[15].x,ball[15].z);
	}
	if(Anim[0]<29)
	{
		CameraPosition(x, z);
		if(ifblack[0])
		glColor3f(0.5f, 0.3f, 0.3f);
		else
		glColor3f(1.0f, 1.0f, 1.0f);
		Animation(0);
	}
	else
	ifblack[0]=false;
	if(Anim[1]<29)
	{
		CameraPosition(x, z);
		if(ifblack[1])
		glColor3f(0.5f, 0.3f, 0.3f);
		else
		glColor3f(1.0f, 1.0f, 1.0f);
		Animation(1);
	}
	else
	ifblack[1]=false;
	if(Anim[2]<29)
	{
		CameraPosition(x, z);
		if(ifblack[2])
		glColor3f(0.5f, 0.3f, 0.3f);
		else
		glColor3f(1.0f, 1.0f, 1.0f);
		Animation(2);
	}
	else
	ifblack[2]=false;
	if(Anim[3]<29)
	{
		CameraPosition(x, z);
		if(ifblack[3])
		glColor3f(0.5f, 0.3f, 0.3f);
		else
		glColor3f(1.0f, 1.0f, 1.0f);
		Animation(3);
	}
	else
	ifblack[3]=false;
	if(Anim[4]<29)
	{
		CameraPosition(x, z);
		if(ifblack[4])
		glColor3f(0.5f, 0.3f, 0.3f);
		else
		glColor3f(1.0f, 1.0f, 1.0f);
		Animation(4);
	}
	else
	ifblack[4]=false;
	if(Anim[5]<29)
	{
		CameraPosition(x, z);
		if(ifblack[5])
		glColor3f(0.5f, 0.3f, 0.3f);
		else
		glColor3f(1.0f, 1.0f, 1.0f);
		Animation(5);
	}
	else
	ifblack[5]=false;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	GLuint PixelFormat;
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),		
			1,									
			PFD_DRAW_TO_WINDOW|					// format must support Window
			PFD_SUPPORT_OPENGL|					// format must support OpenGL
			PFD_DOUBLEBUFFER,					// must support double buffer
			PFD_TYPE_RGBA,						// требуется RGBA формат
			16,									// 16Bit color depth
			0, 0, 0, 0, 0, 0,					// Color bits ignored ?
			0,									// No Alpha buffer
			0,									// shift bit ignored
			0,									// no accumulation buffer
			0, 0, 0, 0,							// accumulation buffer bits ignored
			16,									// 16bit z-buffer (depth buffer)
			0,									// no stencil buffer
			0,									// no auxiliary buffer
			PFD_MAIN_PLANE,						// main drawing layer
			0,									// reserved
			0, 0, 0								// layer mask ignored
	};
	switch(msg)
	{
	case WM_CREATE:
		menu1=true;
		new1=true;
		RotateY=0;
		RotateX=360;
		score=16;
		selected=0;
		hDC = GetDC(hWnd);
		PixelFormat = ChoosePixelFormat(hDC, &pfd);
		SetPixelFormat(hDC, PixelFormat, &pfd);
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		Initial();
		break;
	case WM_DESTROY:
		printf("Why did you do that?! =(");
		getchar();
		ChangeDisplaySettings(NULL, 0);
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		ReleaseDC(hWnd, hDC);
		KillFont();
		PostQuitMessage(0);
		break;

		case WM_KEYDOWN:{
		switch( wParam )
		{
			case VK_ESCAPE:
				{
					if(!menu1 &&  !menu2 &&  !menu3)
					{
						menu3=false;
						menu2=true;
						menu1=false;
						cont=true;
						new1=false;
						exit1=false;
						break;
					}
					if(menu1)
					{
						menu3=true;
						menu2=false;
						menu1=false;
						menu11=true;
						yes=true;
						no=false;
						break;
					}
					if(menu2)
					{
						menu3=false;
						menu2=false;
						menu1=false;
						break;
					}
					break;
				}
			case 0x44:	//D	
				{ bld=true; break; }
			case 0x41:	//A
				{ bla=true; break; }
			case 0x57:	//W
				{ blw=true; break; }
			case 0x53:	//S
				{ bls=true; break; }
			case VK_RETURN:		
				{
					if(menu1 || menu2 || menu3)
					{
						if(menu1)
							if(new1)
							{
								menu1=false;
								menu2=false;
								menu3=false;
								menu22=false;
								menu11=false;
								menu33=false;
								DefaultPosition();break;
							}
							else
							{
								menu11=true;
								menu1=false;
								menu2 =false;
								menu3=true;
								yes=true;
								no=false;
								break;
							}
						if(menu2)
							if(cont)
							{
								menu1=false;
								menu2=false;
								menu3=false;
								menu22=false;
								menu11=false;
								menu33=false;break;
							}
							else
							{
								if(new1)
								{
									menu1=false;
									menu2 =false;
									menu3=true;
									menu22=true;
									yes=true;
									no=false;
									break;
								}
								else
								{
									menu1=false;
									menu2 =false;
									menu3=true;
									menu33=true;
									yes=true;
									no=false;
									break;
								}
							}
						if(menu3)
						{
							if(menu11)
								if(yes)
								{
									ChangeDisplaySettings(NULL, 0);
									wglMakeCurrent(hDC, NULL);
									wglDeleteContext(hRC);
									ReleaseDC(hWnd, hDC);
									KillFont();
									PostQuitMessage(0);break;
								}
								else
								{
									menu1=true;
									menu2=false;
									menu3=false;
									menu11=false;
									new1=true;
									exit1=false;
									break;
								}
							if(menu22)
								if(yes)
								{
									menu1=false;
									menu2=false;
									menu3=false;
									menu22=false;
									menu11=false;
									menu33=false;
									DefaultPosition();break;
								}
								else
								{
									menu1=false;
									menu2=true;
									menu3=false;
									menu22=false;
									cont=true;
									new1=false;
									exit1=false;
									break;
								}
							if(menu33)
								if(yes)
								{
									ChangeDisplaySettings(NULL, 0);
									wglMakeCurrent(hDC, NULL);
									wglDeleteContext(hRC);
									ReleaseDC(hWnd, hDC);
									KillFont();
									PostQuitMessage(0);break;
								}
								else
								{
									menu1=false;
									menu2=true;
									menu3=false;
									menu33=false;
									cont=true;
									new1=false;
									exit1=false;
									break;
								}
						}
					}
					break;
				}
			case VK_UP:
				{	
					if(menu1)
						if(new1)
						{
							exit1=true;
							new1=false;
						}
						else
						{
							exit1=false;
							new1=true;
						}
					if(menu2)
						if(cont)
						{
							exit1=true;
							new1=false;
							cont=false;
						}
						else
						{
							if(new1)
							{
								exit1=false;
								cont=true;
								new1=false;
							}
							else
							{
								exit1=false;
								cont=false;
								new1=true;
							}
						}
					if(menu3)
						if(yes)
						{
							no=true;
							yes=false;
						}
						else
						{
							no=false;
							yes=true;
						}
					break;
				}
			case VK_DOWN:
				{ 
					if(menu1)
						if(new1)
						{
							exit1=true;
							new1=false;
						}
						else
						{
							exit1=false;
							new1=true;
						}
					if(menu2)
						if(cont)
						{
							exit1=false;
							new1=true;
							cont=false;
						}
						else
						{
							if(new1)
							{
								exit1=true;
								cont=false;
								new1=false;
							}
							else
							{
								exit1=false;
								cont=true;
								new1=false;
							}
						}
					if(menu3)
						if(yes)
						{
							no=true;
							yes=false;
						}
						else
						{
							no=false;
							yes=true;
						}
					break;
				}
		}
		}
		break;
		case WM_KEYUP:
			{	
				if(wParam==0x57)blw=false;
				if(wParam==0x53)bls=false;
				if(wParam==0x41)bla=false;
				if(wParam==0x44)bld=false;
				break;
			}
		case WM_MOUSEMOVE:
		{
			GetCursorPos(&xm);
			newx = LOWORD(lParam);
			newy = HIWORD(lParam);
			if (newx >720)
			{
				if(newy>450)
				SetCursorPos(360+xm.x-newx, 450+xm.y-newy);
				else
				SetCursorPos(360+xm.x-newx, xm.y);
				if(newy<352)
				SetCursorPos(360+xm.x-newx, 352+xm.y-newy);
				else
				SetCursorPos(360+xm.x-newx, xm.y);
			}
			else
			{
				if(newy>450)
				SetCursorPos(xm.x, 450+xm.y-newy);
				if(newy<352)
				SetCursorPos(xm.x, 352+xm.y-newy);
			}
			if (newx <360)
			{
				if(newy>450)
				SetCursorPos(720+xm.x-newx, 450+xm.y-newy);
				else
				SetCursorPos(720+xm.x-newx, xm.y);
				if(newy<352)
				SetCursorPos(720+xm.x-newx, 352+xm.y-newy);
				else
				SetCursorPos(720+xm.x-newx, xm.y);
			}
			else
			{
				if(newy>450)
				SetCursorPos(xm.x, 450+xm.y-newy);
				if(newy<352)
				SetCursorPos(xm.x, 352+xm.y-newy);
			}
			
			if(rkm)
			{
				if(newy>449)newy=449;
				if(newy<360)newy=360;
				newy=newy%90;
				scale=(float)newy/50;
			}
			else
			{
				RotateY=newx;
				RotateX=newy;
				while(RotateY>=360) RotateY-=360;
			}
			break;
		}
		case WM_MOUSEWHEEL:
		{
			if(score)
			{
				wheel=HIWORD(wParam);
				if(wheel==120)
				{
					do{
						selected++;
						if(selected>15)selected=0;
						x=-ball[selected].x;
						z=-ball[selected].z;
					}while(!showball[selected]);
				}
				if(wheel==65416)
				{
					
					do{
						selected--;
						if(selected<0)selected=15;
						x=-ball[selected].x;
						z=-ball[selected].z;
					}while(!showball[selected]);
				}
			}
			break;
		}
		case WM_RBUTTONDOWN:
		{ rkm=true; break; }
		case WM_RBUTTONUP:
		{ rkm=false; break; }
		case WM_LBUTTONDOWN:
		{	
			if(showball[selected])
			if(!LKM)
			{
				if(!lkm)force=0;
				lkm=true;
			}
			break;
		}
		case WM_LBUTTONUP:
		{
			if(score)
			{
				if(showball[selected])
				if(!LKM)
				{
					LKM=true;
					lkm=false;
					ball[selected].angle=-RotateY;
					ball[selected].acceleration=force;
					force=0;
				}
			}
			break;
		}
	case WM_SIZE:{Resize(LOWORD(lParam), HIWORD(lParam));break;}
	default:return( DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return 0;
}

using namespace std;

int main( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, int nShowCmd)
{

	double length=0.08f, movement=0.03f, deaccel=0.001f, grad=3.14159265/180,agrad=180/3.14159265,T;
	int gamai,gamaj,beta,perfom=0;

	cout<<"Please wait a few seconds while testing your computer!\n"<<endl;
	cout<<"\"Bad perfomance\"       -   Many wrong collisions"<<endl;
	cout<<"\"Medium perfomance\"    -   Frequent wrong collisions"<<endl;
	cout<<"\"Good perfomance\"      -   Some few wrong collisions"<<endl;
	cout<<"\"Excellent perfomance\" -   A very low number of wrong collisions"<<endl;

	T=GetTickCount();
	while(perfom<3000000000)
	{perfom++;}
	T=((GetTickCount()-T)/100)/72;
	if(T<=1.05)T=1;
	length*=T;
	movement*=T;
	deaccel*=T;

	if(T>=2)cout<<"\tBad perfomance"<<endl;
	if(T<2 && T>=1.5)cout<<"\tMedium perfomance"<<endl;
	if(T<1.5 && T>1.05)cout<<"\tGood perfomance"<<endl;
	if(T<=1.05)cout<<"\tExcellent perfomance"<<endl;
	
	Sleep(1500);
	MSG			msg;
	WNDCLASS	wc;
	HWND		hWnd;

	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc	= (WNDPROC)WndProc;
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= hInst;
	wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor		=LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= L"Billiard_Petrov";

	RegisterClass(&wc); 
	hWnd = CreateWindow(L"Billiard_Petrov",L"Billiard by D. Petrov",WS_POPUP |WS_OVERLAPPEDWINDOW |WS_CLIPSIBLINGS, -8, -30, 
						GetSystemMetrics(SM_CXSCREEN)+16, GetSystemMetrics(SM_CYSCREEN)+8, NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	SetFocus(hWnd);
	SetCursorPos(360,360);
	ShowCursor(false);

	while(1)
	{
		
		while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				return TRUE;
			}
		}
	if(menu1)
		DrawMenu1();
	else
	if(menu2)
		DrawMenu2();
	else
	if(menu3)
		DrawMenu3();
	else
	{
///вычисления///
			if(blw)	{	
					z+=movement*cos(RotateY*3.14/180);
					if(z < -0.6) {z=-0.6;}
					if(z > 6.8) {z=6.8;}
					x+=(-1)*movement*sin(RotateY*3.14/180);
					if(x < (-2)){x=(-2);}
					if(x > 2) {x=2;}
					}
			if(bls)	{
					z-=movement*cos(RotateY*3.14/180);
					if(z < -0.6) {z=-0.6;}
					if(z > 6.8) {z=6.8;}
					x-=(-1)*movement*sin(RotateY*3.14/180);
					if(x < (-2)){x=(-2);}
					if(x > 2) {x=2;}
					}			
			if(bla)	{
					z+=movement*sin(RotateY*3.14/180);
					if(z < -0.6) {z=-0.6;}
					if(z > 6.8) {z=6.8;}
					x+=movement*cos(RotateY*3.14/180);
					if(x < (-2)){x=(-2);}
					if(x > 2) {x=2;}
					}
			if(bld)	{
					z-=movement*sin(RotateY*3.14/180);
					if(z < -0.6) {z=-0.6;}
					if(z > 6.8) {z=6.8;}
					x-=movement*cos(RotateY*3.14/180);
					if(x < (-2)){x=(-2);}
					if(x > 2) {x=2;}
					}
	if(lkm)
	{
		
		if(!overforce)
		{
			force+=0.01;
			if(force>=1)
			overforce=true;
		}
		if(overforce)
		{
			force-=0.01;
			if(force<=0)
			overforce=false;
		}
	}
	if(LKM)
	{
		if(showball[0]){
		ball[0].x-=length*sin(ball[0].angle*grad)*ball[0].acceleration;
		ball[0].z-=length*cos(ball[0].angle*grad)*ball[0].acceleration;}
		if(showball[1]){
		ball[1].x-=length*sin(ball[1].angle*grad)*ball[1].acceleration;
		ball[1].z-=length*cos(ball[1].angle*grad)*ball[1].acceleration;}
		if(showball[2]){
		ball[2].x-=length*sin(ball[2].angle*grad)*ball[2].acceleration;
		ball[2].z-=length*cos(ball[2].angle*grad)*ball[2].acceleration;}
		if(showball[3]){
		ball[3].x-=length*sin(ball[3].angle*grad)*ball[3].acceleration;
		ball[3].z-=length*cos(ball[3].angle*grad)*ball[3].acceleration;}
		if(showball[4]){
		ball[4].x-=length*sin(ball[4].angle*grad)*ball[4].acceleration;
		ball[4].z-=length*cos(ball[4].angle*grad)*ball[4].acceleration;}
		if(showball[5]){
		ball[5].x-=length*sin(ball[5].angle*grad)*ball[5].acceleration;
		ball[5].z-=length*cos(ball[5].angle*grad)*ball[5].acceleration;}
		if(showball[6]){
		ball[6].x-=length*sin(ball[6].angle*grad)*ball[6].acceleration;
		ball[6].z-=length*cos(ball[6].angle*grad)*ball[6].acceleration;}
		if(showball[7]){
		ball[7].x-=length*sin(ball[7].angle*grad)*ball[7].acceleration;
		ball[7].z-=length*cos(ball[7].angle*grad)*ball[7].acceleration;}
		if(showball[8]){
		ball[8].x-=length*sin(ball[8].angle*grad)*ball[8].acceleration;
		ball[8].z-=length*cos(ball[8].angle*grad)*ball[8].acceleration;}
		if(showball[9]){
		ball[9].x-=length*sin(ball[9].angle*grad)*ball[9].acceleration;
		ball[9].z-=length*cos(ball[9].angle*grad)*ball[9].acceleration;}
		if(showball[10]){
		ball[10].x-=length*sin(ball[10].angle*grad)*ball[10].acceleration;
		ball[10].z-=length*cos(ball[10].angle*grad)*ball[10].acceleration;}
		if(showball[11]){
		ball[11].x-=length*sin(ball[11].angle*grad)*ball[11].acceleration;
		ball[11].z-=length*cos(ball[11].angle*grad)*ball[11].acceleration;}
		if(showball[12]){
		ball[12].x-=length*sin(ball[12].angle*grad)*ball[12].acceleration;
		ball[12].z-=length*cos(ball[12].angle*grad)*ball[12].acceleration;}
		if(showball[13]){
		ball[13].x-=length*sin(ball[13].angle*grad)*ball[13].acceleration;
		ball[13].z-=length*cos(ball[13].angle*grad)*ball[13].acceleration;}
		if(showball[14]){
		ball[14].x-=length*sin(ball[14].angle*grad)*ball[14].acceleration;
		ball[14].z-=length*cos(ball[14].angle*grad)*ball[14].acceleration;}
		if(showball[15]){
		ball[15].x-=length*sin(ball[15].angle*grad)*ball[15].acceleration;
		ball[15].z-=length*cos(ball[15].angle*grad)*ball[15].acceleration;}
		/////рассчет углов и ускорений при столкновении шара с шаром	
		inc=0;
		for(int i=0 ; i<15 ; i++)
		{
			if(showball[i])
			for(int j=i+1 ; j<16 ; j++)
			{	
				if(showball[j])
				if(pow((ball[i].x-ball[j].x),2)+pow((ball[i].z-ball[j].z),2) < 0.018496)
				{	
					if(!ifcross[inc])
						if(ball[j].z<ball[i].z)
			/*1, 2*/	{
							beta=asin((ball[j].x-ball[i].x)/sqrt(pow((ball[j].x-ball[i].x),2)+pow((ball[j].z-ball[i].z),2)))*agrad;
							gamai=(360-ball[i].angle-beta+360)%360;
							gamaj=(360-ball[j].angle-beta+360)%360;
							
							Aa=ball[i].acceleration*cos(gamai*grad);
							Bb=-ball[j].acceleration*cos(gamaj*grad);
							////////////////////
							if(Aa<0.0f)
							{
								xi=Aa-Bb;
								yi=ball[i].acceleration*sin(gamai*grad);
							}
							else
							{
								xi=-((ball[i].acceleration-Aa)*cos(gamai*grad)+Bb);
								yi=(ball[i].acceleration-Aa)*sin(gamai*grad);
							}

							ball[i].acceleration=sqrt(xi*xi+yi*yi);
							if(yi<0.0f)
							ball[i].angle=float(acos( xi/ (ball[i].acceleration+0.0000001))*agrad-beta);
							else
							ball[i].angle=float(360-acos( xi/ (ball[i].acceleration+0.0000001))*agrad-beta);
							///////////////////
							if(Bb<0.0f)
							{
								xj=Aa-Bb;
								yj=ball[j].acceleration*sin(gamaj*grad);
							}
							else
							{
								xj=Aa-(ball[j].acceleration-Bb)*cos(gamaj*grad);
								yj=(ball[j].acceleration-Bb)*sin(gamaj*grad);
							}

							ball[j].acceleration=sqrt(xj*xj+yj*yj);
							if(yj<0.0f)
							ball[j].angle=float(acos( xj/ (ball[j].acceleration+0.0000001))*agrad-beta);
							else
							ball[j].angle=float(360-acos( xj/ (ball[j].acceleration+0.0000001))*agrad-beta);
							///////////////////
						}
						else
			/*3, 4*/	{
							beta=asin((ball[i].x-ball[j].x)/sqrt(pow((ball[j].x-ball[i].x),2)+pow((ball[j].z-ball[i].z),2)))*agrad;
							gamai=(360-ball[i].angle-beta+360)%360;
							gamaj=(360-ball[j].angle-beta+360)%360;
						
							Bb=-ball[i].acceleration*cos(gamai*grad);
							Aa=ball[j].acceleration*cos(gamaj*grad);
							//////////////////
							if(Aa<0.0f)
							{
								xj=Aa-Bb;
								yj=ball[j].acceleration*sin(gamaj*grad);
							}
							else
							{
								xj=-((ball[j].acceleration-Aa)*cos(gamaj*grad)+Bb);
								yj=(ball[j].acceleration-Aa)*sin(gamaj*grad);
							}

							ball[j].acceleration=sqrt(xj*xj+yj*yj);
							if(yj<0.0f)
							ball[j].angle=float(acos( xj/ (ball[j].acceleration+0.0000001))*agrad-beta);
							else
							ball[j].angle=float(360-acos( xj/ (ball[j].acceleration+0.0000001))*agrad-beta);
							/////////////////
							if(Bb<0.0f)
							{
								xi=Aa-Bb;
								yi=ball[i].acceleration*sin(gamai*grad);
							}
							else
							{	
								xi=Aa-(ball[i].acceleration-Bb)*cos(gamai*grad);
								yi=(ball[i].acceleration-Bb)*sin(gamai*grad);
							}

							ball[i].acceleration=sqrt(xi*xi+yi*yi);
							if(yi<0.0f)
							ball[i].angle=float(acos( xi/ (ball[i].acceleration+0.0000001))*agrad-beta);
							else
							ball[i].angle=float(360-acos( xi/ (ball[i].acceleration+0.0000001))*agrad-beta);
							////////////////
						}
						ifcross[inc]=true;
						for(j=j+1;j<16;j++)
						{
							inc++;
							ifcross[inc]=false;
						}
						//break;
				}
				else
				{
					ifcross[inc]=false;
					inc++;
				}
			}
			else
			for(int j=i+1;j<16;j++)
			{
				inc++;
				ifcross[inc]=false;
			}
		}
		/////столкновение с бортами
			for(int i=0 ; i<16 ; i++)
			{
				if(!showball[i])continue;

				if(ball[i].z < -6.332)
				{
					if(ball[i].x < -1.511)
					{
						showball[i]=false;
						if(i==0)ifblack[4]=true;
						ball[i].acceleration=0;
						Anim[4]=0;
						score--;
					}
					else
					if(ball[i].x > 1.511)
					{
						showball[i]=false;
						if(i==0)ifblack[5]=true;
						ball[i].acceleration=0;
						Anim[5]=0;
						score--;;
					}
					else
					ball[i].z = -6.332;ball[i].angle=540-ball[i].angle;
				}
				else
				if(ball[i].z > -0.068)
				{
					if(ball[i].x < -1.511)
					{
						showball[i]=false;
						if(i==0)ifblack[2]=true;
						ball[i].acceleration=0;
						Anim[2]=0;
						score--;
					}
					else
					if(ball[i].x > 1.511)
					{
						showball[i]=false;
						if(i==0)ifblack[1]=true;
						ball[i].acceleration=0;
						Anim[1]=0;
						score--;
					}
					else
					ball[i].z = -0.068;ball[i].angle=540-ball[i].angle;
				}
				else
				if(ball[i].x < -1.532)
				{
					if(ball[i].z<-3.183 && ball[i].z>-3.217)
					{
						showball[i]=false;
						if(i==0)ifblack[3]=true;
						ball[i].acceleration=0;
						Anim[3]=0;
						score--;
					}
					else
					if(ball[i].z<-6.311)
					{
						showball[i]=false;
						if(i==0)ifblack[4]=true;
						ball[i].acceleration=0;
						Anim[4]=0;
						score--;
					}
					else
					if(ball[i].z>-0.021)
					{
						showball[i]=false;
						if(i==0)ifblack[2]=true;
						ball[i].acceleration=0;
						Anim[2]=0;
						score--;
					}
					else
					ball[i].x = -1.532;ball[i].angle=360-ball[i].angle;
					
				}
				else
				if(ball[i].x >  1.532)
				{
					if(ball[i].z<-3.183 && ball[i].z>-3.217)
					{
						showball[i]=false;
						if(i==0)ifblack[0]=true;
						ball[i].acceleration=0;
						Anim[0]=0;
						score--;
					}
					else
					if(ball[i].z<-6.311)
					{
						showball[i]=false;
						if(i==0)ifblack[5]=true;
						ball[i].acceleration=0;
						Anim[5]=0;
						score--;
					}
					else
					if(ball[i].z>-0.021)
					{
						showball[i]=false;
						if(i==0)ifblack[1]=true;
						ball[i].acceleration=0;
						Anim[1]=0;
						score--;
					}
					else
					ball[i].x =  1.532;ball[i].angle=360-ball[i].angle;
				}
				while(ball[i].angle<0) ball[i].angle+=360;
				if(ball[i].angle>=360) ball[i].angle%=360;
			}
		/////постепенное уменьшение скорости
		for(int i=0 ; i<16 ; i++)
		{
			if(showball[i])
			if(ball[i].acceleration>0)
			{
				ball[i].acceleration-=0.001f;
			}
			else
			{
				ball[i].acceleration=0;
			}
		}
	}
	/////передача управления ЛКМ после остановки всех шаров на столе
	if(
		ball[0].acceleration==0 &&
		ball[1].acceleration==0 &&
		ball[2].acceleration==0 &&
		ball[3].acceleration==0 &&
		ball[4].acceleration==0 &&
		ball[5].acceleration==0 &&
		ball[6].acceleration==0 &&
		ball[7].acceleration==0 &&
		ball[8].acceleration==0 &&
		ball[9].acceleration==0 &&
		ball[10].acceleration==0 &&
		ball[11].acceleration==0 &&
		ball[12].acceleration==0 &&
		ball[13].acceleration==0 &&
		ball[14].acceleration==0 &&
		ball[15].acceleration==0
	  )
	{
		LKM=false;
	}
	
	
	Draw();
	}
		Sleep(10);
		SwapBuffers(hDC);
	}
}
