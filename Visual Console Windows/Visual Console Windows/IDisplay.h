//IDisplay.h
#pragma once

template<typename T>
class IDisplay
{
public:
  virtual ~IDisplay() = default;
  virtual void show(const T*) = 0;
};