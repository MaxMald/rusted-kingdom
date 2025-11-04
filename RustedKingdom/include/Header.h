#pragma once

#include "rkEventType.h"

namespace rk
{
  class Event
  {
  public:
    
    Event(EventType::Type type) : m_type(type) {}
    virtual ~Event() = default;

    const EventType::Type& getType() const
    {
      return m_type;
    }

  private:
    EventType::Type m_type;
  };
}