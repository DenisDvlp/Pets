#include <windows.h>
#include <iostream>
#include <cmath>
#include <chrono>
#include "Core.h"
#include "table2.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "glaux.h"
#include "Size.h"
#include "Utils.h"
#pragma comment (lib, "legacy_stdio_definitions.lib")
#pragma comment (lib, "glaux.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "opengl32.lib")
static HGLRC hRC;
static HDC hDC;
static Core core;


struct Ball1
{
  double x, z; //координаты
  int angle; //угол (направление)
  float acceleration; //начальное ускорение
};

static constexpr float animation[29][2] =
{
  0.004f,-1.932f,
  0.008f,-1.932f,
  0.012f,-1.932f,
  0.016f,-1.932f,
  0.020f,-1.932f,
  0.024f,-1.932f,
  0.028f,-1.932f,
  0.032f,-1.932f,
  0.036f,-1.932f,
  0.040f,-1.932f,
  0.044f,-1.932f,
  0.048f,-1.932f,
  0.052f,-1.932f,
  0.056f,-1.932f,
  0.058f,-1.933f,
  0.069f,-1.936f,
  0.080f,-1.941f,
  0.090f,-1.948f,
  0.098f,-1.956f,
  0.105f,-1.966f,
  0.110f,-1.978f,
  0.113f,-1.988f,
  0.114f,-2.000f,
  0.114f,-2.011f,
  0.114f,-2.023f,
  0.114f,-2.034f,
  0.114f,-2.045f,
  0.114f,-2.056f,
  0.114f,-2.068f
};
Ball1 ball[16];
POINT pos;
int wheel, selected, inc, Anim[6], score;
int RotateY, RotateX;//угол камеры
float x, z, Aa, Bb, xi, yi, xj, yj, force, scale; //координаты камеры
bool menu1, menu2, menu3, new1, cont, exit1, yes, no, menu11, menu22, menu33;
GLuint  texture[6];
bool ifcross[120], showball[16], overforce, ifblack[6], rkm, LKM, lkm, blw, bls, bla, bld;
Size screenSize;
Position screenCenter;

GLuint  base;
GLYPHMETRICSFLOAT gmf[256];
GLfloat LightDiffuse[] = { 0.8f, 0.8f, 0.8f, 0.0f };
GLfloat LightPosition[] = { 0.0f, 4.0f, -3.2f, 0.0f };
GLfloat LightDirection[] = { 0.0f, 0.0f, 0.0f, 0.0f };

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
GLvoid Draw();
void DefaultPosition();

GLsizei Width, Height;
GLUquadricObj* quadratic;

