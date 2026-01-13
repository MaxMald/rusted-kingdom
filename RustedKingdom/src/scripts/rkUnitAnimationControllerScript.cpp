#include "scripts/rkUnitAnimationControllerScript.h"

#include "rkGameObject.h"
#include "rkRigidBodyComponent.h"
#include "rkAnimationStateMachineComponent.h"
#include "rkBlackboard.h"

using sf::Vector2f;

namespace rk
{
  UnitAnimationControllerScript::UnitAnimationControllerScript(GameObject& gameObject)
    : ScriptComponent(gameObject),
    m_animationComponent(nullptr),
    m_rigidBodyComponent(nullptr)
  {
  }

  UnitAnimationControllerScript::~UnitAnimationControllerScript()
  {
  }

  void UnitAnimationControllerScript::onCreate()
  {
    m_animationComponent = m_gameObject->getComponent<AnimationStateMachineComponent>();
    m_rigidBodyComponent = m_gameObject->getComponent<RigidBodyComponent>();
  }

  void UnitAnimationControllerScript::onUpdate(float)
  {
    Vector2f velocity = m_rigidBodyComponent->getVelocity();

    m_animationComponent->getBlackboard()
      .getFloatValues()
      .setValue("luciusSpeed", velocity.length() / 100.0f);

    m_animationComponent->getBlackboard()
      .getFloatValues()
      .setValue("speedModifier", velocity.length() / 100.0f);

    Angle direcitonAngle = sf::radians(0.0f);
    if (velocity.lengthSquared() > 0.001f)
      direcitonAngle = velocity.angle();

    m_animationComponent->getBlackboard()
      .getAngleValues()
      .setValue("directionAngle", direcitonAngle);
  }
}