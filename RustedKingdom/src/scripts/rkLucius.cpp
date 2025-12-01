#include "scripts/rkLucius.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "rkGameObject.h"
#include "rkSpriteComponent.h"
#include "rkSteerForces.h"
#include "rkPathfinderComponent.h"

#include "scripts/rkAgentPathMovement.h"

namespace rk
{
  Lucius::Lucius(
    GameObject& gameObject, 
    const RenderWindow& renderWindow,
    SharedPtr<IPositionTransformer> positionTransformer
  )
    : ScriptComponent(gameObject),
    m_positionTransformer(positionTransformer),
    m_renderWindow(renderWindow),
    m_agentPathMovement(nullptr),
    m_pathfinderComponent(nullptr),
    m_currentState(luciusStates::Type::Idle)
  {
  }

  Lucius::~Lucius()
  {
  }

  void Lucius::goTo(const Vector2f& position)
  {
    Vector2f startIso = m_positionTransformer->transform(
      m_gameObject->getPosition()
    );

    Vector2f endIso = m_positionTransformer->transform(
      position
    );

    Vector<Vector2f> path = m_pathfinderComponent->findPath(startIso, endIso);

    if (path.empty())
      return;

    for (Vector2f& pathPoint : path)
      pathPoint = m_positionTransformer->inverseTransform(pathPoint);

    m_agentPathMovement->start(path);
  }

  void Lucius::onCreate()
  {
    SpriteComponent* spriteComponent = m_gameObject->getComponent<SpriteComponent>();
    sf::Vector2f spriteOrigin(50.0f, 80.0f);
    spriteComponent->setOrigin(spriteOrigin);

    m_pathfinderComponent = m_gameObject->getComponent<PathfinderComponent>();
    m_agentPathMovement = m_gameObject->getComponent<AgentPathMovement>();
    m_agentPathMovement->setSpeed(100.0f);
  }

  void Lucius::onUpdate(float)
  {
    // Check for left mouse button press
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
      // Get mouse position in window coordinates
      sf::Vector2i mousePixelPos = sf::Mouse::getPosition(m_renderWindow);

      // Convert to world coordinates using the window's current view
      sf::Vector2f mouseWorldPos = m_renderWindow.mapPixelToCoords(mousePixelPos);

      // Call goTo with the world position
      goTo(mouseWorldPos);
    }
  }
}