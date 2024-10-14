#pragma once

namespace gl {

class TypeBase {
  public:
    constexpr TypeBase() = default;
    constexpr TypeBase(const float i0, const float i1, const float i2, const float i3 = 0) : m_data{i0, i1, i2, i3} {}
    void set(const float i0, const float i1) {
        m_data[0] = i0;
        m_data[1] = i1;
    }
    void set(const float i0, const float i1, const float i2) {
        m_data[0] = i0;
        m_data[1] = i1;
        m_data[2] = i2;
    }
    void set(const float i0, const float i1, const float i2, const float i3) {
        m_data[0] = i0;
        m_data[1] = i1;
        m_data[2] = i2;
        m_data[3] = i3;
    }
    operator float*() { return m_data; }
    operator const float*() const { return m_data; }
    TypeBase operator-() const { return {-m_data[0], -m_data[1], -m_data[2], -m_data[3]}; }

  protected:
    float m_data[4]{};
};

class Color : public TypeBase {
  public:
    float& r() { return m_data[0]; }
    float& g() { return m_data[1]; }
    float& b() { return m_data[2]; }
    float& a() { return m_data[3]; }
    const float& r() const { return m_data[0]; }
    const float& g() const { return m_data[1]; }
    const float& b() const { return m_data[2]; }
    const float& a() const { return m_data[3]; }
};

class Point : public TypeBase {
  public:
    float& x() { return m_data[0]; }
    float& y() { return m_data[1]; }
    float& z() { return m_data[2]; }
    const float& x() const { return m_data[0]; }
    const float& y() const { return m_data[1]; }
    const float& z() const { return m_data[2]; }
};

using Position = Point;
using Direction = Point;
using Rotation = Point;

} // namespace gl
