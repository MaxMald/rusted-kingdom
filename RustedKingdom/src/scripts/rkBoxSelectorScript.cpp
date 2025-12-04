#include "scripts/rkBoxSelectorScript.h"

#include "rkServiceLocator.h"
#include "rkInputManager.h"
#include "rkMouseInputManager.h"

namespace rk
{
  const sf::Mouse::Button SELECTION_BUTTON = sf::Mouse::Button::Left;

  BoxSelectorScript::BoxSelectorScript(GameObject& gameObject): 
    ScriptComponent(gameObject),
    m_boxP1(0.f, 0.f),
    m_boxP2(0.f, 0.f),
    m_boxShape(),
    m_isSelecting(false),
    m_inputManager(nullptr),
    m_borderColor(sf::Color::Green),
    m_fillColor(sf::Color::Green),
    m_borderThickness(2.f)
  {
  }

  BoxSelectorScript::~BoxSelectorScript()
  {
  }

  void BoxSelectorScript::setBorderColor(const sf::Color& color)
  {
    m_borderColor = color;
  }

  void BoxSelectorScript::setFillColor(const sf::Color& color)
  {
    m_fillColor = color;
  }

  void BoxSelectorScript::setBorderThickness(float thickness)
  {
    m_borderThickness = thickness;
  }

  void BoxSelectorScript::onCreate()
  {
    m_inputManager = ServiceLocator::Instance().getService<InputManager>();
    m_inputManager->getMouseInputManager().subscribe(this);
  }

  void BoxSelectorScript::onUpdate(float deltaTime)
  {
    if (!m_isSelecting)
      return;

    updateBoxP2();
    updateBoxShape();
  }

  void BoxSelectorScript::onDraw(RenderTarget& renderTarget, RenderStates states) const
  {
    if(!m_isSelecting)
      return;

    renderTarget.draw(m_boxShape, states);
  }

  void BoxSelectorScript::onDelete()
  {
    m_inputManager->getMouseInputManager().unsubscribe(this);
  }

  void BoxSelectorScript::onMouseButtonPressed(
    const MouseButtonEvent& mouseEvent
  )
  {
    if (mouseEvent.getButton() != SELECTION_BUTTON || m_isSelecting)
      return;

    m_isSelecting = true;
    
    m_boxP1 = m_inputManager->getMouseInputManager()
      .getMousePositionWorldCoordinates();
  }

  void BoxSelectorScript::onMouseButtonReleased(
    const MouseButtonEvent& mouseEvent
  )
  {
    if (mouseEvent.getButton() != SELECTION_BUTTON || !m_isSelecting)
      return;

    m_isSelecting = false;
  }
  void BoxSelectorScript::updateBoxP2()
  {
    m_boxP2 = m_inputManager->getMouseInputManager()
      .getMousePositionWorldCoordinates();
  }

  void BoxSelectorScript::updateBoxShape()
  {
    Vector2f topLeft(
      std::min(m_boxP1.x, m_boxP2.x),
      std::min(m_boxP1.y, m_boxP2.y)
    );

    Vector2f size(
      std::abs(m_boxP2.x - m_boxP1.x),
      std::abs(m_boxP2.y - m_boxP1.y)
    );

    m_boxShape.setPosition(topLeft);
    m_boxShape.setSize(size);
    m_boxShape.setFillColor(m_fillColor);
    m_boxShape.setOutlineColor(m_borderColor);
    m_boxShape.setOutlineThickness(m_borderThickness);
  }
}