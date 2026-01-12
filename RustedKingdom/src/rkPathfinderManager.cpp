#include "rkPathfinderManager.h"
#include "rkPathfinder.h"

namespace rk
{
  PathfinderManager::PathfinderManager()
  {
  }

  PathfinderManager::~PathfinderManager()
  {
    clear();
  }

  SharedPtr<Pathfinder> PathfinderManager::getPathfinder(
    const String& key
  )
  {
    auto it = m_pathfinders.find(key);
    if (it != m_pathfinders.end())
      return it->second;

    throw RuntimeErrorException(
      String::Format(
        "PathfinderManager::getPathfinder: Pathfinder with key '%s' not found.",
        key.c_str()
      )
    );
  }

  const SharedPtr<Pathfinder> PathfinderManager::getPathfinder(
    const String& key
  ) const
  {
    auto it = m_pathfinders.find(key);
    if (it != m_pathfinders.end())
      return it->second;

    throw RuntimeErrorException(
      String::Format(
        "PathfinderManager::getPathfinder: Pathfinder with key '%s' not found.",
        key.c_str()
      )
    );
  }

  const UnorderedMap<String, SharedPtr<Pathfinder>>& PathfinderManager::getAllPathfinders() const
  {
    return m_pathfinders;
  }

  SharedPtr<Pathfinder> PathfinderManager::createPathfinder(const String& key)
  {
    SharedPtr<Pathfinder> pathfinder = MakeShared<Pathfinder>();
    m_pathfinders[key] = pathfinder;
    return pathfinder;
  }

  void PathfinderManager::addPathfinder(
    const String& key,
    const SharedPtr<Pathfinder>& pathfinder
  )
  {
    m_pathfinders[key] = pathfinder;
  }

  void PathfinderManager::clear()
  {
    m_pathfinders.clear();
  }

  void PathfinderManager::init(ServiceLocator&)
  {
  }

  void PathfinderManager::destroy()
  {
  }
}