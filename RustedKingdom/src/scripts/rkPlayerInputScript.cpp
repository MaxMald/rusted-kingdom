#include "scripts/rkPlayerInputScript.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "rkGameObject.h"
#include "rkSpriteComponent.h"
#include "rkSteerForces.h"
#include "rkPathfinderComponent.h"
#include "rkServiceLocator.h"
#include "rkInputManager.h"

#include "scripts/rkUnitsCommanderScript.h"

namespace rk
{
  constexpr sf::Mouse::Button MOVEMENT_BUTTON = sf::Mouse::Button::Right;

  PlayerInputScript::PlayerInputScript(GameObject& gameObject) :
    ScriptComponent(gameObject),
    m_unitsCommanderScript(nullptr),
    m_inputManager(nullptr)
  {
  }

  PlayerInputScript::~PlayerInputScript()
  {
  }

  void PlayerInputScript::onCreate()
  {
    m_inputManager = ServiceLocator::Instance().getService<InputManager>();
    m_inputManager->getMouseInputManager().subscribe(this);

    m_unitsCommanderScript = m_gameObject->getComponent<UnitsCommanderScript>();
  }

  void PlayerInputScript::onDelete()
  {
    m_inputManager->getMouseInputManager().unsubscribe(this);
  }

  void PlayerInputScript::onMouseButtonPressed(MouseButtonEvent&)
  {
  }

  void PlayerInputScript::onMouseButtonReleased(MouseButtonEvent& mouseEvent)
  {
    if (MOVEMENT_BUTTON != mouseEvent.getButton())
      return;

    m_unitsCommanderScript->moveSelectedUnitsTo(
      m_inputManager->getMouseInputManager().getMousePositionWorldCoordinates()
    );
  }
}