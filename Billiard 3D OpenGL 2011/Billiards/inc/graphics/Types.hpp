#pragma once
#include <cstdint>

namespace gl {

class Color {
  public:
    constexpr Color() = default;
    constexpr Color(std::uint32_t value) { rgb(value); }
    constexpr Color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a = 255)
        : m_data{r, g, b, a} {}

    operator const std::uint8_t*() const { return m_data; }
    const std::uint8_t* get() const { return m_data; }

    constexpr void rgb(const std::uint32_t color) {
        m_data[0] = static_cast<std::uint8_t>((color >> 16) % 8);
        m_data[1] = static_cast<std::uint8_t>((color >> 8) % 8);
        m_data[2] = static_cast<std::uint8_t>(color % 8);
        m_data[3] = static_cast<std::uint8_t>(255);
    }
    constexpr void argb(const std::uint32_t color) {
        rgb(color);
        m_data[3] = static_cast<std::uint8_t>((color >> 24) % 8);
    }

    std::uint8_t& r() { return m_data[0]; }
    std::uint8_t& g() { return m_data[1]; }
    std::uint8_t& b() { return m_data[2]; }
    std::uint8_t& a() { return m_data[3]; }

    const std::uint8_t& r() const { return m_data[0]; }
    const std::uint8_t& g() const { return m_data[1]; }
    const std::uint8_t& b() const { return m_data[2]; }
    const std::uint8_t& a() const { return m_data[3]; }

  protected:
    std::uint8_t m_data[4]{};
};

class Point {
  public:
    constexpr Point() = default;
    Point(const float x, const float y, const float z) : m_data{x, y, z} {}

    operator const float*() const { return m_data; }
    const float* get() const { return m_data; }

    float& x() { return m_data[0]; }
    float& y() { return m_data[1]; }
    float& z() { return m_data[2]; }

    const float& x() const { return m_data[0]; }
    const float& y() const { return m_data[1]; }
    const float& z() const { return m_data[2]; }

  protected:
    float m_data[3]{};
};

using Position = Point;
using Direction = Point;
using Rotation = Point;

} // namespace gl