GLvoid BuildFont(GLvoid)
{
  HFONT  font;
  base = glGenLists(96);
  font = CreateFont(-200,        // Высота фонта
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
    FF_DONTCARE | DEFAULT_PITCH,  // Семейство и шаг
    TEXT("Times New Roman"));      // Имя шрифта

  SelectObject(hDC, font);
  wglUseFontOutlines(hDC,
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

GLvoid glPrint(const char* text)
{
  if (!text)
    return;
  glPushAttrib(GL_LIST_BIT);
  glListBase(base);
  glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
  glPopAttrib();
}

void DefaultPosition()
{
  for (int i = 0; i < 6; i++)
  {
    Anim[i] = 30;
    ifblack[i] = false;
  }
  for (int i = 0; i < 16; i++)
  {
    ball[i].acceleration = 0;
    showball[i] = true;
  }
  ball[0].x = 0.0f;
  ball[0].z = -1.6f;

  ball[1].x = 0.0f;
  ball[1].z = -4.8f;

  ball[2].x = -0.069f;
  ball[2].z = -4.919f;
  ball[3].x = 0.069f;
  ball[3].z = -4.919f;

  ball[4].x = -0.137f;
  ball[4].z = -5.038f;
  ball[5].x = 0.0f;
  ball[5].z = -5.038f;
  ball[6].x = 0.137f;
  ball[6].z = -5.038f;

  ball[7].x = -0.206f;
  ball[7].z = -5.156f;
  ball[8].x = -0.069f;
  ball[8].z = -5.156f;
  ball[9].x = 0.069f;
  ball[9].z = -5.156f;
  ball[10].x = 0.206f;
  ball[10].z = -5.156f;

  ball[11].x = -0.274f;
  ball[11].z = -5.275f;
  ball[12].x = -0.137f;
  ball[12].z = -5.275f;
  ball[13].x = 0.0f;
  ball[13].z = -5.275f;
  ball[14].x = 0.137f;
  ball[14].z = -5.275f;
  ball[15].x = 0.274f;
  ball[15].z = -5.275f;

  selected = 0;
  x = -ball[0].x;
  z = -ball[0].z;
  RotateY = 0;
  RotateX = 0;
}

inline GLvoid BallPosition(GLfloat x, GLfloat z)
{
  glTranslatef(x, -1.932f, z);
  gluSphere(quadratic, 0.068f, 24, 24);
  glTranslatef(0, -0.0678f, 0);
  glRotatef(90, 1, 0, 0);
  glColor3f(0.3f, 0.6f, 0.3f);
  gluDisk(quadratic, 0.0f, 0.055f, 16, 16);
}

inline GLvoid Animation(int N)
{
  if (N == 0)
  {
    glTranslatef(1.532f, 0, -3.2f);
  }
  if (N == 1)
  {
    glTranslatef(1.532f, 0, -0.068f);
    glRotatef(315, 0, 1, 0);
  }
  if (N == 2)
  {
    glTranslatef(-1.532f, 0, -0.068f);
    glRotatef(225, 0, 1, 0);
  }
  if (N == 3)
  {
    glTranslatef(-1.532f, 0, -3.2f);
    glRotatef(180, 0, 1, 0);
  }
  if (N == 4)
  {
    glTranslatef(-1.532f, 0, -6.332f);
    glRotatef(135, 0, 1, 0);
  }
  if (N == 5)
  {
    glTranslatef(1.532f, 0, -6.332f);
    glRotatef(45, 0, 1, 0);
  }
  glTranslatef(animation[Anim[N]][0], animation[Anim[N]][1], 0);
  gluSphere(quadratic, 0.068f, 16, 16);
  glTranslatef(0, -0.0678f, 0);
  glRotatef(90, 1, 0, 0);
  glColor3f(0.3f, 0.6f, 0.3f);
  gluDisk(quadratic, 0.0f, 0.055f, 16, 16);
  Anim[N]++;
}

inline GLvoid CameraPosition(float x, float z)
{
  glLoadIdentity();
  glTranslatef(0, 0 + scale * 0.3f, -2.8f + scale);
  glRotatef(RotateX, 1, 0, 0);
  glRotatef(RotateY, 0, 1, 0);
  glTranslatef(x, 0.8f, z);
}

GLvoid Initial()
{
  AUX_RGBImageRec* texture1;
  glGenTextures(5, &texture[0]);

  texture1 = auxDIBImageLoad(TEXT("table/sukno.bbp"));
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

  texture1 = auxDIBImageLoad(TEXT("table/bort.bbp"));
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

  texture1 = auxDIBImageLoad(TEXT("table/nogi.bbp"));
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

  texture1 = auxDIBImageLoad(TEXT("table/pol.bbp"));
  glBindTexture(GL_TEXTURE_2D, texture[3]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

  texture1 = auxDIBImageLoad(TEXT("table/stena.bbp"));
  glBindTexture(GL_TEXTURE_2D, texture[4]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

  texture1 = auxDIBImageLoad(TEXT("table/menu.bbp"));
  glBindTexture(GL_TEXTURE_2D, texture[5]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

  quadratic = gluNewQuadric();
  gluQuadricNormals(quadratic, GLU_SMOOTH);
  gluQuadricTexture(quadratic, GL_TRUE);

  glEnable(GL_LIGHTING);

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_COLOR_MATERIAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  BuildFont();
}

GLvoid Resize(GLsizei Width, GLsizei Height)
{
  if (Height == 0)
    Height = 1;
  glViewport(0, 0, Width, Height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(65.0f, (GLfloat)Width / (GLfloat)Height, 0.01f, 100.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
GLvoid DrawMenu1()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  LightPosition[0] = 0.0f;
  LightPosition[1] = 0.0f;
  LightPosition[2] = -4.0f;
  LightPosition[3] = 0.0f;
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection);
  glEnable(GL_LIGHT1);

  glLoadIdentity();
  LightPosition[0] = 0.0f;
  LightPosition[1] = 0.0f;
  LightPosition[2] = 1.0f;
  LightPosition[3] = 1.0f;
  glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT2, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, LightDirection);
  glEnable(GL_LIGHT2);

  glLoadIdentity();
  glColor3f(1.0f, 0.0f, 0.0f);
  if (!new1)
  {
    glTranslatef(-2.3f, 0.0f, -2.95f); glColor3f(0.9f, 0.65f, 0.0f);
  }
  else
    glTranslatef(-2.3f, 0.0f, -2.7f);
  glPrint("новая игра");

  glLoadIdentity();
  glColor3f(1.0f, 0.0f, 0.0f);
  if (!exit1)
  {
    glTranslatef(-1.3f, -0.8f, -2.95f); glColor3f(0.9f, 0.65f, 0.0f);
  }
  else
    glTranslatef(-1.3f, -0.8f, -2.7f);
  glPrint("выход");

  glLoadIdentity();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(0.0f, 0.5f, -6.4f);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[5]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f); m();
  glTexCoord2f(1.0f, 1.0f); l();
  glTexCoord2f(1.0f, 0.0f); L();
  glTexCoord2f(0.0f, 0.0f); M();
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

GLvoid DrawMenu2()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  LightPosition[0] = 0.0f;
  LightPosition[1] = 0.0f;
  LightPosition[2] = -4.0f;
  LightPosition[3] = 0.0f;
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection);
  glEnable(GL_LIGHT1);

  glLoadIdentity();
  LightPosition[0] = 0.0f;
  LightPosition[1] = 0.0f;
  LightPosition[2] = 1.0f;
  LightPosition[3] = 1.0f;
  glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT2, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, LightDirection);
  glEnable(GL_LIGHT2);

  glLoadIdentity();
  glColor3f(1.0f, 0.0f, 0.0f);
  if (!cont)
  {
    glTranslatef(-2.5f, 0.8f, -2.95f); glColor3f(0.9f, 0.65f, 0.0f);
  }
  else
    glTranslatef(-2.5f, 0.8f, -2.7f);
  glPrint("продолжить");

  glLoadIdentity();
  glColor3f(1.0f, 0.0f, 0.0f);
  if (!new1)
  {
    glTranslatef(-2.3f, 0.0f, -2.95f); glColor3f(0.9f, 0.65f, 0.0f);
  }
  else
    glTranslatef(-2.3f, 0.0f, -2.7f);
  glPrint("новая игра");

  glLoadIdentity();
  glColor3f(1.0f, 0.0f, 0.0f);
  if (!exit1)
  {
    glTranslatef(-1.3f, -0.8f, -2.95f); glColor3f(0.9f, 0.65f, 0.0f);
  }
  else
    glTranslatef(-1.3f, -0.8f, -2.7f);
  glPrint("выход");

  glLoadIdentity();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(0.0f, 0.5f, -6.4f);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[5]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f); m();
  glTexCoord2f(1.0f, 1.0f); l();
  glTexCoord2f(1.0f, 0.0f); L();
  glTexCoord2f(0.0f, 0.0f); M();
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

GLvoid DrawMenu3()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  LightPosition[0] = 0.0f;
  LightPosition[1] = 0.0f;
  LightPosition[2] = 0.0f;
  LightPosition[3] = 0.0f;
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection);
  glEnable(GL_LIGHT1);

  glLoadIdentity();
  LightPosition[0] = 0.0f;
  LightPosition[1] = 0.0f;
  LightPosition[2] = 1.0f;
  LightPosition[3] = 1.0f;
  glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT2, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, LightDirection);
  glEnable(GL_LIGHT2);

  glLoadIdentity();
  glColor3f(0.9f, 0.65f, 0.0f);
  glTranslatef(-1.6f, 0.8f, -2.95f);
  glPrint("Уверен?");

  glLoadIdentity();
  glColor3f(1.0f, 0.0f, 0.0f);
  if (!no)
  {
    glTranslatef(-0.6f, -0.8f, -2.95f); glColor3f(0.9f, 0.65f, 0.0f);
  }
  else
    glTranslatef(-0.6f, -0.8f, -2.7f);
  glPrint("нет");

  glLoadIdentity();
  glColor3f(1.0f, 0.0f, 0.0f);
  if (!yes)
  {
    glTranslatef(-0.4f, 0.0f, -2.95f); glColor3f(0.9f, 0.65f, 0.0f);
  }
  else
    glTranslatef(-0.4f, 0.0f, -2.7f);
  glPrint("да");

  glLoadIdentity();
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(0.0f, 0.5f, -6.4f);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[5]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f); m();
  glTexCoord2f(1.0f, 1.0f); l();
  glTexCoord2f(1.0f, 0.0f); L();
  glTexCoord2f(0.0f, 0.0f); M();
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

