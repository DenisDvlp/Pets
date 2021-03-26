#pragma once
#include "Collection.h"

class Sizable
{
protected:
  CSize   m_size;

  virtual void onResize() = 0;
public:
  virtual ~Sizable();

  int width();
  void width(int width);

  int height();
  void height(int height);

  CSize size();
  void size(CSize size);
  void size(int width, int height);
};

