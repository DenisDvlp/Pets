//Message.cpp
#include "Message.h"
#include <string>

std::string Message::toString()
{
  std::string output = ::toString(type) + "\t";
  if (type == MessageType::DISPLAY_RESIZE)
    output += std::to_string(data.size.width()) + " " + std::to_string(data.size.height());
  else if (type == MessageType::MOUSE_MOVE)
    output += std::to_string(data.position.x()) + " " + std::to_string(data.position.y());
  else
    output += ::toString(data.key);
  return output;
}
