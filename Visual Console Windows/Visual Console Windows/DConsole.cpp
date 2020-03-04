//DConsole.cpp
#include "DConsole.h"
#include <unordered_map>

#ifdef min
#undef min
#endif
#ifdef DELETE
#undef DELETE
#endif

//https://docs.microsoft.com/en-us/windows/console/key-event-record-str

static std::unordered_map<unsigned, MessageType> mouseTypeMap =
{
    { 0,              MessageType::MOUSE_BUTTONS      },
    { MOUSE_MOVED,    MessageType::MOUSE_MOVE         },
    { DOUBLE_CLICK,   MessageType::MOUSE_DOUBLE_CLICK },
    { MOUSE_WHEELED,  MessageType::MOUSE_WHEEL        },
    { MOUSE_HWHEELED, MessageType::MOUSE_WHEEL        },
};

static std::unordered_map<unsigned, Key> keyMap =
{
    { 0, Key::NONE },

    { 0x41, Key::A },
    { 0x42, Key::B },
    { 0x43, Key::C },
    { 0x44, Key::D },
    { 0x45, Key::E },
    { 0x46, Key::F },
    { 0x47, Key::G },
    { 0x48, Key::H },
    { 0x49, Key::I },
    { 0x4A, Key::J },
    { 0x4B, Key::K },
    { 0x4C, Key::L },
    { 0x4D, Key::M },
    { 0x4E, Key::N },
    { 0x4F, Key::O },
    { 0x50, Key::P },
    { 0x51, Key::Q },
    { 0x52, Key::R },
    { 0x53, Key::S },
    { 0x54, Key::T },
    { 0x55, Key::U },
    { 0x56, Key::V },
    { 0x57, Key::W },
    { 0x58, Key::X },
    { 0x59, Key::Y },
    { 0x5A, Key::Z },

    { VK_OEM_4,      Key::SQUARE_BRACKET_L },
    { VK_OEM_6,      Key::SQUARE_BRACKET_R },
    { VK_OEM_1,      Key::SEMICOLON        },
    { VK_OEM_7,      Key::QUOTES           },
    { VK_OEM_COMMA,  Key::COMA             },
    { VK_OEM_PERIOD, Key::DOT              },
    { VK_OEM_5,      Key::BACKSLASH        },
    { VK_OEM_2,      Key::SLASH            },

    { 0x30, Key::_0 },
    { 0x31, Key::_1 },
    { 0x32, Key::_2 },
    { 0x33, Key::_3 },
    { 0x34, Key::_4 },
    { 0x35, Key::_5 },
    { 0x36, Key::_6 },
    { 0x37, Key::_7 },
    { 0x38, Key::_8 },
    { 0x39, Key::_9 },

    { VK_OEM_3,     Key::APOSTROPHE },
    { VK_OEM_MINUS, Key::UNDERSCORE },
    { VK_OEM_PLUS,  Key::ASSIGN     },
    { VK_BACK,      Key::BACKSPACE  },

    { VK_NUMPAD0, Key::NUM_0 },
    { VK_NUMPAD1, Key::NUM_1 },
    { VK_NUMPAD2, Key::NUM_2 },
    { VK_NUMPAD3, Key::NUM_3 },
    { VK_NUMPAD4, Key::NUM_4 },
    { VK_NUMPAD5, Key::NUM_5 },
    { VK_NUMPAD6, Key::NUM_6 },
    { VK_NUMPAD7, Key::NUM_7 },
    { VK_NUMPAD8, Key::NUM_8 },
    { VK_NUMPAD9, Key::NUM_9 },

    { VK_MULTIPLY, Key::MULTIPLY },
    { VK_ADD,      Key::PLUS     },
    { VK_SUBTRACT, Key::MINUS    },
    { VK_DIVIDE,   Key::DIVIDE   },
    { VK_DECIMAL,  Key::PERIOD   },

    { VK_F1,  Key::F1  },
    { VK_F2,  Key::F2  },
    { VK_F3,  Key::F3  },
    { VK_F4,  Key::F4  },
    { VK_F5,  Key::F5  },
    { VK_F6,  Key::F6  },
    { VK_F7,  Key::F7  },
    { VK_F8,  Key::F8  },
    { VK_F9,  Key::F9  },
    { VK_F10, Key::F10 },
    { VK_F11, Key::F11 },
    { VK_F12, Key::F12 },

    { VK_SHIFT,   Key::SHIFT      },
    { VK_CONTROL, Key::CTRL       },
    { VK_MENU,    Key::ALT        },
    { VK_LWIN,    Key::WIN_L      },
    { VK_RWIN,    Key::WIN_R      },
    { VK_PAUSE,   Key::BREAK      },
    { VK_APPS,    Key::MENU       },
    { VK_TAB,     Key::TAB        },
    { VK_CAPITAL, Key::CAPSLOCK   },
    { VK_NUMLOCK, Key::NUMLOCK    },
    { VK_SCROLL,  Key::SCROLLLOCK },

    { VK_RETURN, Key::ENTER     },
    { VK_ESCAPE, Key::ESCAPE    },
    { VK_SPACE,  Key::SPACE     },
    { VK_END,    Key::END       },
    { VK_HOME,   Key::HOME      },
    { VK_INSERT, Key::INSERT    },
    { VK_DELETE, Key::DELETE    },
    { VK_PRIOR,  Key::PAGE_UP   },
    { VK_NEXT,   Key::PAGE_DOWN },

    { VK_LEFT,  Key::ARROW_LEFT  },
    { VK_UP,    Key::ARROW_UP    },
    { VK_RIGHT, Key::ARROW_RIGHT },
    { VK_DOWN,  Key::ARROW_DOWN  },

    { VK_NAVIGATION_UP,    Key::ARROW_UP    },
    { VK_NAVIGATION_DOWN,  Key::ARROW_DOWN  },
    { VK_NAVIGATION_LEFT,  Key::ARROW_LEFT  },
    { VK_NAVIGATION_RIGHT, Key::ARROW_RIGHT },

};

