#pragma once

#include "rkPrerequisites.h"
#include "rkEvent.h"

namespace rk
{
  /**
   * @brief Interface for objects that want to receive events from
   * EventsManager.
   */
  class EventsManagerListener
  {
  public:
    /**
     * @brief Virtual default destructor.
     */
    virtual ~EventsManagerListener() = default;

    /**
     * @brief Called by EventsManager when an event is dispatched.
     * @param event The dispatched event to handle.
     */
    virtual void onEvent(const Event& event) = 0;
  };
}