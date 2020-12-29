//DDrawWin.cpp
#include "DDraw.h"
#include "DColor.h"
#include <Windows.h>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
#ifdef IN
#undef IN
#endif

//WINDOWS CONSOLE IMPLEMENTATION

byte convertToConsoleColor(const DColor color)
{
    const byte intensity = (color.red() > 169 || color.green() > 169 || color.blue() > 169) ? 0b1000 : 0;
    const byte r = color.red() > 84 ? 0b0100 : 0;
    const byte g = color.green() > 84 ? 0b0010 : 0;
    const byte b = color.blue() > 84 ? 0b0001 : 0;
    return intensity | r | g | b;
}

template<>
void DDrawWin::fill(const DColor color)
{
    auto total = size().square();
    auto raw = this->raw();
    const CHAR_INFO pixel = { ' ', convertToConsoleColor(color) << 4 };
    for(dint i = 0; i < total; ++i)
    {
        raw[i] = pixel;
    }
}

template<>
void DDrawWin::drawRect(const DRect& rect, const DColor color)
{
    auto intersection = rect & DRect(0, 0, size());
    const CHAR_INFO pixel = { ' ', convertToConsoleColor(color) << 4 };
    auto map = this->map();
    intersection.forEach([this, map, pixel] (auto i, auto j)
        {
            map[i][j] = pixel;
        });
}

#define HAS_FLAG(IN, FLAG) ((static_cast<uint8>(IN) & static_cast<uint8>(FLAG)) == static_cast<uint8>(FLAG))

template<>
void DDrawWin::drawText(const DRect& rect, const DString& text, const DColor color, const DAlign align)
{
    drawText(rect, DStringList(text), color, align);
}


template<>
void DDrawWin::drawText(const DRect& rect, const DStringList& text, const DColor color, const DAlign align)
{
    auto textRect = calcTextRect(text);
    dint textSize = textRect.width();
    textRect.position(rect.position());

    auto x = rect.x();
    auto y = rect.y();

    if(HAS_FLAG(align, DAlign::CENTER_H))
    {
        x = rect.center().x() - textRect.width() / 2;
    }
    else if(HAS_FLAG(align, DAlign::RIGHT))
    {
        x = rect.right() - textRect.width();
    }

    if(HAS_FLAG(align, DAlign::CENTER_V))
    {
        y = rect.center().y() - textRect.height() / 2;
    }
    else if(HAS_FLAG(align, DAlign::BOTTOM))
    {
        y = rect.bottom() - textRect.height();
    }

    textRect.x(x);
    textRect.y(y);

    auto intersection = rect & textRect & DRect(0, 0, size());

    x = std::max<dint>(0, intersection.x() - textRect.x());
    y = std::max<dint>(0, intersection.y() - textRect.y());

    const auto consoleTextColor = convertToConsoleColor(color);
    auto map = this->map();
    intersection.forEach([this, map, consoleTextColor, &text, &x, &y] (auto i, auto j)
        {
            map[i][j].Char.AsciiChar = text[y++][x++];
            map[i][j].Attributes |= consoleTextColor;
        });
}

template<>
DRect DDrawWin::calcTextRect(const DString& text)
{
    return DRect(0, 0, static_cast<dint>(text.size()), 1);
}

template<>
DRect DDrawWin::calcTextRect(const DStringList& text)
{
    dint maxWidth = 0;
    dint height = 0;
    for(const auto& line : text)
    {
        const auto lineSize = line.size();
        if(lineSize > maxWidth)
        {
            maxWidth = lineSize;
        }
        ++height;
    }
    return DRect(0, 0, maxWidth, height);
}

/*template<>
void DDrawWin::drawImage(Point16 point, const Image& image)
{
    auto imageRect = Rect(point.x(), point.y(), image.size().width() * 2, image.size().height());
    auto screenRect = Rect(0, 0, size());
    auto intersection = imageRect * screenRect;
    intersection.forEach([this, pixels = image.pixels(), x = intersection.x(), y = intersection.y()](auto i, auto j)
    {
        m_biArray[i][j].Char.AsciiChar = ' ';
        m_biArray[i][j].Attributes = convertToConsoleColor(pixels[(i - x)][(j - y) / 2]) << 4;
    });
}*/