GLvoid Draw()
{
  core.draw();
  return;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glDisable(GL_LIGHT2);
  CameraPosition(x, z);
  glTranslatef(0, -0.5, 6.8);
  LightPosition[0] = 0.0f;
  LightPosition[1] = 1.0f;
  if (RotateX < 375)
    LightPosition[2] = -4.2f;
  else
    LightPosition[2] = -2.5f;
  LightPosition[3] = 0.3f;
  //glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);//отсвечивание
  glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);//положение
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection);//направление
  glEnable(GL_LIGHT1);

  ////////индикатор силы/////
  glLoadIdentity();
  glEnable(GL_LIGHT2);
  glTranslatef(0, 0, -0.3);
  glBegin(GL_QUADS);
  glColor3f(force, 1 - force, 0.0f);

  glVertex3f(0.17f, -0.15f + force * 0.16, 0.0f);
  glVertex3f(0.20f, -0.15f + force * 0.16, 0.0f);

  glColor3f(0.0f, 1.0f, 0.0f);

  glVertex3f(0.20f, -0.15f, 0.0f);
  glVertex3f(0.17f, -0.15f, 0.0f);

  glEnd();
  ////кий//////
  CameraPosition(x, z);
  glTranslatef(0 - x, -1.932, 0 - z);
  glRotatef(-RotateY, 0, 1, 0);
  glRotatef(347, 1, 0, 0);
  glTranslatef(0, 0, 0.068 + force * 0.6);
  glColor3f(0.737f, 0.353f, 0.094f);
  gluCylinder(quadratic, 0.015f, 0.03f, 3.5, 16, 16);
  glDisable(GL_LIGHT2);
  /////////лампы/////////
  if (RotateX < 375)
  {
    CameraPosition(x, z);
    //крепление

    glTranslatef(0, 0.5, -0.75);
    glRotatef(180, 1, 0, 0);
    glColor3f(0.7f, 0.3f, 0.5f);
    gluCylinder(quadratic, 0.03f, 0.03f, 4.9, 4, 4);
    glRotatef(180, 1, 0, 0);

    //светильники

    glRotatef(90, 1, 0, 0);

    glTranslatef(0, -4.7f, 0);
    glColor3f(0.3f, 0.7f, 0.5f);
    gluCylinder(quadratic, 0.2f, 0.7f, 0.6f, 16, 16);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluCylinder(quadratic, 0.19f, 0.69f, 0.6f, 16, 16);

    glTranslatef(0, 1.5, 0);
    glColor3f(0.3f, 0.7f, 0.5f);
    gluCylinder(quadratic, 0.2f, 0.7f, 0.6f, 16, 16);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluCylinder(quadratic, 0.19f, 0.69f, 0.6f, 16, 16);

    glTranslatef(0, 1.5, 0);
    glColor3f(0.3f, 0.7f, 0.5f);
    gluCylinder(quadratic, 0.2f, 0.7f, 0.6f, 16, 16);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluCylinder(quadratic, 0.19f, 0.69f, 0.6f, 16, 16);

    glTranslatef(0, 1.5, 0);
    glColor3f(0.3f, 0.7f, 0.5f);
    gluCylinder(quadratic, 0.2f, 0.7f, 0.6f, 16, 16);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluCylinder(quadratic, 0.19f, 0.69f, 0.6f, 16, 16);
  }
  ///////////стол///////////
  CameraPosition(x, z);
  glColor3f(1.0f, 1.0f, 1.0f);
  Table2(texture, quadratic);


  if (Anim[0] < 29)
  {
    CameraPosition(x, z);
    if (ifblack[0])
      glColor3f(0.5f, 0.3f, 0.3f);
    else
      glColor3f(1.0f, 1.0f, 1.0f);
    Animation(0);
  }
  else
    ifblack[0] = false;
  if (Anim[1] < 29)
  {
    CameraPosition(x, z);
    if (ifblack[1])
      glColor3f(0.5f, 0.3f, 0.3f);
    else
      glColor3f(1.0f, 1.0f, 1.0f);
    Animation(1);
  }
  else
    ifblack[1] = false;
  if (Anim[2] < 29)
  {
    CameraPosition(x, z);
    if (ifblack[2])
      glColor3f(0.5f, 0.3f, 0.3f);
    else
      glColor3f(1.0f, 1.0f, 1.0f);
    Animation(2);
  }
  else
    ifblack[2] = false;
  if (Anim[3] < 29)
  {
    CameraPosition(x, z);
    if (ifblack[3])
      glColor3f(0.5f, 0.3f, 0.3f);
    else
      glColor3f(1.0f, 1.0f, 1.0f);
    Animation(3);
  }
  else
    ifblack[3] = false;
  if (Anim[4] < 29)
  {
    CameraPosition(x, z);
    if (ifblack[4])
      glColor3f(0.5f, 0.3f, 0.3f);
    else
      glColor3f(1.0f, 1.0f, 1.0f);
    Animation(4);
  }
  else
    ifblack[4] = false;
  if (Anim[5] < 29)
  {
    CameraPosition(x, z);
    if (ifblack[5])
      glColor3f(0.5f, 0.3f, 0.3f);
    else
      glColor3f(1.0f, 1.0f, 1.0f);
    Animation(5);
  }
  else
    ifblack[5] = false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  GLuint PixelFormat;
  static PIXELFORMATDESCRIPTOR pfd =
  {
    sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW |    // format must support Window
      PFD_SUPPORT_OPENGL |    // format must support OpenGL
      PFD_DOUBLEBUFFER,       // must support double buffer
      PFD_TYPE_RGBA,          // требуется RGBA формат
      32,                     // 32Bit color depth
      0, 0, 0, 0, 0, 0,       // Color bits ignored ?
      0,                      // No Alpha buffer
      0,                      // shift bit ignored
      0,                      // no accumulation buffer
      0, 0, 0, 0,             // accumulation buffer bits ignored
      32,                     // 32bit z-buffer (depth buffer)
      0,                      // no stencil buffer
      0,                      // no auxiliary buffer
      PFD_MAIN_PLANE,         // main drawing layer
      0,                      // reserved
      0, 0, 0                 // layer mask ignored
  };
  switch (msg)
  {
  case WM_CREATE:
    menu1 = true;
    new1 = true;
    RotateY = 0;
    RotateX = 360;
    score = 16;
    selected = 0;
    hDC = GetDC(hWnd);
    PixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, PixelFormat, &pfd);
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);
    core.init();
    screenSize.width = GetSystemMetrics(SM_CXSCREEN);
    screenSize.height = GetSystemMetrics(SM_CYSCREEN);
    screenCenter.x() = screenSize.width / 2;
    screenCenter.y() = screenSize.height / 2;
    Initial();
    break;
  case WM_DESTROY:
    ChangeDisplaySettings(NULL, 0);
    wglMakeCurrent(hDC, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
    KillFont();
    PostQuitMessage(0);
    break;

  case WM_KEYDOWN: {
    switch (wParam)
    {
    case VK_ESCAPE:
    {
      if (!menu1 && !menu2 && !menu3)
      {
        menu3 = false;
        menu2 = true;
        menu1 = false;
        cont = true;
        new1 = false;
        exit1 = false;
        break;
      }
      if (menu1)
      {
        menu3 = true;
        menu2 = false;
        menu1 = false;
        menu11 = true;
        yes = true;
        no = false;
        break;
      }
      if (menu2)
      {
        menu3 = false;
        menu2 = false;
        menu1 = false;
        break;
      }
      break;
    }
    case 0x44:  //D  
    { bld = true; break; }
    case 0x41:  //A
    { bla = true; break; }
    case 0x57:  //W
    { blw = true; break; }
    case 0x53:  //S
    { bls = true; break; }
    case VK_RETURN:
    {
      if (menu1 || menu2 || menu3)
      {
        if (menu1)
          if (new1)
          {
            menu1 = false;
            menu2 = false;
            menu3 = false;
            menu22 = false;
            menu11 = false;
            menu33 = false;
            break;
          }
          else
          {
            menu11 = true;
            menu1 = false;
            menu2 = false;
            menu3 = true;
            yes = true;
            no = false;
            break;
          }
        if (menu2)
          if (cont)
          {
            menu1 = false;
            menu2 = false;
            menu3 = false;
            menu22 = false;
            menu11 = false;
            menu33 = false; break;
          }
          else
          {
            if (new1)
            {
              menu1 = false;
              menu2 = false;
              menu3 = true;
              menu22 = true;
              yes = true;
              no = false;
              break;
            }
            else
            {
              menu1 = false;
              menu2 = false;
              menu3 = true;
              menu33 = true;
              yes = true;
              no = false;
              break;
            }
          }
        if (menu3)
        {
          if (menu11)
            if (yes)
            {
              ChangeDisplaySettings(NULL, 0);
              wglMakeCurrent(hDC, NULL);
              wglDeleteContext(hRC);
              ReleaseDC(hWnd, hDC);
              KillFont();
              PostQuitMessage(0); break;
            }
            else
            {
              menu1 = true;
              menu2 = false;
              menu3 = false;
              menu11 = false;
              new1 = true;
              exit1 = false;
              break;
            }
          if (menu22)
            if (yes)
            {
              menu1 = false;
              menu2 = false;
              menu3 = false;
              menu22 = false;
              menu11 = false;
              menu33 = false;
              break;
            }
            else
            {
              menu1 = false;
              menu2 = true;
              menu3 = false;
              menu22 = false;
              cont = true;
              new1 = false;
              exit1 = false;
              break;
            }
          if (menu33)
            if (yes)
            {
              ChangeDisplaySettings(NULL, 0);
              wglMakeCurrent(hDC, NULL);
              wglDeleteContext(hRC);
              ReleaseDC(hWnd, hDC);
              KillFont();
              PostQuitMessage(0); break;
            }
            else
            {
              menu1 = false;
              menu2 = true;
              menu3 = false;
              menu33 = false;
              cont = true;
              new1 = false;
              exit1 = false;
              break;
            }
        }
      }
      break;
    }
    case VK_UP:
    {
      if (menu1)
        if (new1)
        {
          exit1 = true;
          new1 = false;
        }
        else
        {
          exit1 = false;
          new1 = true;
        }
      if (menu2)
        if (cont)
        {
          exit1 = true;
          new1 = false;
          cont = false;
        }
        else
        {
          if (new1)
          {
            exit1 = false;
            cont = true;
            new1 = false;
          }
          else
          {
            exit1 = false;
            cont = false;
            new1 = true;
          }
        }
      if (menu3)
        if (yes)
        {
          no = true;
          yes = false;
        }
        else
        {
          no = false;
          yes = true;
        }
      break;
    }
    case VK_DOWN:
    {
      if (menu1)
        if (new1)
        {
          exit1 = true;
          new1 = false;
        }
        else
        {
          exit1 = false;
          new1 = true;
        }
      if (menu2)
        if (cont)
        {
          exit1 = false;
          new1 = true;
          cont = false;
        }
        else
        {
          if (new1)
          {
            exit1 = true;
            cont = false;
            new1 = false;
          }
          else
          {
            exit1 = false;
            cont = true;
            new1 = false;
          }
        }
      if (menu3)
        if (yes)
        {
          no = true;
          yes = false;
        }
        else
        {
          no = false;
          yes = true;
        }
      break;
    }
    }
  }
                 break;
  case WM_KEYUP:
  {
    switch (wParam)
    {
    case 0x57:
      blw = false;
      break;
    case 0x53:
      bls = false;
      break;
    case 0x41:
      bla = false;
      break;
    case 0x44:
      bld = false;
      break;
    }
    break;
  }
  case WM_MOUSEMOVE:
  {
    static constexpr float mouseSensivity = 0.25f;
    POINT cursor;
    GetCursorPos(&cursor);
    Position angle = core.cameraAngle();
    angle.x() += (cursor.y - screenCenter.y()) * mouseSensivity;
    angle.y() += (cursor.x - screenCenter.x()) * mouseSensivity;
    SetCursorPos(screenCenter.x(), screenCenter.y());

    if (rkm)
    {
    }
    else
    {
      core.cameraRotate(angle.x(), angle.y());
    }
    break;
  }
  case WM_MOUSEWHEEL:
  {
    if (score)
    {
      wheel = HIWORD(wParam);
      if (wheel < 65000) // wheel up
      {
        core.nextBall();
      }
      else  // wheel down
      {
        core.prevBall();
      }
    }
    break;
  }
  case WM_RBUTTONDOWN:
  { rkm = true; break; }
  case WM_RBUTTONUP:
  { rkm = false; break; }
  case WM_LBUTTONDOWN:
  {
    if (showball[selected])
      if (!LKM)
      {
        if (!lkm)force = 0;
        lkm = true;
      }
    break;
  }
  case WM_LBUTTONUP:
  {
    if (score)
    {
      if (showball[selected])
        if (!LKM)
        {
          LKM = true;
          lkm = false;
          core.ballPull(force);
          force = 0;
        }
    }
    break;
  }
  case WM_SIZE:
  {
    screenSize = { LOWORD(lParam), HIWORD(lParam) };
    core.sceneResize(screenSize.width, screenSize.height);
    break;
  }
  default:return(DefWindowProc(hWnd, msg, wParam, lParam));
  }
  return 0;
}

