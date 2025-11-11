#include "scripts/rkLucius.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "rkGameObject.h"
#include "rkAnimationComponent.h"
#include "rkSpriteComponent.h"

namespace rk
{
  Lucius::Lucius(GameObject& gameObject, const RenderWindow& renderWindow)
    : ScriptComponent(gameObject, "lucius"),
    m_animationComponent(nullptr),
    m_currentVelocity(0.0f, 0.0f),
    m_renderWindow(&renderWindow)
  {
    if (!gameObject.hasComponent(rk::componentType::Animation))
    {
      throw RuntimeErrorException(
        "Lucius script component requires an Animation component to be present in"
        "the same GameObject."
      );
    }

    m_animationComponent = gameObject
      .getComponent<AnimationComponent>(rk::componentType::Animation);
    m_animationComponent->play();

    if (gameObject.hasComponent(rk::componentType::Sprite))
    {
      SpriteComponent* spriteComponent = gameObject
        .getComponent<SpriteComponent>(rk::componentType::Sprite);

      sf::Vector2i frameSize = m_animationComponent->getFrameSize();
      sf::Vector2f spriteOrigin(
        frameSize.x * 0.5f,
        frameSize.y
      );

      spriteComponent->setOrigin(spriteOrigin);
    }
  }

  Lucius::~Lucius()
  {
  }

  void Lucius::onUpdate(float deltaTime)
  {
    const float maxSpeed = 100.0f;
    const float mass = 500.0f;

    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_renderWindow);
    Vector2f target = m_renderWindow->mapPixelToCoords(mousePosition);

    Vector2f desiredVelocity = target - m_gameObject->getPosition();
    desiredVelocity = desiredVelocity.normalized() * maxSpeed;

    Vector2f steering = desiredVelocity - m_currentVelocity;
    if (steering.length() > 0.0f)
      steering = steering.normalized() * maxSpeed;
    steering = steering / mass;

    m_currentVelocity = m_currentVelocity + steering;
    if (m_currentVelocity.length() > maxSpeed) // truncate
      m_currentVelocity = m_currentVelocity.normalized() * maxSpeed;

    m_gameObject->setPosition(
      m_gameObject->getPosition() + m_currentVelocity * deltaTime
    );

    // Update animation based on velocity
    m_animationComponent->setDirectionAngle(m_currentVelocity.angle());

    float speedModifier = m_currentVelocity.length() / maxSpeed;
    m_animationComponent->setSpeedModifier(speedModifier);
  }
}