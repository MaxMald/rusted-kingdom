#include "scripts/rkAgentPathMovement.h"

#include <SFML/Graphics/VertexArray.hpp>

#include "rkGameObject.h"
#include "rkRigidBodyComponent.h"
#include "rkCollider.h"

namespace rk
{
  AgentPathMovement::AgentPathMovement(GameObject& gameObject)
    : ScriptComponent(gameObject, "agent-path-movement"),
    m_rigidBodyComponent(nullptr),
    m_currentPathPointIndex(0),
    m_isMoving(false),
    m_speed(0.0f)
  {
  }

  AgentPathMovement::~AgentPathMovement()
  {
  }

  void AgentPathMovement::start(const Vector<Vector2f>& pathPoints)
  {
    if (m_isMoving)
      stop();

    m_pathPoints = pathPoints;
    m_currentPathPointIndex = 0;
    m_isMoving = true;
  }

  void AgentPathMovement::stop()
  {
    m_pathPoints.clear();
    m_currentPathPointIndex = 0;
    m_rigidBodyComponent->setVelocity(Vector2f(0.0f, 0.0f));
    m_isMoving = false;
  }

  void AgentPathMovement::onCreate()
  {
    m_rigidBodyComponent = m_gameObject
      ->getComponentOrFail<RigidBodyComponent>(componentType::Type::RigidBody);
  }

  void AgentPathMovement::onUpdate(float)
  {
    if (!m_isMoving)
      return;

    if (m_pathPoints.empty())
      return;

    Vector2f targetPosition = m_pathPoints[m_currentPathPointIndex];
    if (false /* check collision */)
    {
      m_currentPathPointIndex++;
      if (m_currentPathPointIndex >= m_pathPoints.size())
      {
        stop();
        return;
      }

      targetPosition = m_pathPoints[m_currentPathPointIndex];
    }

    Vector2f currentPosition = m_gameObject->getPosition();
    Vector2f direction = (targetPosition - currentPosition).normalized();
    m_rigidBodyComponent->setVelocity(direction * m_speed);
  }

  void AgentPathMovement::onDraw(
    sf::RenderTarget& target,
    sf::RenderStates
  ) const
  {
    if (m_pathPoints.size() < 2)
      return;

    sf::VertexArray lines(sf::PrimitiveType::LineStrip, m_pathPoints.size());
    for (SizeT i = 0; i < m_pathPoints.size(); ++i)
    {
      lines[i].position = m_pathPoints[i];
      lines[i].color = sf::Color::Green;
    }
    target.draw(lines);
  }
}