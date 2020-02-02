//MessageType.cpp
#include "MessageType.h"
#include <unordered_map>

std::unordered_map<MessageType, std::string> messageTypeStringMap =
{
  { MessageType::NONE,               "MessageType::NONE"               },
  { MessageType::KEY_UP,             "MessageType::KEY_UP"             },
  { MessageType::KEY_DOWN,           "MessageType::KEY_DOWN"           },
  { MessageType::MOUSE_BUTTONS,      "MessageType::MOUSE_BUTTONS"      },
  { MessageType::MOUSE_UP,           "MessageType::MOUSE_UP"           },
  { MessageType::MOUSE_DOWN,         "MessageType::MOUSE_DOWN"         },
  { MessageType::MOUSE_MOVE,         "MessageType::MOUSE_MOVE"         },
  { MessageType::MOUSE_DOUBLE_CLICK, "MessageType::MOUSE_DOUBLE_CLICK" },
  { MessageType::MOUSE_WHEEL,        "MessageType::MOUSE_WHEEL"        },
  { MessageType::DISPLAY_RESIZE,     "MessageType::DISPLAY_RESIZE"     },
  { MessageType::SIZE,               "MessageType::SIZE"               },
};

std::string toString(MessageType type)
{
  return messageTypeStringMap[type];
}
