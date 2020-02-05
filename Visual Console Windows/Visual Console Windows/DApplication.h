//DApplication.h
#pragma once
#include "Console.h"
#include "DLoop.h"
#include "DSafeObject.h"
#include "DVector.h"
#include "DMessage.h"
#include "DSize.h"
#include "DPoint.h"
#include "SystemEvents.h"
#include "Root.h"

class DApplication
{
    using DMessages = DSafeObject<DVector<DMessage>>;
public:
    DApplication();
    void run();
    void exit();
public:
    static SystemEvents events;
private:
    void consoleLoop();
    void systemLoop();
    void drawLoop();
private:
    Console m_console;

    DMessages m_consoleMessages;
    byte m_keyStates = 0;
    byte m_mouseButtons = 0;
    DSize m_size;
    DPoint m_position;

    DMessages m_systemMessages;
    DrawBuffer<_CHAR_INFO> m_drawBuffer;

    DLoop m_consoleLoop;
    DLoop m_systemLoop;
    DLoop m_drawLoop;

    Root m_root;
};