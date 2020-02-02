//IPositionable.h
#pragma once

template<typename T>
class PointT;

template<typename T>
class IPositionable
{
public:
  virtual ~IPositionable()     = default;
  virtual T x() const                = 0;
  virtual T y() const                = 0;
  virtual void x(T)                  = 0;
  virtual void y(T)                  = 0;
  virtual void position(T, T)        = 0;
  virtual void position(PointT<T>)   = 0;
  virtual PointT<T> position() const = 0;
};