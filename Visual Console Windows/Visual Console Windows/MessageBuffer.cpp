//MessageBuffer.cpp
#include "MessageBuffer.h"

bool MessageBuffer::empty() const
{
  std::lock_guard<std::mutex> guard(m_mutex);
  return m_messages.empty();
}

void MessageBuffer::addMessage(Message message)
{
  std::lock_guard<std::mutex> guard(m_mutex);
  m_messages.push(message);
}

void MessageBuffer::addMessages(const DVector<Message>& messages)
{
  std::lock_guard<std::mutex> guard(m_mutex);
  m_messages.push(messages);
}

DVector<Message> MessageBuffer::readMessages()
{
  std::lock_guard<std::mutex> guard(m_mutex);
  return std::move(m_messages);
}
