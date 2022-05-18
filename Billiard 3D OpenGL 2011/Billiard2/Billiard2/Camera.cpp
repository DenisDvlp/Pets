#include "Camera.h"
#include "Utils.h"
#include <cmath>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

void Camera::setBall(const Ball& ball)
{
  pos = ball.position();
}

void Camera::move(int direction1, int direction2, float(*trig1)(float), float(*trig2)(float))
{
  const float radian = degToRad(angle.y);
  pos.x += direction1 * speed * trig1(radian);
  pos.y += direction2 * speed * trig2(radian);
  adjustInRange<float>(-5, pos.x, 5);
  adjustInRange<float>(-10.0f, pos.y, 10.0f);
}

void Camera::moveForward()
{
  move(-1, 1, sin, cos);
}

void Camera::moveBackward()
{
  move(1, -1, sin, cos);
}

void Camera::moveLeft()
{
  move(1, 1, cos, sin);
}

void Camera::moveRight()
{
  move(-1, -1, cos, sin);
}

void Camera::rotate(float angleX, float angleY)
{
  adjustInRange<float>(-30, angleX, 90);
  adjustInLoop<float>(0, angleY, 360);
  angle = { angleX, angleY, angle.z };
}

void Camera::resize(size_t width, size_t height)
{
  size = { width, height };
  glViewport(0, 0, width, height);
}

Camera::Angle Camera::viewAngle() const
{
  return angle;
}

void Camera::draw()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0f, (GLfloat)size.width / size.height, 0.01f, 100.0f);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  glTranslatef(0, 2, -2.8f);
  glRotatef(angle.x, 1, 0, 0);
  glRotatef(angle.y, 0, 1, 0);
  glTranslatef(pos.x, 0, pos.y);

  glPushMatrix();
  glEnable(GL_LIGHT0);
  glTranslatef(-pos.x, 0, -pos.y);
  GLfloat sun[] = { 0, 1, 0, 0 }; 
  glLightfv(GL_LIGHT0, GL_POSITION, sun);
  GLfloat spec[] = { 0, 0, 0, 0 };
  glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
  glPopMatrix();

  /*glPushMatrix();
  glEnable(GL_LIGHT1);
  glTranslatef(0, 1, -4);

  gluSphere(*quadric, 0.068f, 32, 32);

  GLfloat spotLight[] = { 0, 0, 0, 1 };
  glLightfv(GL_LIGHT1, GL_POSITION, spotLight);
  GLfloat diffuse[] = { 0, 0, 0, 0 };
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
  GLfloat spec2[] = { 1, 1, 1, 0 };
  glLightfv(GL_LIGHT1, GL_SPECULAR, spec2);
  glPopMatrix();*/

  

  // прожектор
  // убывание интенсивности с расстоянием
  // отключено (по умолчанию)
  // половина угла при вершине 30 градусов
  // направление на центр плоскости
  ////draw sample square below
  //glLoadIdentity();
  glPushMatrix();
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 128 };
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  GLfloat x, y;
  glBegin(GL_QUADS);
  const float d = 0.03f;
  const float height = -3;
  glNormal3f(0.0, 1.0, 0.0);
  for (x = -2.0; x < 2.0; x += d)
  {
    for (y = 0.0; y > -5.0; y -= d)
    {
      glVertex3f(x, height, y);
      glVertex3f(x, height, y + d);
      glVertex3f(x + d, height, y + d);
      glVertex3f(x + d, height, y);
    }
  }
  glEnd();
  glPopMatrix();
}
