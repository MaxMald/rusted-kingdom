#include "scripts/rkLucius.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "rkGameObject.h"
#include "rkSpriteComponent.h"
#include "rkSteerForces.h"
#include "rkPathfinderComponent.h"
#include "rkServiceLocator.h"
#include "rkInputManager.h"

#include "scripts/rkAgentPathMovement.h"

namespace rk
{
  constexpr sf::Mouse::Button MOVEMENT_BUTTON = sf::Mouse::Button::Right;

  Lucius::Lucius(
    GameObject& gameObject,
    SharedPtr<IPositionTransformer> positionTransformer
  )
    : ScriptComponent(gameObject),
    m_positionTransformer(positionTransformer),
    m_inputManager(nullptr),
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

    m_inputManager = ServiceLocator::Instance().getService<InputManager>();
    m_inputManager->getMouseInputManager().subscribe(this);
  }

  void Lucius::onUpdate(float)
  {
    // No implementation needed
  }

  void Lucius::onDelete()
  {
    m_inputManager->getMouseInputManager().unsubscribe(this);
  }

  void Lucius::onMouseButtonPressed(const MouseButtonEvent&)
  {
    // No implementation needed
  }

  void Lucius::onMouseButtonReleased(const MouseButtonEvent& mouseEvent)
  {
    if (MOVEMENT_BUTTON != mouseEvent.getButton())
      return;

    goTo(m_inputManager->getMouseInputManager().getMousePositionWorldCoordinates());
  }
}