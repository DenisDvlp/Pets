//Linkable.cpp
#include "Linkable.h"
#include "Signal.h"

Linkable::~Linkable()
{
  unlinkAll();
}

void Linkable::link(void* object)
{
  if(object)
  {
    m_signals.insert(object);
  }
}

void Linkable::unlink(void* object)
{
  if(object)
  {
    m_signals.erase(object);
  }
}

void Linkable::unlinkAll()
{
  while(!m_signals.empty())
  {
    reinterpret_cast<Signal<>*>(*m_signals.begin())->unlink(this); //implicitly calls Linkable::unlink through the Signal
  }
}
