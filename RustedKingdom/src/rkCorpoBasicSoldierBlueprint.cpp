#include "rkCorpoBasicSoldierBlueprint.h"

#include <SFML/System/Angle.hpp>

#include "rkGameObject.h"
#include "rkSpriteComponent.h"
#include "rkServiceLocator.h"
#include "rkSpriteComponentFactory.h"
#include "rkAssetManager.h"
#include "rkAnimationStateMachineComponent.h"
#include "rkAnimationStateMachineBuilder.h"
#include "rkRigidBodyComponent.h"
#include "rkRigidBodyComponentFactory.h"
#include "rkColliderComponent.h"
#include "rkColliderComponentFactory.h"

#include "scripts/rkAgentPathMovement.h"

using sf::IntRect;
using sf::Vector2i;

namespace rk
{
  CorpoBasicSoldierBlueprint::CorpoBasicSoldierBlueprint()
  {
  }

  CorpoBasicSoldierBlueprint::~CorpoBasicSoldierBlueprint()
  {
  }

  void CorpoBasicSoldierBlueprint::apply(GameObject& gameObject) const
  {
    gameObject.addComponent(
      spriteComponentFactory::createSpriteComponent(
        gameObject,
        "lucius-walking",
        IntRect(Vector2i(0, 0), Vector2i(100, 100))
      )
    );

    AnimationStateMachineBuilder animBuilder;
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

    gameObject.addComponent(
      MakeUnique<AnimationStateMachineComponent>(
        gameObject,
        std::move(animStateMachine)
      )
    );

    gameObject.addComponent(
      rigidBodyComponentFactory::create(
        gameObject,
        rigidBodyType::Type::Kinematic,
        false
      )
    );

    UniquePtr<ColliderComponent> circleCollider =
      colliderComponentFactory::createCircle(
        gameObject,
        Vector2f(0.0f, 0.0f),
        20.0f,
        "characters"
      );

    gameObject.addComponent(std::move(circleCollider));
    gameObject.addComponent(MakeUnique<AgentPathMovement>(gameObject));
  }
}