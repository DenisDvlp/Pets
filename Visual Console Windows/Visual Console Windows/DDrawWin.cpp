#include "DDrawWin.h"
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

void DDrawWin::fill(const DColor color)
{
    auto square = size().square();
    auto raw = m_biArray.raw();
    for(decltype(square) i = 0; i < square; ++i)
    {
        raw[i].Char.AsciiChar = ' ';
        raw[i].Attributes = convertToConsoleColor(color) << 4;
    }
}

void DDrawWin::drawRect(const DRect& rect, const DColor color)
{
    auto intersection = rect & DRect(0, 0, width(), height());
    intersection.forEach([this, color] (auto i, auto j)
        {
            m_biArray[i][j].Char.AsciiChar = ' ';
            m_biArray[i][j].Attributes = convertToConsoleColor(color) << 4;
        });
}

#define HAS_FLAG(IN, FLAG) ((static_cast<uint8>(IN) & static_cast<uint8>(FLAG)) == static_cast<uint8>(FLAG))

void DDrawWin::drawText(const DRect& rect, const DStringList& text, const DColor color, const DAlign align)
{
    auto textRect = calcTextRect(text);
    dint textSize = textRect.width();
    textRect.position(rect.position());

    if(HAS_FLAG(align, DAlign::LEFT))
    {
        textRect.x(rect.x());

        if(HAS_FLAG(align, DAlign::RIGHT))
        {
            textRect.right(rect.right());
        }
    }
    else if(HAS_FLAG(align, DAlign::RIGHT))
    {
        textRect.x(rect.right() - textRect.width());
    }
    else
    {
        textRect.x(rect.center().x() - textRect.width() / 2);
    }

    if(HAS_FLAG(align, DAlign::TOP))
    {
        textRect.y(rect.y());

        if(HAS_FLAG(align, DAlign::BOTTOM))
        {
            textRect.bottom(rect.bottom());
        }
    }
    else if(HAS_FLAG(align, DAlign::BOTTOM))
    {
        textRect.y(rect.bottom() - textRect.height());
    }
    else
    {
        textRect.y(rect.center().y() - textRect.height() / 2);
    }

    auto intersection = rect & textRect & DRect(0, 0, width(), height());

    int x = std::max<dint>(0, intersection.x() - textRect.x());
    int y = std::max<dint>(0, intersection.y() - textRect.y());

    intersection.forEach([this, color, &text, &x, &y] (auto i, auto j)
        {
            m_biArray[i][j].Char.AsciiChar = text[y][x++];
            m_biArray[i][j].Attributes = m_biArray[i][j].Attributes | convertToConsoleColor(color);
        });
}

DRect DDrawWin::calcTextRect(const DString& text)
{
    return DRect(0, 0, static_cast<dint>(text.size()), 1);
}

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
