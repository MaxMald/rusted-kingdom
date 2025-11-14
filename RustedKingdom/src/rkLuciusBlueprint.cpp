#include "rkLuciusBlueprint.h"

#include <SFML/System/Angle.hpp>

#include "rkGameObjectBuilder.h"
#include "rkAnimationStateMachineBuilder.h"
#include "rkSpriteComponentFactory.h"
#include "rkSpriteComponent.h"
#include "rkAnimationStateMachineComponent.h"
#include "rkAnimationStateMachine.h"
#include "rkRigidBodyComponent.h"
#include "rkRigidBodyComponentFactory.h"
#include "scripts/rkLucius.h"

using sf::IntRect;
using sf::Vector2i;

namespace rk
{
  LuciusBlueprint::LuciusBlueprint(
    GameObjectBuilder& gameObjectBuilder, 
    SpriteComponentFactory& spriteComponentFactory, 
    AnimationFactory& animationFactory,
    RigidBodyComponentFactory& rigidBodyComponentFactory,
    const RenderWindow& renderWindow
  ) :
    m_gameObjectBuilder(gameObjectBuilder),
    m_spriteComponentFactory(spriteComponentFactory),
    m_animationFactory(animationFactory),
    m_rigidBodyComponentFactory(rigidBodyComponentFactory),
    m_renderWindow(renderWindow)
  {
  }

  LuciusBlueprint::~LuciusBlueprint()
  {
  }

  GameObject* LuciusBlueprint::instantiate(GameObject& parent)
  {
    GameObject* lucius = m_gameObjectBuilder
      .createGameObject("lucius")
      .buildWithParent(parent);

    lucius->addComponent(
      m_spriteComponentFactory.createSpriteComponent(
        *lucius,
        "lucius-walking",
        IntRect(Vector2i(0, 0), Vector2i(100, 100))
      )
    );

    AnimationStateMachineBuilder animBuilder(m_animationFactory);
    UniquePtr<AnimationStateMachine> animStateMachine = animBuilder
      .createStateMachine("idle")
      .withFloat("luciusSpeed", 0.0f)
      .withAngle("directionAngle", sf::radians(0.0f))
      .withFloat("speedModifierKey", 1.0f)
      .withEightDirectionAnimationState("idle", "lucius-idle-anim")
      .withEightDirectionAnimationState("walking", "lucius-walking-anim")
      .withEightDirectionAnimationState("running", "lucius-running-anim")
      .withFloatComparisonTransition("idle", "walking", 0.01f, logicalComparisonType::Less, "luciusSpeed")
      .withFloatComparisonTransition("walking", "running", 0.5f, logicalComparisonType::Less, "luciusSpeed")
      .withFloatComparisonTransition("walking", "idle", 0.01f, logicalComparisonType::GreaterEqual, "luciusSpeed")
      .withFloatComparisonTransition("running", "walking", 0.5f, logicalComparisonType::GreaterEqual, "luciusSpeed")
      .build();

    lucius->addComponent(
      MakeUnique<AnimationStateMachineComponent>(
        *lucius,
        std::move(animStateMachine)
      )
    );

    lucius->addComponent(
      m_rigidBodyComponentFactory.createWithCircleCollider(
        *lucius,
        rigidBodyType::Type::Kinematic,
        Vector2f(0.0f, 0.0f),
        40.0f
      )
    );

    lucius->addComponent(
      MakeUnique<Lucius>(*lucius, m_renderWindow)
    );

    return lucius;
  }
}