DConsole::DConsole()
{
    init();
    initFont(8, "Lucida DConsole");
}

void DConsole::title(DString value)
{
    m_title = std::move(value);
    SetConsoleTitleA(m_title.data());
}

DString DConsole::title() const
{
    return m_title;
}

void DConsole::fontSize(int16 fontSize)
{
    auto font = getFont();
    setFontSize(font, fontSize);
    setFont(font);
}

int16 DConsole::fontSize() const
{
    return getFont().dwFontSize.Y;
}

void DConsole::fontName(DString fontName)
{
    auto font = getFont();
    setFontName(font, std::move(fontName));
    setFont(font);
}

DString DConsole::fontName() const
{
    std::wstring wstr(getFont().FaceName);
    return DString(wstr.begin(), wstr.end());
}

void DConsole::show(const CHAR_INFO* buffer) const
{
    if(buffer)
    {
        SMALL_RECT rect = { 0, 0, static_cast<SHORT>(width()), static_cast<SHORT>(height()) };
        WriteConsoleOutputA(m_handleOUT, buffer, { static_cast<SHORT>(width()), static_cast<SHORT>(height()) }, { 0, 0 }, &rect);
    }
}

void DConsole::init()
{
    DWORD mode =
        ENABLE_PROCESSED_INPUT |
        ENABLE_LINE_INPUT |
        ENABLE_ECHO_INPUT |
        ENABLE_WINDOW_INPUT |
        ENABLE_MOUSE_INPUT |
        ENABLE_EXTENDED_FLAGS |
        ENABLE_AUTO_POSITION;
    SetConsoleMode(m_handleIN, mode);
    auto style = GetWindowLong(m_handleWindow, GWL_STYLE);
    SetWindowLong(m_handleWindow, GWL_STYLE, style & ~(WS_SIZEBOX | WS_MAXIMIZEBOX));
    auto maxSize = GetLargestConsoleWindowSize(m_handleOUT);
    m_maxSize.set(maxSize.X, maxSize.Y);
    size(getSize());
}

void DConsole::initFont(int16 fontSize, DString fontName)
{
    CONSOLE_FONT_INFOEX font{ sizeof(CONSOLE_FONT_INFOEX) };
    font.FontWeight = FW_NORMAL;

    setFontSize(font, fontSize);
    setFontName(font, std::move(fontName));
    setFont(font);
}

