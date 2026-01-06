#pragma once

#include "rkPrerequisites.h"
#include "rkIService.h"

namespace rk
{
  class Pathfinder;

  class PathfinderManager : public IService
  {
  public:
    PathfinderManager();
    virtual ~PathfinderManager();

    SharedPtr<Pathfinder> getPathfinder(const String& key);
    const SharedPtr<Pathfinder> getPathfinder(const String& key) const;
    const UnorderedMap<String, SharedPtr<Pathfinder>>& getAllPathfinders() const;

    void addPathfinder(const String& key, const SharedPtr<Pathfinder>&);
    void clear();

  protected:
    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void destroy() override;

  private:
    UnorderedMap<String, SharedPtr<Pathfinder>> m_pathfinders;
  };
}