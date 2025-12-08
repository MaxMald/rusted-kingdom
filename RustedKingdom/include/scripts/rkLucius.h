#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkScriptComponent.h"
#include "rkIPositionTransformer.h"
#include "rkIMouseInputManagerListener.h"
#include "scripts/rkLuciusStates.h"

using sf::Vector2f;

namespace rk
{
  class InputManager;
  class PathfinderComponent;
  class AgentPathMovement;

  class Lucius : public ScriptComponent, IMouseInputManagerListener
  {
  public:
    Lucius(
      GameObject& gameObject,
      SharedPtr<IPositionTransformer> positionTransformer
    );
    virtual ~Lucius();

    void goTo(const Vector2f& position);

  protected:
    virtual void onCreate() override;
    virtual void onUpdate(float deltaTime) override;
    virtual void onDelete() override;

    virtual void onMouseButtonPressed(MouseButtonEvent&);
    virtual void onMouseButtonReleased(MouseButtonEvent&);

  private:
    SharedPtr<InputManager> m_inputManager;
    SharedPtr<IPositionTransformer> m_positionTransformer;
    PathfinderComponent* m_pathfinderComponent;
    AgentPathMovement* m_agentPathMovement;
    luciusStates::Type m_currentState;
  };
}