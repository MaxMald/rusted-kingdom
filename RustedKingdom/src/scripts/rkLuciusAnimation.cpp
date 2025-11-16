#include "scripts/rkLuciusAnimation.h"
#include "rkGameObject.h"
#include "rkRigidBodyComponent.h"
#include "rkAnimationStateMachineComponent.h"
#include "rkBlackboard.h"

using sf::Vector2f;

namespace rk
{
  LuciusAnimation::LuciusAnimation(GameObject& gameObject)
    : ScriptComponent(gameObject, "lucius-animation"),
    m_animationComponent(nullptr),
    m_rigidBodyComponent(nullptr)
  {
  }

  LuciusAnimation::~LuciusAnimation()
  {
  }

  void LuciusAnimation::onCreate()
  {
    m_animationComponent = m_gameObject
      ->getComponentOrFail<AnimationStateMachineComponent>(rk::componentType::Animation);
    m_rigidBodyComponent = m_gameObject
      ->getComponentOrFail<RigidBodyComponent>(rk::componentType::RigidBody);
  }

  void LuciusAnimation::onUpdate(float deltaTime)
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