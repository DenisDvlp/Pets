#include "QuadricPtr.h"
#include "Drawing.h"

QuadricPtr::QuadricPtr() : ptr(gluNewQuadric())
{
  gluQuadricNormals(ptr, GLU_SMOOTH);
  gluQuadricTexture(ptr, GL_TRUE);
}

QuadricPtr::~QuadricPtr()
{
  gluDeleteQuadric(ptr);
}

GLUquadric* QuadricPtr::operator*() const
{
  return ptr;
}
