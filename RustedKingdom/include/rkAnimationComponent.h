#pragma once

#include "rkComponent.h"

namespace sf
{
  class Texture;
}

namespace rk
{
  class SpriteComponent;
  class EightDirectionsSpriteSheetAnimation;
  class EightDirectionsSpriteSheetAnimationDescription;

  class AnimationComponent : public Component
  {
  public:
    AnimationComponent(GameObject& gameObject);
    virtual ~AnimationComponent();

    void setAnimation(
      const EightDirectionsSpriteSheetAnimationDescription& description,
      const sf::Texture& texture
    );
    bool hasAnimation() const;
    bool isPlaying() const;
    void reset();
    void play();
    void stop();
    void setDirectionAngle(sf::Angle angle);

  protected:
    virtual void onUpdate(float deltaTime) override;
    void clearAnimation();

  private:
    SpriteComponent* m_spriteComponent;
    EightDirectionsSpriteSheetAnimation* m_animation;
  };
}