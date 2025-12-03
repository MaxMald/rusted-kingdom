#include "scripts/rkMinimapScript.h"

#include <algorithm>

#include <SFML/Graphics/View.hpp>

#include "rkServiceLocator.h"
#include "rkViewsManager.h"
#include "rkViewController.h"

namespace rk
{
  MinimapScript::MinimapScript(GameObject& gameObject) :
    ScriptComponent(gameObject),
    m_viewsManager(nullptr),
    m_mapRect(),
    m_viewBoxThickness(1.f)
  {
  }

  MinimapScript::~MinimapScript()
  {
  }
  
  void MinimapScript::setMapRect(const FloatRect& mapRect)
  {
    m_mapRect = mapRect;
    m_mapTopLeft = mapRect.position;
    m_mapBottomRight = mapRect.position + mapRect.size;
  }

  void MinimapScript::setMinimapSize(const Vector2f& minimapSize)
  {
    m_minimapSize = minimapSize;
  }

  void MinimapScript::setViewBoxColor(const sf::Color& color)
  {
    m_viewBoxColor = color;
  }

  void MinimapScript::onCreate()
  {
    m_viewsManager = ServiceLocator::Instance().getService<ViewsManager>();
  }

  void MinimapScript::onDraw(RenderTarget& target, RenderStates states) const
  {
    if (!m_viewsManager)
      return;

    if (m_mapRect.size.x == 0.f || m_mapRect.size.y == 0.f
      || m_minimapSize.x == 0.f || m_minimapSize.y == 0.f)
      return;

    drawViewBox(target, states);
  }

  void MinimapScript::drawViewBox(RenderTarget& target, RenderStates states) const
  {
    SharedPtr<ViewController> activeView = m_viewsManager->getActiveView();
    if (!activeView)
      return;

    Vector2f viewSize = activeView->getView().getSize();
    Vector2f viewCenter = activeView->getView().getCenter();
    Vector2f viewPosition = {
      viewCenter.x - viewSize.x * 0.5f,
      viewCenter.y - viewSize.y * 0.5f
    };

    FloatRect viewRect(
      viewPosition,
      viewSize
    );

    viewRect = clipRectViewToMapRect(viewRect);

    // Move to origin relative to map rect
    viewRect.position.x -= m_mapRect.position.x;
    viewRect.position.y -= m_mapRect.position.y;

    viewRect = scaleViewRectToMinimap(viewRect);

    if (viewRect.size.x <= 0.f || viewRect.size.y <= 0.f)
      return;

    sf::RectangleShape viewBox;
    viewBox.setPosition(viewRect.position);
    viewBox.setSize(viewRect.size);
    viewBox.setFillColor(sf::Color::Transparent);
    viewBox.setOutlineColor(m_viewBoxColor);
    viewBox.setOutlineThickness(m_viewBoxThickness);

    target.draw(viewBox, states);
  }

  FloatRect MinimapScript::clipRectViewToMapRect(const FloatRect& viewRect) const
  {
    Vector2f topLeftPoint = viewRect.position;
    Vector2f bottomRightPoint = viewRect.position + viewRect.size;

    topLeftPoint.x = std::max(topLeftPoint.x, m_mapTopLeft.x);
    topLeftPoint.y = std::max(topLeftPoint.y, m_mapTopLeft.y);
    bottomRightPoint.x = std::min(bottomRightPoint.x, m_mapBottomRight.x);
    bottomRightPoint.y = std::min(bottomRightPoint.y, m_mapBottomRight.y);

    Vector2f rectSize = bottomRightPoint - topLeftPoint;
    return FloatRect(topLeftPoint, rectSize);
  }

  FloatRect MinimapScript::scaleViewRectToMinimap(const FloatRect& viewRect) const
  {
    float xScale = m_minimapSize.x / m_mapRect.size.x;
    float yScale = m_minimapSize.y / m_mapRect.size.y;

    FloatRect minimapViewRect;
    minimapViewRect.position.x = viewRect.position.x * xScale;
    minimapViewRect.position.y = viewRect.position.y * yScale;
    minimapViewRect.size.x = viewRect.size.x * xScale;
    minimapViewRect.size.y = viewRect.size.y * yScale;

    return minimapViewRect;
  }

  FloatRect MinimapScript::moveRectToOrigin(const FloatRect& rect) const
  {
    FloatRect movedRect = rect;
    movedRect.position.x -= m_mapRect.position.x;
    movedRect.position.y -= m_mapRect.position.y;
    return movedRect;
  }
}