//DColor.cpp
#include "DColor.h"

constexpr size_t ALPHA_SHIFT = sizeof(byte) * 3;
constexpr size_t RED_SHIFT = sizeof(byte) * 2;
constexpr size_t GREEN_SHIFT = sizeof(byte) * 1;
constexpr size_t BLUE_SHIFT = sizeof(byte) * 0;

#define INT_CHANNEL(IN, SHIFT) (static_cast<uint32>(IN) << SHIFT)

constexpr uint32 ALPHA_MASK = INT_CHANNEL(0xFF, ALPHA_SHIFT);
constexpr uint32 RED_MASK = INT_CHANNEL(0xFF, RED_SHIFT);
constexpr uint32 GREEN_MASK = INT_CHANNEL(0xFF, GREEN_SHIFT);
constexpr uint32 BLUE_MASK = INT_CHANNEL(0xFF, BLUE_SHIFT);

#define GET_CHANNEL(IN, MASK, SHIFT) ((IN & MASK) >> SHIFT)
#define SET_CHANNEL(OUT, IN, MASK, SHIFT) OUT &= ~static_cast<uint32>(MASK) | INT_CHANNEL(IN, SHIFT)

inline byte DColor::Alpha(uint32 color)
{
    return GET_CHANNEL(color, ALPHA_MASK, ALPHA_SHIFT);
}

inline byte DColor::Alpha(DColors color)
{
    return Alpha(static_cast<uint32>(color));
}

inline byte DColor::Red(uint32 color)
{
    return GET_CHANNEL(color, RED_MASK, RED_SHIFT);
}

inline byte DColor::Red(DColors color)
{
    return Red(static_cast<uint32>(color));
}

inline byte DColor::Green(uint32 color)
{
    return GET_CHANNEL(color, GREEN_MASK, GREEN_SHIFT);
}

inline byte DColor::Green(DColors color)
{
    return Green(static_cast<uint32>(color));
}

inline byte DColor::Blue(uint32 color)
{
    return GET_CHANNEL(color, BLUE_MASK, BLUE_SHIFT);
}

inline byte DColor::Blue(DColors color)
{
    return Blue(static_cast<uint32>(color));
}

DColor::DColor(uint32 color)
    : m_color(color)
{}

DColor::DColor(DColors color)
    : m_color(static_cast<uint32>(color))
{}

DColor::DColor(byte red, byte green, byte blue)
    : m_color(
        INT_CHANNEL(0xFF, ALPHA_SHIFT) |
        INT_CHANNEL(red, RED_SHIFT) |
        INT_CHANNEL(green, GREEN_SHIFT) |
        INT_CHANNEL(blue, BLUE_SHIFT)
    )
{}

DColor::DColor(byte alpha, byte red, byte green, byte blue)
    : m_color(
        INT_CHANNEL(alpha, ALPHA_SHIFT) |
        INT_CHANNEL(red, RED_SHIFT) |
        INT_CHANNEL(green, GREEN_SHIFT) |
        INT_CHANNEL(blue, BLUE_SHIFT)
    )
{}

inline void DColor::set(uint32 color)
{
    m_color = color;
}

inline void DColor::set(DColors color)
{
    m_color = static_cast<uint32>(color);
}

void DColor::set(byte red, byte green, byte blue)
{
    m_color =
        ALPHA_MASK |
        INT_CHANNEL(red, RED_SHIFT) |
        INT_CHANNEL(green, GREEN_SHIFT) |
        INT_CHANNEL(blue, BLUE_SHIFT);
}

void DColor::set(byte alpha, byte red, byte green, byte blue)
{
    m_color =
        INT_CHANNEL(alpha, ALPHA_SHIFT) |
        INT_CHANNEL(red, RED_SHIFT) |
        INT_CHANNEL(green, GREEN_SHIFT) |
        INT_CHANNEL(blue, BLUE_SHIFT);
}

void DColor::setAlpha(byte color)
{
    SET_CHANNEL(m_color, color, ALPHA_MASK, ALPHA_SHIFT);
}

void DColor::setRed(byte color)
{
    SET_CHANNEL(m_color, color, RED_MASK, RED_SHIFT);
}

void DColor::setGreen(byte color)
{
    SET_CHANNEL(m_color, color, GREEN_MASK, GREEN_SHIFT);
}

void DColor::setBlue(byte color)
{
    SET_CHANNEL(m_color, color, BLUE_MASK, BLUE_SHIFT);
}

inline DColor::operator uint32() const
{
    return m_color;
}

inline uint32 DColor::value() const
{
    return m_color;
}

inline byte DColor::alpha() const
{
    return Alpha(m_color);
}

inline byte DColor::red() const
{
    return Red(m_color);
}

inline byte DColor::green() const
{
    return Green(m_color);
}

inline byte DColor::blue() const
{
    return Blue(m_color);
}

DColor& DColor::operator=(uint32 color)
{
    m_color = color;
    return *this;
}

DColor& DColor::operator=(DColors color)
{
    m_color = static_cast<uint32>(color);
    return *this;
}

DColor& DColor::operator|=(uint32 color)
{
    m_color |= color;
    return *this;
}

DColor& DColor::operator|=(DColors color)
{
    m_color |= static_cast<uint32>(color);
    return *this;
}