using namespace std;
int WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, int nShowCmd)
{
  float length = 0.08f, movement = 0.03f, grad = pi / 180, agrad = 180 / pi;
  int gamai, gamaj, beta, perfom = 0;

  MSG      msg;
  WNDCLASS  wc;
  HWND    hWnd;

  auto className = TEXT("Billiard_Petrov");

  wc.style = 0;
  wc.lpfnWndProc = (WNDPROC)WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInst;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = className;

  RegisterClass(&wc);
  hWnd = CreateWindow(
    className,
    TEXT("Billiard by D. Petrov 2022"),
    WS_DLGFRAME | WS_MAXIMIZE | WS_VISIBLE,
    0, 0, 0, 0,
    NULL, NULL, hInst, NULL);

#ifdef _DEBUG
  ShowCursor(true);
#else
  ShowCursor(false);
#endif

  while (true)
  {
    while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
    {
      if (GetMessage(&msg, NULL, 0, 0))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
      else
      {
        return TRUE;
      }
    }

    /*if (menu1)
      DrawMenu1();
    else if (menu2)
      DrawMenu2();
    else if (menu3)
      DrawMenu3();
    else*/
    {
      ///вычисления///
      if (blw) {
        core.cameraMoveForward();
      }
      if (bls) {
        core.cameraMoveBackward();
      }
      if (bla) {
        core.cameraMoveLeft();
      }
      if (bld) {
        core.cameraMoveRight();
      }
      if (lkm)
      {

        if (!overforce)
        {
          force += 0.01;
          if (force >= 1)
            overforce = true;
        }
        if (overforce)
        {
          force -= 0.01;
          if (force <= 0)
            overforce = false;
        }
      }
      if (LKM)
      {
        if (showball[0]) {
          ball[0].x -= length * Sin(ball[0].angle * grad) * ball[0].acceleration;
          ball[0].z -= length * Cos(ball[0].angle * grad) * ball[0].acceleration;
        }
        if (showball[1]) {
          ball[1].x -= length * Sin(ball[1].angle * grad) * ball[1].acceleration;
          ball[1].z -= length * Cos(ball[1].angle * grad) * ball[1].acceleration;
        }
        if (showball[2]) {
          ball[2].x -= length * Sin(ball[2].angle * grad) * ball[2].acceleration;
          ball[2].z -= length * Cos(ball[2].angle * grad) * ball[2].acceleration;
        }
        if (showball[3]) {
          ball[3].x -= length * Sin(ball[3].angle * grad) * ball[3].acceleration;
          ball[3].z -= length * Cos(ball[3].angle * grad) * ball[3].acceleration;
        }
        if (showball[4]) {
          ball[4].x -= length * Sin(ball[4].angle * grad) * ball[4].acceleration;
          ball[4].z -= length * Cos(ball[4].angle * grad) * ball[4].acceleration;
        }
        if (showball[5]) {
          ball[5].x -= length * Sin(ball[5].angle * grad) * ball[5].acceleration;
          ball[5].z -= length * Cos(ball[5].angle * grad) * ball[5].acceleration;
        }
        if (showball[6]) {
          ball[6].x -= length * Sin(ball[6].angle * grad) * ball[6].acceleration;
          ball[6].z -= length * Cos(ball[6].angle * grad) * ball[6].acceleration;
        }
        if (showball[7]) {
          ball[7].x -= length * Sin(ball[7].angle * grad) * ball[7].acceleration;
          ball[7].z -= length * Cos(ball[7].angle * grad) * ball[7].acceleration;
        }
        if (showball[8]) {
          ball[8].x -= length * Sin(ball[8].angle * grad) * ball[8].acceleration;
          ball[8].z -= length * Cos(ball[8].angle * grad) * ball[8].acceleration;
        }
        if (showball[9]) {
          ball[9].x -= length * Sin(ball[9].angle * grad) * ball[9].acceleration;
          ball[9].z -= length * Cos(ball[9].angle * grad) * ball[9].acceleration;
        }
        if (showball[10]) {
          ball[10].x -= length * Sin(ball[10].angle * grad) * ball[10].acceleration;
          ball[10].z -= length * Cos(ball[10].angle * grad) * ball[10].acceleration;
        }
        if (showball[11]) {
          ball[11].x -= length * Sin(ball[11].angle * grad) * ball[11].acceleration;
          ball[11].z -= length * Cos(ball[11].angle * grad) * ball[11].acceleration;
        }
        if (showball[12]) {
          ball[12].x -= length * Sin(ball[12].angle * grad) * ball[12].acceleration;
          ball[12].z -= length * Cos(ball[12].angle * grad) * ball[12].acceleration;
        }
        if (showball[13]) {
          ball[13].x -= length * Sin(ball[13].angle * grad) * ball[13].acceleration;
          ball[13].z -= length * Cos(ball[13].angle * grad) * ball[13].acceleration;
        }
        if (showball[14]) {
          ball[14].x -= length * Sin(ball[14].angle * grad) * ball[14].acceleration;
          ball[14].z -= length * Cos(ball[14].angle * grad) * ball[14].acceleration;
        }
        if (showball[15]) {
          ball[15].x -= length * Sin(ball[15].angle * grad) * ball[15].acceleration;
          ball[15].z -= length * Cos(ball[15].angle * grad) * ball[15].acceleration;
        }
        /////рассчет углов и ускорений при столкновении шара с шаром  
        inc = 0;
        for (int i = 0; i < 15; i++)
        {
          if (showball[i])
            for (int j = i + 1; j < 16; j++)
            {
              if (showball[j])
                if (pow((ball[i].x - ball[j].x), 2) + pow((ball[i].z - ball[j].z), 2) < 0.018496)
                {
                  if (!ifcross[inc])
                    if (ball[j].z < ball[i].z)
                      /*1, 2*/ {
                      beta = asin((ball[j].x - ball[i].x) / sqrt(pow((ball[j].x - ball[i].x), 2) + pow((ball[j].z - ball[i].z), 2))) * agrad;
                      gamai = (360 - ball[i].angle - beta + 360) % 360;
                      gamaj = (360 - ball[j].angle - beta + 360) % 360;

                      Aa = ball[i].acceleration * Cos(gamai * grad);
                      Bb = -ball[j].acceleration * Cos(gamaj * grad);
                      ////////////////////
                      if (Aa < 0.0f)
                      {
                        xi = Aa - Bb;
                        yi = ball[i].acceleration * Sin(gamai * grad);
                      }
                      else
                      {
                        xi = -((ball[i].acceleration - Aa) * Cos(gamai * grad) + Bb);
                        yi = (ball[i].acceleration - Aa) * Sin(gamai * grad);
                      }

                      ball[i].acceleration = sqrt(xi * xi + yi * yi);
                      if (yi < 0.0f)
                        ball[i].angle = float(acos(xi / (ball[i].acceleration + 0.0000001)) * agrad - beta);
                      else
                        ball[i].angle = float(360 - acos(xi / (ball[i].acceleration + 0.0000001)) * agrad - beta);
                      ///////////////////
                      if (Bb < 0.0f)
                      {
                        xj = Aa - Bb;
                        yj = ball[j].acceleration * Sin(gamaj * grad);
                      }
                      else
                      {
                        xj = Aa - (ball[j].acceleration - Bb) * Cos(gamaj * grad);
                        yj = (ball[j].acceleration - Bb) * Sin(gamaj * grad);
                      }

                      ball[j].acceleration = sqrt(xj * xj + yj * yj);
                      if (yj < 0.0f)
                        ball[j].angle = float(acos(xj / (ball[j].acceleration + 0.0000001)) * agrad - beta);
                      else
                        ball[j].angle = float(360 - acos(xj / (ball[j].acceleration + 0.0000001)) * agrad - beta);
                      ///////////////////
                    }
                    else
                      /*3, 4*/ {
                      beta = asin((ball[i].x - ball[j].x) / sqrt(pow((ball[j].x - ball[i].x), 2) + pow((ball[j].z - ball[i].z), 2))) * agrad;
                      gamai = (360 - ball[i].angle - beta + 360) % 360;
                      gamaj = (360 - ball[j].angle - beta + 360) % 360;

                      Bb = -ball[i].acceleration * Cos(gamai * grad);
                      Aa = ball[j].acceleration * Cos(gamaj * grad);
                      //////////////////
                      if (Aa < 0.0f)
                      {
                        xj = Aa - Bb;
                        yj = ball[j].acceleration * Sin(gamaj * grad);
                      }
                      else
                      {
                        xj = -((ball[j].acceleration - Aa) * Cos(gamaj * grad) + Bb);
                        yj = (ball[j].acceleration - Aa) * Sin(gamaj * grad);
                      }

                      ball[j].acceleration = sqrt(xj * xj + yj * yj);
                      if (yj < 0.0f)
                        ball[j].angle = float(acos(xj / (ball[j].acceleration + 0.0000001)) * agrad - beta);
                      else
                        ball[j].angle = float(360 - acos(xj / (ball[j].acceleration + 0.0000001)) * agrad - beta);
                      /////////////////
                      if (Bb < 0.0f)
                      {
                        xi = Aa - Bb;
                        yi = ball[i].acceleration * Sin(gamai * grad);
                      }
                      else
                      {
                        xi = Aa - (ball[i].acceleration - Bb) * Cos(gamai * grad);
                        yi = (ball[i].acceleration - Bb) * Sin(gamai * grad);
                      }

                      ball[i].acceleration = sqrt(xi * xi + yi * yi);
                      if (yi < 0.0f)
                        ball[i].angle = float(acos(xi / (ball[i].acceleration + 0.0000001)) * agrad - beta);
                      else
                        ball[i].angle = float(360 - acos(xi / (ball[i].acceleration + 0.0000001)) * agrad - beta);
                      ////////////////
                    }
                  ifcross[inc] = true;
                  for (j = j + 1; j < 16; j++)
                  {
                    inc++;
                    ifcross[inc] = false;
                  }
                  //break;
                }
                else
                {
                  ifcross[inc] = false;
                  inc++;
                }
            }
          else
            for (int j = i + 1; j < 16; j++)
            {
              inc++;
              ifcross[inc] = false;
            }
        }
        /////столкновение с бортами
        for (int i = 0; i < 16; i++)
        {
          if (!showball[i])continue;

          if (ball[i].z < -6.332)
          {
            if (ball[i].x < -1.511)
            {
              showball[i] = false;
              if (i == 0)ifblack[4] = true;
              ball[i].acceleration = 0;
              Anim[4] = 0;
              score--;
            }
            else
              if (ball[i].x > 1.511)
              {
                showball[i] = false;
                if (i == 0)ifblack[5] = true;
                ball[i].acceleration = 0;
                Anim[5] = 0;
                score--;;
              }
              else
                ball[i].z = -6.332; ball[i].angle = 540 - ball[i].angle;
          }
          else
            if (ball[i].z > -0.068)
            {
              if (ball[i].x < -1.511)
              {
                showball[i] = false;
                if (i == 0)ifblack[2] = true;
                ball[i].acceleration = 0;
                Anim[2] = 0;
                score--;
              }
              else
                if (ball[i].x > 1.511)
                {
                  showball[i] = false;
                  if (i == 0)ifblack[1] = true;
                  ball[i].acceleration = 0;
                  Anim[1] = 0;
                  score--;
                }
                else
                  ball[i].z = -0.068; ball[i].angle = 540 - ball[i].angle;
            }
            else
              if (ball[i].x < -1.532)
              {
                if (ball[i].z<-3.183 && ball[i].z>-3.217)
                {
                  showball[i] = false;
                  if (i == 0)ifblack[3] = true;
                  ball[i].acceleration = 0;
                  Anim[3] = 0;
                  score--;
                }
                else
                  if (ball[i].z < -6.311)
                  {
                    showball[i] = false;
                    if (i == 0)ifblack[4] = true;
                    ball[i].acceleration = 0;
                    Anim[4] = 0;
                    score--;
                  }
                  else
                    if (ball[i].z > -0.021)
                    {
                      showball[i] = false;
                      if (i == 0)ifblack[2] = true;
                      ball[i].acceleration = 0;
                      Anim[2] = 0;
                      score--;
                    }
                    else
                      ball[i].x = -1.532; ball[i].angle = 360 - ball[i].angle;

              }
              else
                if (ball[i].x > 1.532)
                {
                  if (ball[i].z<-3.183 && ball[i].z>-3.217)
                  {
                    showball[i] = false;
                    if (i == 0)ifblack[0] = true;
                    ball[i].acceleration = 0;
                    Anim[0] = 0;
                    score--;
                  }
                  else
                    if (ball[i].z < -6.311)
                    {
                      showball[i] = false;
                      if (i == 0)ifblack[5] = true;
                      ball[i].acceleration = 0;
                      Anim[5] = 0;
                      score--;
                    }
                    else
                      if (ball[i].z > -0.021)
                      {
                        showball[i] = false;
                        if (i == 0)ifblack[1] = true;
                        ball[i].acceleration = 0;
                        Anim[1] = 0;
                        score--;
                      }
                      else
                        ball[i].x = 1.532; ball[i].angle = 360 - ball[i].angle;
                }
          while (ball[i].angle < 0) ball[i].angle += 360;
          if (ball[i].angle >= 360) ball[i].angle %= 360;
        }
        /////постепенное уменьшение скорости
        for (int i = 0; i < 16; i++)
        {
          if (showball[i])
            if (ball[i].acceleration > 0)
            {
              ball[i].acceleration -= 0.001f;
            }
            else
            {
              ball[i].acceleration = 0;
            }
        }
      }
      /////передача управления ЛКМ после остановки всех шаров на столе
      if (
        ball[0].acceleration == 0 &&
        ball[1].acceleration == 0 &&
        ball[2].acceleration == 0 &&
        ball[3].acceleration == 0 &&
        ball[4].acceleration == 0 &&
        ball[5].acceleration == 0 &&
        ball[6].acceleration == 0 &&
        ball[7].acceleration == 0 &&
        ball[8].acceleration == 0 &&
        ball[9].acceleration == 0 &&
        ball[10].acceleration == 0 &&
        ball[11].acceleration == 0 &&
        ball[12].acceleration == 0 &&
        ball[13].acceleration == 0 &&
        ball[14].acceleration == 0 &&
        ball[15].acceleration == 0
        )
      {
        LKM = false;
      }


      core.update();
      core.draw();
    }
    //Sleep(10);
    SwapBuffers(hDC);
  }
}
