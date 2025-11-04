#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class EventsManagerListener;
  class Event;

  /**
   * @brief Centralized event dispatcher.
   */
  class EventsManager
  {
    public:

    /**
     * @brief Construct a new EventsManager.
     */
    EventsManager();

    /**
     * @brief Destroy the EventsManager.
     */
    ~EventsManager();

    /**
     * @brief Register a listener to receive events.
     * @param listener Pointer to an EventsManagerListener to register.
     */
    void addListener(EventsManagerListener* listener);

    /**
     * @brief Unregister a previously registered listener.
     * @param listener Pointer to the listener to remove.
     */
    void removeListener(EventsManagerListener* listener);

    /**
     * @brief Queue an event for later processing.
     *
     * The manager takes ownership of the provided event via `UniquePtr`.
     * Events are processed in queue order when `processEvents()` runs.
     *
     * @param event UniquePtr to the Event to enqueue (moved).
     */
    void queueEvent(UniquePtr<Event> event);

  private:
    Vector<EventsManagerListener*> m_listeners;
    Queue<UniquePtr<Event>> m_eventQueue;
    Bool m_isProcessingEvents;

    /**
     * @brief Process and dispatch all queued events to registered listeners.
     */
    void processEvents();

    /**
     * @brief Check whether a listener is already registered.
     */
    Bool listenerExists(EventsManagerListener* listener) const;
  };
}