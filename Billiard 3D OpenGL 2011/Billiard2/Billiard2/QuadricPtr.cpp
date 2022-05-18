#include "QuadricPtr.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

QuadricPtr::QuadricPtr() : ptr(gluNewQuadric())
{
  gluQuadricNormals(ptr, GLU_SMOOTH);
  gluQuadricTexture(ptr, GL_TRUE);
}

QuadricPtr::~QuadricPtr()
{
  gluDeleteQuadric(ptr);
}

GLUquadric* QuadricPtr::operator*()
{
  return ptr;
}
