#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkScriptComponent.h"
#include "rkIPositionTransformer.h"
#include "scripts/rkLuciusStates.h"

namespace sf
{
  class RenderWindow;
}

using sf::Vector2f;
using sf::RenderWindow;

namespace rk
{
  class PathfinderComponent;
  class AgentPathMovement;

  class Lucius : public ScriptComponent
  {
  public:
    Lucius(
      GameObject& gameObject, 
      const RenderWindow& renderWindow,
      SharedPtr<IPositionTransformer> positionTransformer
    );
    virtual ~Lucius();

    void goTo(const Vector2f& position);

  protected:
    virtual void onCreate() override;
    virtual void onUpdate(float deltaTime) override;

  private:
    SharedPtr<IPositionTransformer> m_positionTransformer;
    PathfinderComponent* m_pathfinderComponent;
    AgentPathMovement* m_agentPathMovement;
    const RenderWindow& m_renderWindow;
    luciusStates::Type m_currentState;
  };
}