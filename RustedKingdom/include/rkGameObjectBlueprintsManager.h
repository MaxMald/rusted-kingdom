#pragma once

#include "rkIService.h"
#include "rkGameObjectBlueprint.h"

namespace rk
{
  class GameObjectBlueprintsManager : public IService
  {
  public:
    void registerBlueprint(const String& key, SharedPtr<GameObjectBlueprint>);
    SharedPtr<GameObjectBlueprint> get(const String& key);

  protected:
    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void destroy() override;

  private:
    UnorderedMap<String, SharedPtr<GameObjectBlueprint>> m_blueprints;
  };

  namespace gameObjectBlueprintKeys
  {
    const String BoxSelector = "BoxSelector";
    const String CorpoBasicSoldier = "CorpoBasicSoldier";
  }
}