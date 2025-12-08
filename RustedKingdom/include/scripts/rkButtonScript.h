#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "rkScriptComponent.h"
#include "rkIMouseInputManagerListener.h"
#include "rkIButtonScriptListener.h"

using sf::Vector2i;
using sf::IntRect;

namespace rk
{
  class InputManager;
  class SpriteComponent;

  class ButtonScript : public ScriptComponent, public IMouseInputManagerListener
  {
  public:
    ButtonScript(GameObject& gameObject);
    virtual ~ButtonScript();

    void prepare(
      const IntRect& normalRect,
      const IntRect& hoveredRect,
      const IntRect& pressedRect
    );

    virtual void onMouseButtonPressed(MouseButtonEvent&);
    virtual void onMouseButtonReleased(MouseButtonEvent&);

    void subscribe(IButtonScriptListener* listener);
    void unsubscribe(IButtonScriptListener* listener);

  protected:
    virtual void onCreate() override;
    virtual void onUpdate(float deltaTime) override;
    virtual void onDelete() override;

  private:
    Vector<IButtonScriptListener*> m_listeners;
    SpriteComponent* m_spriteComponent;
    SharedPtr<InputManager> m_inputManager;
    IntRect m_normalRect;
    IntRect m_hoveredRect;
    IntRect m_pressedRect;
    bool m_isHovered;
    bool m_isPressed;

    void updateTextureRect(const IntRect& rect);
    bool isMouseOverButton();
  };
}