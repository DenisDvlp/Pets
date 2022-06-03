#pragma once

class GLUquadric;

class QuadricPtr final
{
  GLUquadric* ptr;
public:
  QuadricPtr();
  ~QuadricPtr();
  GLUquadric* operator*() const;
};

