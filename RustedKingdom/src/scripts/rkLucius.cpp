#include "scripts/rkLucius.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "rkGameObject.h"
#include "rkAnimationStateMachineComponent.h"
#include "rkBlackboard.h"
#include "rkSpriteComponent.h"
#include "rkSteerForces.h"
#include "rkRigidBodyComponent.h"

namespace rk
{
  Lucius::Lucius(GameObject& gameObject, const RenderWindow& renderWindow)
    : ScriptComponent(gameObject, "lucius"),
    m_currentVelocity(0.0f, 0.0f),
    m_animationComponent(nullptr),
    m_rigidBodyComponent(nullptr),
    m_renderWindow(renderWindow)
  {
    m_animationComponent = gameObject
      .getComponent<AnimationStateMachineComponent>(rk::componentType::Animation);

    if (m_animationComponent == nullptr)
    {
      throw RuntimeErrorException(
        "Lucius script component requires an Animation component to be present in"
        "the same GameObject."
      );
    }

    if (gameObject.hasComponent(rk::componentType::Sprite))
    {
      SpriteComponent* spriteComponent = gameObject
        .getComponent<SpriteComponent>(rk::componentType::Sprite);

      sf::Vector2f spriteOrigin(50.0f, 100.0f);

      spriteComponent->setOrigin(spriteOrigin);
    }

    m_rigidBodyComponent = gameObject
      .getComponent<RigidBodyComponent>(rk::componentType::RigidBody);

    if (m_rigidBodyComponent == nullptr)
    {
      throw RuntimeErrorException(
        "Lucius script component requires a RigidBody component to be present in"
        "the same GameObject."
      );
    }
  }

  Lucius::~Lucius()
  {
  }

  void Lucius::onUpdate(float deltaTime)
  {
    (void)deltaTime;

    const float maxSpeed = 100.0f;
    const float mass = 200.0f;

    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_renderWindow);
    Vector2f target = m_renderWindow.mapPixelToCoords(mousePosition);

    Vector2f seekForce = steerForces::seek(
      m_gameObject->getPosition(),
      target,
      m_currentVelocity,
      maxSpeed
    );

    if (seekForce.length() > 0.0f)
      seekForce = seekForce / mass;

    m_currentVelocity = vector2Utilities::truncated(
      m_currentVelocity + seekForce,
      maxSpeed
    );
    m_rigidBodyComponent->setVelocity(m_currentVelocity);

    updateAnimationStateMachine();
  }

  void Lucius::updateAnimationStateMachine()
  {
    Vector2f velocity = m_rigidBodyComponent->getVelocity();

    m_animationComponent->getBlackboard()
      .getFloatValues()
      .setValue("luciusSpeed", velocity.length() / 100.0f);

    m_animationComponent->getBlackboard()
      .getAngleValues()
      .setValue("directionAngle", velocity.angle());

    m_animationComponent->getBlackboard()
      .getFloatValues()
      .setValue("speedModifier", velocity.length() / 100.0f);
  }
}