void DConsole::setFontSize(CONSOLE_FONT_INFOEX& font, int16 fontSize)
{
    font.dwFontSize.Y = std::max<int16>(0, fontSize);
}

void DConsole::setFontName(CONSOLE_FONT_INFOEX& font, DString fontName)
{
    size_t len = std::min<size_t>(fontName.size() + 1, LF_FACESIZE);
    auto wstr = std::wstring(fontName.begin(), fontName.end());
    wcscpy_s(font.FaceName, len, wstr.c_str());
}

void DConsole::setFont(CONSOLE_FONT_INFOEX& font)
{
    SetCurrentConsoleFontEx(m_handleOUT, FALSE, &font);
}

CONSOLE_FONT_INFOEX DConsole::getFont() const
{
    CONSOLE_FONT_INFOEX font{ sizeof(CONSOLE_FONT_INFOEX) };
    GetCurrentConsoleFontEx(m_handleOUT, FALSE, &font);
    return font;
}

DSize DConsole::getSize() const
{
    CONSOLE_SCREEN_BUFFER_INFO info = { sizeof(CONSOLE_SCREEN_BUFFER_INFO) };
    GetConsoleScreenBufferInfo(m_handleOUT, &info);
    return DSize(info.dwSize.X, info.dwSize.Y);
}

void DConsole::resize(DSize& size)
{
    size.set(
        std::min(m_maxSize.width(), width()),
        std::min(m_maxSize.height(), height())
    );

    CONSOLE_SCREEN_BUFFER_INFOEX info = { sizeof(CONSOLE_SCREEN_BUFFER_INFOEX) };
    GetConsoleScreenBufferInfoEx(m_handleOUT, &info);

    info.srWindow = { 0, 0, static_cast<SHORT>(size.width() - 1), static_cast<SHORT>(size.height() - 1) };
    info.dwSize = { static_cast<SHORT>(size.width()), static_cast<SHORT>(size.height()) };

    SetConsoleScreenBufferInfoEx(m_handleOUT, &info);
    SetConsoleWindowInfo(m_handleOUT, TRUE, &info.srWindow);
}

DVector<DMessage> DConsole::recentMessages() const
{
    DWORD number = 0;
    DWORD numberRead = 0;

    GetNumberOfConsoleInputEvents(m_handleIN, &number);

    m_inputEvents.resize(number);
    auto events = const_cast<INPUT_RECORD*>(m_inputEvents.data());

    ReadConsoleInput(m_handleIN, events, number, &numberRead);

    DVector<DMessage> messages;
    DMessage message;

    for(DWORD i = 0; i < numberRead; ++i)
    {
        message.type = MessageType::NONE;
        switch(events[i].EventType)
        {
        case KEY_EVENT:
        {
            auto& event = events[i].Event.KeyEvent;
            message.type = event.bKeyDown ? MessageType::KEY_DOWN : MessageType::KEY_UP;
            message.keyStates = static_cast<byte>(event.dwControlKeyState);
            message.data.key = keyMap[event.wVirtualKeyCode];
            break;
        }
        case MOUSE_EVENT:
        {
            auto& event = events[i].Event.MouseEvent;
            message.type = mouseTypeMap[event.dwEventFlags];
            message.keyStates = static_cast<byte>(event.dwControlKeyState);
            switch(message.type)
            {
            case MessageType::MOUSE_BUTTONS:
            case MessageType::MOUSE_DOUBLE_CLICK:
                message.data.byte = static_cast<byte>(LOWORD(event.dwButtonState));
                break;
            case MessageType::MOUSE_MOVE:
                message.data.position = DPoint(event.dwMousePosition.X, event.dwMousePosition.Y);
                break;
            case MessageType::MOUSE_WHEEL:
                message.data.byte = static_cast<byte>(HIWORD(event.dwButtonState));
                break;
            }
            break;
        }
        case WINDOW_BUFFER_SIZE_EVENT:
        {
            auto& event = events[i].Event.WindowBufferSizeEvent;
            message.type = MessageType::DISPLAY_RESIZE;
            message.data.size = DSize(event.dwSize.X, event.dwSize.Y);
            break;
        }
        }

        if(MessageType::NONE != message.type)
        {
            messages.push(message);
        }
    }
    return messages;
}

