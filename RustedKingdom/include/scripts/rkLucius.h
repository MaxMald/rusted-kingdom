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
  class AnimationStateMachineComponent;
  class RigidBodyComponent;

  class Lucius : public ScriptComponent
  {
  public:
    Lucius(GameObject& gameObject, const RenderWindow& renderWindow);
    virtual ~Lucius();

  protected:
    virtual void onUpdate(float deltaTime) override;

  private:
    AnimationStateMachineComponent* m_animationComponent;
    RigidBodyComponent* m_rigidBodyComponent;
    const RenderWindow& m_renderWindow;
    Vector2f m_currentVelocity;

    void updateAnimationStateMachine();
  };
}