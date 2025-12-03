#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "rkScriptComponent.h"

using sf::FloatRect;
using sf::Vector2f;

namespace rk
{
  class ViewsManager;

  class MinimapScript : public ScriptComponent
  {
  public:
    MinimapScript(GameObject& gameObject);
    virtual ~MinimapScript();

    void setMapRect(const FloatRect& mapRect);
    void setMinimapSize(const Vector2f& minimapSize);
    void setViewBoxThickness(float thickness) { m_viewBoxThickness = thickness; }
    void setViewBoxColor(const sf::Color& color);

  protected:
    virtual void onCreate() override;
    virtual void onDraw(RenderTarget& target, RenderStates states) const override;

  private:
    float m_viewBoxThickness;
    sf::RectangleShape m_viewBoxShape;
    sf::Color m_viewBoxColor;
    FloatRect m_mapRect;
    Vector2f m_mapTopLeft;
    Vector2f m_mapBottomRight;
    Vector2f m_minimapSize;
    SharedPtr<ViewsManager> m_viewsManager;

    void drawViewBox(RenderTarget&, RenderStates) const;
    FloatRect clipRectViewToMapRect(const FloatRect& viewRect) const;
    FloatRect scaleViewRectToMinimap(const FloatRect& viewRect) const;
    FloatRect moveRectToOrigin(const FloatRect& rect) const;
  };
}