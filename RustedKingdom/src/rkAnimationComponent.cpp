#include "rkAnimationComponent.h"
#include "rkGameObject.h"
#include "rkEightDirectionsSpriteSheetAnimation.h"
#include "rkSpriteComponent.h"

namespace rk
{
  AnimationComponent::AnimationComponent(GameObject& gameObject) :
    Component(gameObject, componentType::Type::Animation),
    m_spriteComponent(nullptr),
    m_animation(nullptr)
  {
    if (!gameObject.hasComponent(componentType::Type::Sprite))
    {
      throw RuntimeErrorException(
        "AnimationComponent error: Associated GameObject does not have a "
        "SpriteComponent."
      );
    }

    m_spriteComponent = gameObject.getComponent<SpriteComponent>(
      componentType::Type::Sprite
    );
  }

  AnimationComponent::~AnimationComponent()
  {
    clearAnimation();
  }

  void AnimationComponent::setAnimation(
    const EightDirectionsSpriteSheetAnimationDescription& description,
    const sf::Texture& texture
  )
  {
    clearAnimation();

    m_animation = new EightDirectionsSpriteSheetAnimation(
      description,
      texture,
      m_spriteComponent->getSprite()
    );
  }

  bool AnimationComponent::hasAnimation() const
  {
    return m_animation != nullptr;
  }

  bool AnimationComponent::isPlaying() const
  {
    if (m_animation)
      return m_animation->isPlaying();
    return false;
  }

  void AnimationComponent::reset()
  {
    if (m_animation)
      m_animation->reset();
  }

  void AnimationComponent::play()
  {
    if (m_animation)
      m_animation->play();
  }

  void AnimationComponent::stop()
  {
    if (m_animation)
      m_animation->stop();
  }

  void AnimationComponent::setDirectionAngle(sf::Angle angle)
  {
    if (m_animation)
      m_animation->setDirectionAngle(angle);
  }

  void AnimationComponent::onUpdate(float deltaTime)
  {
    if (m_animation)
      m_animation->update(deltaTime);
  }

  void AnimationComponent::clearAnimation()
  {
    if (m_animation)
    {
      delete m_animation;
      m_animation = nullptr;
    }
  }
}