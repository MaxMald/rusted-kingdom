#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class Pathfinder;

  class PathfinderManager : public NonCopyable
  {
  public:
    PathfinderManager();
    ~PathfinderManager();

    SharedPtr<Pathfinder> getPathfinder(const String& key);
    const SharedPtr<Pathfinder> getPathfinder(const String& key) const;

    void addPathfinder(const String& key, const SharedPtr<Pathfinder>&);
    void clear();

  private:
    UnorderedMap<String, SharedPtr<Pathfinder>> m_pathfinders;
  };
}