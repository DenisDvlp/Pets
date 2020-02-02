//MessageBuffer.h
#pragma once
#include "DVector.h"
#include "IMessageReadable.h"
#include <mutex>

class MessageBuffer
  : public IMessageReadable
{
public:
  bool empty() const;
  void addMessage(Message);
  void addMessages(const DVector<Message>&);
  DVector<Message> readMessages() override;
private:
  DVector<Message> m_messages;
  mutable std::mutex m_mutex;
};