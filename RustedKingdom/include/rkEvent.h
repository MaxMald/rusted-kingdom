#pragma once

#include "rkEventType.h"

namespace rk
{
  /**
   * @brief Base class for events used by the event system.
   */
  class Event
  {
  public:
    /**
     * @brief Construct an Event with the given type.
     * @param type The event type that identifies this event.
     */
    Event(EventType::Type type) : m_type(type) {}

    /**
     * @brief Virtual destructor to allow safe polymorphic deletion.
     */
    virtual ~Event() = default;

    /**
     * @brief Retrieve the event type identifier.
     * @return The event type.
     */
    EventType::Type getType() const
    {
      return m_type;
    }

  private:
    EventType::Type m_type; ///< Identifier describing the concrete event kind.
  };
}