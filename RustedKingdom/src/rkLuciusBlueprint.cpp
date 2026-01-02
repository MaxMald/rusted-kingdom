#include "rkLuciusBlueprint.h"

#include <SFML/System/Angle.hpp>

#include "rkDependenciesLocator.h"
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
    ComponentFactoryLocator& componentFactoryLocator,
    AnimationFactory& animationFactory,
    SharedPtr<Pathfinder> pathfinder,
    SharedPtr<IPositionTransformer> positionTransform
  ) :
    GameObjectBlueprint(componentFactoryLocator),
    m_animationFactory(animationFactory),
    m_pathfinder(pathfinder),
    m_positionTransform(positionTransform)
  {
  }

  LuciusBlueprint::~LuciusBlueprint()
  {
  }

  void LuciusBlueprint::apply(GameObject& gameObject) const
  {
    SharedPtr<SpriteComponentFactory> spriteComponentFactory =
      m_componentFactoryLocator.get<SpriteComponentFactory>();

    gameObject.addComponent(
      spriteComponentFactory->createSpriteComponent(
        gameObject,
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

    gameObject.addComponent(
      MakeUnique<AnimationStateMachineComponent>(
        gameObject,
        std::move(animStateMachine)
      )
    );

    SharedPtr<RigidBodyComponentFactory> rigidBodyComponentFactory =
      m_componentFactoryLocator.get<RigidBodyComponentFactory>();

    gameObject.addComponent(
      rigidBodyComponentFactory->create(
        gameObject,
        rigidBodyType::Type::Kinematic,
        false
      )
    );

    SharedPtr<ColliderComponentFactory> colliderComponentFactory =
      m_componentFactoryLocator.get<ColliderComponentFactory>();

    UniquePtr<ColliderComponent> circleCollider =
      colliderComponentFactory->createCircle(
        gameObject,
        Vector2f(0.0f, 0.0f),
        20.0f,
        "characters"
      );
    circleCollider->setDebug(true);

    gameObject.addComponent(std::move(circleCollider));

    gameObject.addComponent(
      MakeUnique<PathfinderComponent>(gameObject, m_pathfinder)
    );
    gameObject.addComponent(
      MakeUnique<Lucius>(gameObject, m_positionTransform)
    );
    gameObject.addComponent(
      MakeUnique<LuciusAnimation>(gameObject)
    );
    gameObject.addComponent(
      MakeUnique<AgentPathMovement>(gameObject)
    );
  }
}