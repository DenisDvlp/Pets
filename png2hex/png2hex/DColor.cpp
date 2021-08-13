//DColor.cpp
#include "DColor.h"

constexpr size_t BITS_IN_BYTE = 8;

#define INIT_CHANNEL_SHIFT(ÑHANNEL, BYTE_NUM) constexpr size_t ÑHANNEL##_SHIFT = BITS_IN_BYTE * BYTE_NUM;
INIT_CHANNEL_SHIFT(ALPHA, 3) // constexpr size_t ALPHA_SHIFT = BITS_IN_BYTE * 3;
INIT_CHANNEL_SHIFT(RED, 2)
INIT_CHANNEL_SHIFT(GREEN, 1)
INIT_CHANNEL_SHIFT(BLUE, 0)

#define INT_CHANNEL(IN, ÑHANNEL) (static_cast<uint32>(IN) << ÑHANNEL##_SHIFT)

#define INIT_CHANNEL_MASK(ÑHANNEL) constexpr uint32 ÑHANNEL##_MASK = INT_CHANNEL(0xFF, ÑHANNEL);
INIT_CHANNEL_MASK(ALPHA) // constexpr uint32 ALPHA_MASK = INT_CHANNEL(0xFF, ALPHA);
INIT_CHANNEL_MASK(RED)
INIT_CHANNEL_MASK(GREEN)
INIT_CHANNEL_MASK(BLUE)

#define GET_CHANNEL(IN, ÑHANNEL) ((IN & ÑHANNEL##_MASK) >> ÑHANNEL##_SHIFT)
#define SET_CHANNEL(OUT, IN, ÑHANNEL) OUT &= ~static_cast<uint32>(ÑHANNEL##_MASK) | INT_CHANNEL(IN, ÑHANNEL)

inline byte DColor::Alpha(uint32 color)
{
    return GET_CHANNEL(color, ALPHA);
}

inline byte DColor::Alpha(DColors color)
{
    return Alpha(static_cast<uint32>(color));
}

inline byte DColor::Red(uint32 color)
{
    return GET_CHANNEL(color, RED);
}

inline byte DColor::Red(DColors color)
{
    return Red(static_cast<uint32>(color));
}

inline byte DColor::Green(uint32 color)
{
    return GET_CHANNEL(color, GREEN);
}

inline byte DColor::Green(DColors color)
{
    return Green(static_cast<uint32>(color));
}

inline byte DColor::Blue(uint32 color)
{
    return GET_CHANNEL(color, BLUE);
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
        INT_CHANNEL(0xFF, ALPHA) |
        INT_CHANNEL(red, RED) |
        INT_CHANNEL(green, GREEN) |
        INT_CHANNEL(blue, BLUE)
    )
{}

DColor::DColor(byte alpha, byte red, byte green, byte blue)
    : m_color(
        INT_CHANNEL(alpha, ALPHA) |
        INT_CHANNEL(red, RED) |
        INT_CHANNEL(green, GREEN) |
        INT_CHANNEL(blue, BLUE)
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
        INT_CHANNEL(0xFF, ALPHA) |
        INT_CHANNEL(red, RED) |
        INT_CHANNEL(green, GREEN) |
        INT_CHANNEL(blue, BLUE);
}

void DColor::set(byte alpha, byte red, byte green, byte blue)
{
    m_color =
        INT_CHANNEL(alpha, ALPHA) |
        INT_CHANNEL(red, RED) |
        INT_CHANNEL(green, GREEN) |
        INT_CHANNEL(blue, BLUE);
}

void DColor::setAlpha(byte color)
{
    SET_CHANNEL(m_color, color, ALPHA);
}

void DColor::setRed(byte color)
{
    SET_CHANNEL(m_color, color, RED);
}

void DColor::setGreen(byte color)
{
    SET_CHANNEL(m_color, color, GREEN);
}

void DColor::setBlue(byte color)
{
    SET_CHANNEL(m_color, color, BLUE);
}

inline DColor::operator uint32() const
{
    return m_color;
}

inline uint32 DColor::value() const
{
    return m_color;
}

byte DColor::alpha() const
{
    return Alpha(m_color);
}

byte DColor::red() const
{
    return Red(m_color);
}

byte DColor::green() const
{
    return Green(m_color);
}

byte DColor::blue() const
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

bool DColor::operator==(uint32 color) const
{
  return m_color == color;
}

bool DColor::operator==(DColors color) const
{
  return m_color == static_cast<uint32>(color);
}

bool DColor::operator!=(uint32 color) const
{
  return m_color != color;
}

bool DColor::operator!=(DColors color) const
{
  return m_color != static_cast<uint32>(color);
}
