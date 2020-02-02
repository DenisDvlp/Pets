//Application.cpp
#include "Application.h"
#include <Windows.h>

SystemEvents Application::events = SystemEvents();

Application::Application()
    : m_console()
    , m_messageBuffer()
    , m_drawBuffer()
    , m_root()
    , m_consoleLoop(&m_console, &m_messageBuffer)
    , m_systemLoop(&m_messageBuffer, &events, &m_drawBuffer, &m_root)
    , m_drawLoop(&m_drawBuffer, &m_console)
{
    m_console.setSize(80, 40);
    m_console.setFontSize(14);
    m_console.setTitle("Visual Console Windows");
    m_drawBuffer.size(m_console.getSize().width(), m_console.getSize().height());
    m_messageBuffer.addMessage(Message());
}

void Application::run()
{
    m_consoleLoop.run();
    m_systemLoop.run();
    m_drawLoop.run(true);
}

void Application::exit()
{
    m_consoleLoop.stop();
    m_systemLoop.stop();
    m_drawLoop.stop();
}