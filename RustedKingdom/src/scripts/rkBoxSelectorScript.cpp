#include "scripts/rkBoxSelectorScript.h"

#include "rkServiceLocator.h"
#include "rkInputManager.h"
#include "rkMouseInputManager.h"

#include "scripts/rkIBoxSelectorScriptListener.h"

namespace rk
{
  const sf::Mouse::Button SELECTION_BUTTON = sf::Mouse::Button::Left;

  BoxSelectorScript::BoxSelectorScript(GameObject& gameObject) :
    ScriptComponent(gameObject),
    m_boxP1(0.f, 0.f),
    m_boxP2(0.f, 0.f),
    m_boxShape(),
    m_isSelecting(false),
    m_inputManager(nullptr),
    m_borderColor(sf::Color::Green),
    m_fillColor(sf::Color::Green),
    m_borderThickness(2.f),
    m_listeners()
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

  bool BoxSelectorScript::isSelecting() const
  {
    return m_isSelecting;
  }

  const Vector2f& BoxSelectorScript::getBoxP1() const
  {
    return m_boxP1;
  }

  const Vector2f& BoxSelectorScript::getBoxP2() const
  {
    return m_boxP2;
  }

  void BoxSelectorScript::registerListener(IBoxSelectorScriptListener* listener)
  {
    if (listener && std::find(
      m_listeners.begin(),
      m_listeners.end(),
      listener) == m_listeners.end())
    {
      m_listeners.push_back(listener);
    }
  }

  void BoxSelectorScript::unregisterListener(IBoxSelectorScriptListener* listener)
  {
    auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
    if (it != m_listeners.end())
    {
      m_listeners.erase(it);
    }
  }

  void BoxSelectorScript::onCreate()
  {
    m_inputManager = ServiceLocator::Instance().getService<InputManager>();
    m_inputManager->getMouseInputManager().subscribe(this);
  }

  void BoxSelectorScript::onUpdate(float)
  {
    if (!m_isSelecting)
      return;

    updateBoxP2();
    updateBoxShape();

    for (IBoxSelectorScriptListener* listener : m_listeners)
      listener->onBoxSelectionUpdated(m_boxP1, m_boxP2);
  }

  void BoxSelectorScript::onDraw(RenderTarget& renderTarget, RenderStates states) const
  {
    if (!m_isSelecting)
      return;

    renderTarget.draw(m_boxShape, states);
  }

  void BoxSelectorScript::onDelete()
  {
    m_inputManager->getMouseInputManager().unsubscribe(this);
  }

  void BoxSelectorScript::onMouseButtonPressed(
    MouseButtonEvent& mouseEvent
  )
  {
    if (mouseEvent.getButton() != SELECTION_BUTTON || m_isSelecting)
      return;

    m_isSelecting = true;

    m_boxP1 = m_inputManager->getMouseInputManager()
      .getMousePositionWorldCoordinates();

    for (IBoxSelectorScriptListener* listener : m_listeners)
      listener->onBoxSelectionStarted(m_boxP1, m_boxP2);
  }

  void BoxSelectorScript::onMouseButtonReleased(
    MouseButtonEvent& mouseEvent
  )
  {
    if (mouseEvent.getButton() != SELECTION_BUTTON || !m_isSelecting)
      return;

    m_isSelecting = false;

    for (IBoxSelectorScriptListener* listener : m_listeners)
      listener->onBoxSelectionEnded(m_boxP1, m_boxP2);
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