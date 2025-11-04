#include "rkEventsManager.h"
#include <algorithm>
#include "rkEventsManagerListener.h"

namespace rk
{
  EventsManager::EventsManager() :
    m_isProcessingEvents(false),
    m_listeners(),
    m_eventQueue()
  {
  }

  EventsManager::~EventsManager()
  {
  }

  void EventsManager::addListener(EventsManagerListener* listener)
  {
    if (!listener)
      return;

    if (!listenerExists(listener))
      m_listeners.push_back(listener);
  }

  void EventsManager::removeListener(EventsManagerListener* listener)
  {
    if (!listener)
      return;

    auto it = std::remove(m_listeners.begin(), m_listeners.end(), listener);
    if (it != m_listeners.end())
      m_listeners.erase(it, m_listeners.end());
  }

  void EventsManager::queueEvent(UniquePtr<Event> event)
  {
    if (!event)
      return;

    m_eventQueue.push(std::move(event));

    if (!m_isProcessingEvents)
      processEvents();
  }

  void EventsManager::processEvents()
  {
    if (m_isProcessingEvents)
      return;

    m_isProcessingEvents = true;

    while (!m_eventQueue.empty())
    {
      UniquePtr<Event> ev = std::move(m_eventQueue.front());
      m_eventQueue.pop();

      if (!ev)
        continue;

      Vector<EventsManagerListener*> listenersCopy = m_listeners;
      for (auto* listener : listenersCopy)
      {
        if (listener)
          listener->onEvent(*ev);
      }
    }

    m_isProcessingEvents = false;
  }

  Bool EventsManager::listenerExists(EventsManagerListener* listener) const
  {
    return std::find(m_listeners.begin(), m_listeners.end(), listener) 
      != m_listeners.end();
  }
}