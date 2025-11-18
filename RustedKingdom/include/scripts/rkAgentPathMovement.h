#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkScriptComponent.h"

using sf::Vector2f;

namespace rk
{
  class RigidBodyComponent;
  class ColliderComponent;

  class AgentPathMovement : public ScriptComponent
  {
  public:
    AgentPathMovement(GameObject& gameObject);
    virtual ~AgentPathMovement();

    bool isMoving() const { return m_isMoving; }
    float getSpeed() const { return m_speed; }
    void setSpeed(float speed) { m_speed = speed; }

    void start(const Vector<Vector2f>& pathPoints);
    void stop();

  protected:
    virtual void onCreate() override;
    virtual void onUpdate(float deltaTime) override;
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:
    RigidBodyComponent* m_rigidBodyComponent;
    ColliderComponent* m_colliderComponent;
    Vector<Vector2f> m_pathPoints;
    SizeT m_currentPathPointIndex;
    bool m_isMoving;
    float m_speed;
  };
}