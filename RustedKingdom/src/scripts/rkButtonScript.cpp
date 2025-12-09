#include "scripts/rkButtonScript.h"

#include <SFML/Graphics/Sprite.hpp>

#include "rkSpriteComponent.h"
#include "rkGameObject.h"
#include "rkServiceLocator.h"
#include "rkAssetManager.h"
#include "rkInputManager.h"
#include "rkMouseInputManager.h"
#include "rkTypedAssetGroup.h"
#include "rkTexture.h"
#include "rkGameObjectUtilities.h"

using sf::FloatRect;

namespace rk
{
  constexpr sf::Mouse::Button CLICK_BUTTON = sf::Mouse::Button::Left;

  ButtonScript::ButtonScript(GameObject& gameObject) :
    ScriptComponent(gameObject),
    m_normalRect(),
    m_hoveredRect(),
    m_pressedRect(),
    m_isHovered(false),
    m_isPressed(false),
    m_spriteComponent(nullptr),
    m_inputManager(nullptr),
    m_listeners()
  {
  }

  ButtonScript::~ButtonScript()
  {
  }

  void ButtonScript::prepare(
    const IntRect& normalRect,
    const IntRect& hoveredRect,
    const IntRect& pressedRect
  )
  {
    m_normalRect = normalRect;
    m_hoveredRect = hoveredRect;
    m_pressedRect = pressedRect;
  }

  void ButtonScript::onMouseButtonPressed(MouseButtonEvent& event)
  {
    if (event.getButton() != CLICK_BUTTON)
      return;

    if (!isMouseOverButton())
      return;

    m_isPressed = true;
    event.setConsumed(true);
    updateTextureRect(m_pressedRect);
  }

  void ButtonScript::onMouseButtonReleased(MouseButtonEvent& event)
  {
    if (event.getButton() != CLICK_BUTTON)
      return;

    m_isPressed = false;
    if (isMouseOverButton())
    {
      m_isHovered = true;
      updateTextureRect(m_hoveredRect);

      for (IButtonScriptListener* listener : m_listeners)
        listener->onButtonClicked(*(this->m_gameObject));
    }
    else
    {
      m_isHovered = false;
      updateTextureRect(m_normalRect);
    }
  }

  void ButtonScript::subscribe(IButtonScriptListener* listener)
  {
    m_listeners.push_back(listener);
  }

  void ButtonScript::unsubscribe(IButtonScriptListener* listener)
  {
    m_listeners.erase(
      std::remove(
        m_listeners.begin(),
        m_listeners.end(),
        listener
      ),
      m_listeners.end()
    );
  }

  void ButtonScript::onCreate()
  {
    m_spriteComponent = m_gameObject->getComponent<SpriteComponent>();
    m_inputManager = ServiceLocator::Instance().getService<InputManager>();
    m_inputManager->getMouseInputManager().subscribe(this);

    updateTextureRect(m_normalRect);
  }

  void ButtonScript::onUpdate(float)
  {
    Vector2i mousePosition = m_inputManager->getMouseInputManager()
      .getMousePositionRelativeToWindow();

    bool mouseOver = isMouseOverButton();
    if (mouseOver && !m_isHovered && !m_isPressed)
    {
      m_isHovered = true;
      updateTextureRect(m_hoveredRect);
    }
    else if (!mouseOver && m_isHovered && !m_isPressed)
    {
      m_isHovered = false;
      updateTextureRect(m_normalRect);
    }
  }

  void ButtonScript::onDelete()
  {
    m_inputManager->getMouseInputManager().unsubscribe(this);
  }

  void ButtonScript::updateTextureRect(const IntRect& rect)
  {
    m_spriteComponent->setTextureRect(rect);
  }

  bool ButtonScript::isMouseOverButton()
  {
    Vector2i mousePosition = m_inputManager->getMouseInputManager()
      .getMousePositionRelativeToWindow();

    FloatRect spriteBounds = gameObjectUtilities::
      getGameObjectSpriteGlobalBounds(*m_gameObject);

    Vector2f positionFloat = Vector2f(
      static_cast<float>(mousePosition.x),
      static_cast<float>(mousePosition.y)
    );

    return spriteBounds.contains(positionFloat);
  }
}