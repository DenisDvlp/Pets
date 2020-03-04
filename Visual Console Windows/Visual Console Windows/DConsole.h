//DConsole.h
#pragma once
#include "DSizable.h"
#include "DString.h"
#include "DVector.h"
#include "DMessage.h"
#include <Windows.h>

class DConsole
    : public DSizable
{
public:
    DConsole();
    void title(DString);
    DString title() const;
    void fontSize(int16);
    int16 fontSize() const;
    void fontName(DString);
    DString fontName() const;
    void show(const CHAR_INFO*) const;
    DVector<DMessage> recentMessages() const;

private:
    void init();
    void initFont(int16 size, DString);
    void setFontSize(CONSOLE_FONT_INFOEX&, int16);
    void setFontName(CONSOLE_FONT_INFOEX&, DString);
    void setFont(CONSOLE_FONT_INFOEX&);
    CONSOLE_FONT_INFOEX getFont() const;
    DSize getSize() const;

    void resize(DSize&) override;

private:
    HANDLE m_handleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE m_handleIN = GetStdHandle(STD_INPUT_HANDLE);
    HWND m_handleWindow = GetConsoleWindow();
    DSize m_maxSize;
    DString m_title;
    mutable DVector<INPUT_RECORD> m_inputEvents;
};