#include "rkGameObjectBlueprintsManager.h"

#include "rkBoxSelectorBlueprint.h"
#include "rkCorpoBasicSoldierBlueprint.h"

namespace rk
{
  void GameObjectBlueprintsManager::registerBlueprint(
    const String& key,
    SharedPtr<GameObjectBlueprint> gameObjectBlueprint
  )
  {
    m_blueprints[key] = gameObjectBlueprint;
  }

  SharedPtr<GameObjectBlueprint> GameObjectBlueprintsManager::get(const String& key)
  {
    auto it = m_blueprints.find(key);
    if (it != m_blueprints.end()) {
      return it->second;
    }

    throw RuntimeErrorException(
      String::Format("GameObjectBlueprint with key %s not found", key.c_str())
    );
  }

  void GameObjectBlueprintsManager::init(ServiceLocator&)
  {
    registerBlueprint(gameObjectBlueprintKeys::BoxSelector, MakeShared<BoxSelectorBlueprint>());
    registerBlueprint(gameObjectBlueprintKeys::CorpoBasicSoldier, MakeShared<CorpoBasicSoldierBlueprint>());
  }

  void GameObjectBlueprintsManager::destroy()
  {
    m_blueprints.clear();
  }
}