//Color.h
#pragma once
#include "DTypes.h"

#ifdef TRANSPARENT
#undef TRANSPARENT
#endif

enum class DColors : uint32
{
    TRANSPARENT = 0x00'00'00'00,
    BLACK       = 0xFF'00'00'00,
    RED         = 0xFF'FF'00'00,
    GREEN       = 0xFF'00'FF'00,
    BLUE        = 0xFF'00'00'FF,
    CYAN        = GREEN | BLUE,
    YELLOW      = RED   | GREEN,
    PURPLE      = RED   | BLUE,
    WHITE       = RED   | GREEN | BLUE,
};

class DColor
{
public:
    static byte Alpha(uint32 color);
    static byte Alpha(DColors color);
    static byte Red(uint32 color);
    static byte Red(DColors color);
    static byte Green(uint32 color);
    static byte Green(DColors color);
    static byte Blue(uint32 color);
    static byte Blue(DColors color);

public:
    DColor() = default;
    DColor(uint32 color);
    DColor(DColors color);
    DColor(byte r, byte g, byte b);
    DColor(byte a, byte r, byte g, byte b);

    void set(uint32 color);
    void set(DColors color);
    void set(byte r, byte g, byte b);
    void set(byte a, byte r, byte g, byte b);

    void setAlpha(byte color);
    void setRed(byte color);
    void setGreen(byte color);
    void setBlue(byte color);

    uint32 value() const;

    byte alpha() const;
    byte red() const;
    byte green() const;
    byte blue() const;

    DColor& operator=(uint32 color);
    DColor& operator=(DColors color);
    DColor& operator|=(uint32 color);
    DColor& operator|=(DColors color);
    operator uint32() const;

private:
    uint32 m_color;
};

