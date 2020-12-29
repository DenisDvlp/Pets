//DApplication.h
#pragma once
#include "DConsole.h"
#include "DLoop.h"
#include "DSafeObject.h"
#include "DVector.h"
#include "DMessage.h"
#include "DSize.h"
#include "DPoint.h"
#include "SystemEvents.h"
#include "DDrawBuffer.h"
#include "DView.h"

class DApplication
{
    using DMessages = DSafeObject<DVector<DMessage>>;
public:
    DApplication();
    void run();
    void exit();
    void addView(DView*);
private:
    void consoleLoop();
    void systemLoop();
    void drawLoop();
    void drawRoot(IDDraw&, DView&);
private:
    DConsole m_console;

    DMessages m_consoleMessages;
    byte m_keyStates = 0;
    byte m_mouseButtons = 0;
    DSize m_size;
    DPoint m_position;

    DMessages m_systemMessages;
    DDrawBuffer m_drawBuffer;

    DLoop m_consoleLoop;
    DLoop m_systemLoop;
    DLoop m_drawLoop;

    DView m_rootView;
};