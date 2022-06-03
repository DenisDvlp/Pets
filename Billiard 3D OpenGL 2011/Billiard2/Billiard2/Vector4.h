#pragma once

template<typename T>
struct Vector4 {
  T data[4] = {};
  constexpr Vector4() = default;
  constexpr Vector4(T a, T b, T c, T d = 0) : data{a, b, c, d} {}
  void set(T a, T b)
  {
    data[0] = a;
    data[1] = b;
  }
  void set(T a, T b, T c)
  {
    data[0] = a;
    data[1] = b;
    data[2] = c;
  }
  void set(T a, T b, T c, T d)
  {
    data[0] = a;
    data[1] = b;
    data[2] = c;
    data[3] = d;
  }
  operator T* () {
    return data;
  }
  operator const T* () const {
    return (const T*)(const_cast<Vector4*>(this));
  }
  Vector4 operator-() const
  {
    return { -data[0], -data[1], -data[2], -data[3] };
  }
  T& x() { return data[0]; }
  T& y() { return data[1]; }
  T& z() { return data[2]; }
  const T& x() const { return data[0]; }
  const T& y() const { return data[1]; }
  const T& z() const { return data[2]; }

  T& r() { return data[0]; }
  T& g() { return data[1]; }
  T& b() { return data[2]; }
  T& a() { return data[3]; }
  const T& r() const { return data[0]; }
  const T& g() const { return data[1]; }
  const T& b() const { return data[2]; }
  const T& a() const { return data[3]; }
};

using Color = Vector4<float>;
using Direction = Vector4<float>;
using Position = Vector4<float>;
using Angle = Vector4<float>;