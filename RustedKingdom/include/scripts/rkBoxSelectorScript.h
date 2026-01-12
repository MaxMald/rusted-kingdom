#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "rkScriptComponent.h"
#include "rkIMouseInputManagerListener.h"

using sf::Vector2f;

namespace rk
{
  class InputManager;
  class IBoxSelectorScriptListener;

  class BoxSelectorScript : public ScriptComponent, IMouseInputManagerListener
  {
  public:
    BoxSelectorScript(GameObject& gameObject);
    virtual ~BoxSelectorScript();

    void setBorderColor(const sf::Color& color);
    void setFillColor(const sf::Color& color);
    void setBorderThickness(float thickness);

    bool isSelecting() const;
    const Vector2f& getBoxP1() const;
    const Vector2f& getBoxP2() const;

    void registerListener(IBoxSelectorScriptListener* listener);
    void unregisterListener(IBoxSelectorScriptListener* listener);

  protected:
    virtual void onCreate() override;
    virtual void onUpdate(float deltaTime) override;
    virtual void onDraw(RenderTarget&, RenderStates) const override;
    virtual void onDelete() override;

    virtual void onMouseButtonPressed(MouseButtonEvent&);
    virtual void onMouseButtonReleased(MouseButtonEvent&);

  private:
    sf::Color m_borderColor;
    sf::Color m_fillColor;
    sf::RectangleShape m_boxShape;
    float m_borderThickness;
    Vector2f m_boxP1;
    Vector2f m_boxP2;
    bool m_isSelecting;
    SharedPtr<InputManager> m_inputManager;
    Vector<IBoxSelectorScriptListener*> m_listeners;

    void updateBoxP2();
    void updateBoxShape();
  };
}