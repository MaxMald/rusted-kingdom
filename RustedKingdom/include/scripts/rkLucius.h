#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkScriptComponent.h"

namespace sf
{
  class RenderWindow;
}

using sf::Vector2f;
using sf::RenderWindow;

namespace rk
{
  class AnimationComponent;

  class Lucius : public ScriptComponent
  {
  public:
    Lucius(GameObject& gameObject, const RenderWindow& renderWindow);
    virtual ~Lucius();

  private:
    AnimationComponent* m_animationComponent;
    const RenderWindow* m_renderWindow;
    Vector2f m_currentVelocity;

    virtual void onUpdate(float deltaTime) override;
  };
}