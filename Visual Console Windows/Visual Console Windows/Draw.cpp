#include "Draw.h"
#include "Image.h"
#include "BasicTypes.h"
#include <Windows.h>
#include <algorithm>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

//WINDOWS CONSOLE IMPLEMENTATION

byte convertToConsoleColor(Color color)
{
    byte intensity = (color.r > 169 || color.g > 169 || color.b > 169) ? 0b1000 : 0;
    byte r = color.r > 84 ? 0b0100 : 0;
    byte g = color.g > 84 ? 0b0010 : 0;
    byte b = color.b > 84 ? 0b0001 : 0;
    return intensity | r | g | b;
}

template<>
void Draw<CHAR_INFO>::clear(Color color)
{
    auto square = m_size.square();
    auto raw = m_biArray.raw();
    for(decltype(square) i = 0; i < square; ++i)
    {
        raw[i].Char.AsciiChar = ' ';
        raw[i].Attributes = convertToConsoleColor(color) << 4;
    }
}

template<>
void Draw<CHAR_INFO>::drawRect(Rect16 rect, Color color)
{
    auto intersection = rect * Rect16(0, 0, width(), height());
    intersection.forEach([this, color] (auto i, auto j)
        {
            m_biArray[i][j].Char.AsciiChar = '$';
            m_biArray[i][j].Attributes = convertToConsoleColor(color) << 4;
        });
}

template<>
void Draw<CHAR_INFO>::drawText(Rect16 rect, const DString& text, Color color, Align align)
{
    using intx = decltype(rect.width());
    intx textSize = text.size();
    auto textRect = calcTextRect(text);
    textRect.position(rect.position());

    switch(align)
    {
    case Align::CENTER_CENTER:
    case Align::CENTER_TOP:
    case Align::CENTER_BOTTOM:
        textRect.center(rect.center());
        break;
    case Align::RIGHT_CENTER:
    case Align::RIGHT_TOP:
    case Align::RIGHT_BOTTOM:
        textRect.x(rect.right() - textSize);
        break;
    }

    switch(align)
    {
    case Align::CENTER_TOP:
        textRect.y(rect.y());
        break;
    case Align::LEFT_CENTER:
    case Align::RIGHT_CENTER:
        textRect.y(rect.center().y());
        break;
    case Align::LEFT_BOTTOM:
    case Align::CENTER_BOTTOM:
    case Align::RIGHT_BOTTOM:
        textRect.y(rect.bottom() - 1);
        break;
    }

    auto intersection = rect * textRect * Rect16(0, 0, width(), height());

    int x = std::max<short>(0, intersection.x() - textRect.x());
    intersection.forEach([this, color, &text, &x] (auto i, auto j)
        {
            m_biArray[i][j].Char.AsciiChar = text[x++];
            m_biArray[i][j].Attributes = m_biArray[i][j].Attributes | convertToConsoleColor(color);
        });
}

template<>
void Draw<CHAR_INFO>::drawImage(Point16 point, const Image& image)
{
    auto imageRect = Rect(point.x(), point.y(), image.size().width() * 2, image.size().height());
    auto screenRect = Rect(0, 0, size());
    auto intersection = imageRect * screenRect;
    intersection.forEach([this, pixels = image.pixels(), x = intersection.x(), y = intersection.y()](auto i, auto j)
    {
        m_biArray[i][j].Char.AsciiChar = ' ';
        m_biArray[i][j].Attributes = convertToConsoleColor(pixels[(i - x)][(j - y) / 2]) << 4;
    });
}

template<>
Rect16 Draw<CHAR_INFO>::calcTextRect(const DString& text)
{
    return Rect16(0, 0, static_cast<short>(text.size()), 1);
}
