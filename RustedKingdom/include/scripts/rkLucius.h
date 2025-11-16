#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkScriptComponent.h"
#include "rkIsometricPositionTransformer.h"
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
      const IsometricPositionTransformer isometricPositionTransformer
    );
    virtual ~Lucius();

    void goTo(const Vector2f& position);

  protected:
    virtual void onCreate() override;
    virtual void onUpdate(float deltaTime) override;

  private:
    IsometricPositionTransformer m_isometricPositionTransformer;
    PathfinderComponent* m_pathfinderComponent;
    AgentPathMovement* m_agentPathMovement;
    const RenderWindow& m_renderWindow;
    luciusStates::Type m_currentState;
  };
}