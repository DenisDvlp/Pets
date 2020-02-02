//Linkable.h
#pragma once
#include <set>

class Linkable
{
public:
  virtual ~Linkable();
  void link(void* object);
  void unlink(void* object);
  void unlinkAll();
private:
  std::set<void*> m_signals;
};