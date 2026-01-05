#include "rkBlueprintClassApplier.h"

#include <SFML/System/Vector2.hpp>
#include <TMR/tmrObject.h>

#include "rkGameObject.h"
#include "rkGameObjectBlueprint.h"

using sf::Vector2f;

namespace rk
{
  BlueprintClassApplier::BlueprintClassApplier(
    SharedPtr<GameObjectBlueprint> gameObjectBlueprint
  ) : m_gameObjectBlueprint(gameObjectBlueprint)
  {
  }

  BlueprintClassApplier::~BlueprintClassApplier()
  {
  }

  void BlueprintClassApplier::apply(
    GameObject& gameObject,
    const tmr::Object* tmrObject,
    const tmr::TiledMap*
  )
  {
    if (!m_gameObjectBlueprint)
      return;

    m_gameObjectBlueprint->apply(gameObject);

    initPosition(gameObject, tmrObject);
    initProperties(gameObject, tmrObject);
  }

  void BlueprintClassApplier::initProperties(GameObject&, const tmr::Object*)
  {
    // implement in derived classes if needed
  }

  void BlueprintClassApplier::initPosition(
    GameObject& gameObject,
    const tmr::Object* tmrObject
  )
  {
    if (tmrObject)
      gameObject.setPosition(Vector2f(tmrObject->getX(), tmrObject->getY()));
  }
}