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
#include "rkColliderComponentFactory.h"
#include "rkColliderComponent.h"
#include "rkPathfinderComponent.h"

#include "scripts/rkLucius.h"
#include "scripts/rkLuciusAnimation.h"
#include "scripts/rkAgentPathMovement.h"

using sf::IntRect;
using sf::Vector2i;

namespace rk
{
  LuciusBlueprint::LuciusBlueprint(
    GameObjectBuilder& gameObjectBuilder, 
    SpriteComponentFactory& spriteComponentFactory, 
    AnimationFactory& animationFactory,
    RigidBodyComponentFactory& rigidBodyComponentFactory,
    ColliderComponentFactory& colliderComponentFactory,
    SharedPtr<Pathfinder> pathfinder,
    const IsometricPositionTransformer isometricPositionTransformer,
    const RenderWindow& renderWindow
  ) :
    m_gameObjectBuilder(gameObjectBuilder),
    m_spriteComponentFactory(spriteComponentFactory),
    m_animationFactory(animationFactory),
    m_rigidBodyComponentFactory(rigidBodyComponentFactory),
    m_colliderComponentFactory(colliderComponentFactory),
    m_pathfinder(pathfinder),
    m_isometricPositionTransformer(isometricPositionTransformer),
    m_renderWindow(renderWindow)
  {
  }

  LuciusBlueprint::~LuciusBlueprint()
  {
  }

  GameObject* LuciusBlueprint::instantiate(const String& name, GameObject& parent) const
  {
    GameObject* lucius = m_gameObjectBuilder
      .createGameObject(name)
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
      m_rigidBodyComponentFactory.create(
        *lucius,
        rigidBodyType::Type::Kinematic,
        false
      )
    );

    UniquePtr<ColliderComponent> circleCollider =
      m_colliderComponentFactory.createCircle(
        *lucius,
        Vector2f(0.0f, 0.0f),
        20.0f,
        "characters"
      );
    circleCollider->setDebug(true);

    lucius->addComponent(std::move(circleCollider));

    lucius->addComponent(
      MakeUnique<PathfinderComponent>(*lucius, m_pathfinder)
    );
    lucius->addComponent(
      MakeUnique<Lucius>(*lucius, m_renderWindow, m_isometricPositionTransformer)
    );
    lucius->addComponent(
      MakeUnique<LuciusAnimation>(*lucius)
    );
    lucius->addComponent(
      MakeUnique<AgentPathMovement>(*lucius)
    );

    return lucius;
  }
}