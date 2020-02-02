//KeyState.cpp
#include "KeyState.h"
#include <unordered_map>

using byte = unsigned char;

std::unordered_map<byte, std::string> keyStateStringMap =
{
  { KeyState::NONE,       "KeyState::NONE"       },
  { KeyState::CAPSLOCK,   "KeyState::CAPSLOCK"   },
  { KeyState::SCROLLLOCK, "KeyState::SCROLLLOCK" },
  { KeyState::NUMLOCK,    "KeyState::NUMLOCK"    },
  { KeyState::SHIFT,      "KeyState::SHIFT"      },
  { KeyState::CTRL_L,     "KeyState::CTRL_L"     },
  { KeyState::CTRL_R,     "KeyState::CTRL_R"     },
  { KeyState::ALT_L,      "KeyState::ALT_L"      },
  { KeyState::ALT_R,      "KeyState::ALT_R"      },
  { KeyState::CTRL,       "KeyState::CTRL"       },
  { KeyState::ALT,        "KeyState::ALT"        },
};

std::string KeyState::toString(byte keyStates)
{
  auto founded = keyStateStringMap.find(keyStates);
  return founded != keyStateStringMap.end() ? founded->second : "KeyState::UNKNOWN";
}

