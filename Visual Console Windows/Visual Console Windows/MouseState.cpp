//MouseState.cpp
#include "MouseState.h"
#include <unordered_map>

using byte = unsigned char;

std::unordered_map<byte, std::string> mouseStateStringMap =
{
  { MouseState::NONE,    "MouseState::NONE"       },
  { MouseState::LEFT,    "MouseState::CAPSLOCK"   },
  { MouseState::RIGHT,   "MouseState::SCROLLLOCK" },
  { MouseState::MIDDLE1, "MouseState::MIDDLE1"    },
  { MouseState::MIDDLE2, "MouseState::MIDDLE2"    },
};

std::string MouseState::toString(byte MouseStates)
{
  auto founded = mouseStateStringMap.find(MouseStates);
  return founded != mouseStateStringMap.end() ? founded->second : "MouseState::UNKNOWN";
}

