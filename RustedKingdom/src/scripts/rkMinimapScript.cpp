#include "scripts/rkMinimapScript.h"

#include <algorithm>

#include <SFML/Graphics/View.hpp>

#include "rkServiceLocator.h"
#include "rkViewsManager.h"
#include "rkInputManager.h"
#include "rkViewController.h"
#include "rkGameObject.h"

namespace rk
{
  constexpr sf::Mouse::Button DRAG_BUTTON = sf::Mouse::Button::Left;

  MinimapScript::MinimapScript(GameObject& gameObject) :
    ScriptComponent(gameObject),
    m_viewsManager(nullptr),
    m_mapRect(),
    m_viewBoxThickness(1.f),
    m_inputManager(nullptr),
    m_isDragging(false)
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
    m_inputManager = ServiceLocator::Instance().getService<InputManager>();
    m_inputManager->getMouseInputManager().subscribe(this);
  }

  void MinimapScript::onUpdate(float)
  {
    if (!m_isDragging)
      return;

    sf::Vector2f mouseWorldPos = m_inputManager->getMouseInputManager()
      .getMousePositionWorldCoordinates();

    SharedPtr<ViewController> activeView = m_viewsManager->getActiveView();
    if (!activeView)
      return;

    // Convert mouse world position to view-relative position
    sf::Vector2f viewCenter = activeView->getView().getCenter();
    sf::Vector2f viewPosition = {
      viewCenter.x - activeView->getView().getSize().x * 0.5f,
      viewCenter.y - activeView->getView().getSize().y * 0.5f
    };
    sf::Vector2f mouseViewPos = {
      mouseWorldPos.x - viewPosition.x,
      mouseWorldPos.y - viewPosition.y
    };

    if (!isPointInMinimap(mouseViewPos))
      return;

    // Calculate the corresponding position on the main map
    Vector2f localMinimapPos = mouseViewPos - m_gameObject->getPosition();
    Vector2f normalizedLocalPos = {
      localMinimapPos.x / m_minimapSize.x,
      localMinimapPos.y / m_minimapSize.y
    };
    Vector2f mouseMapPos = {
      m_mapRect.position.x + normalizedLocalPos.x * m_mapRect.size.x,
      m_mapRect.position.y + normalizedLocalPos.y * m_mapRect.size.y
    };

    activeView->setViewCenter(mouseMapPos);
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

  void MinimapScript::onMouseButtonPressed(const MouseButtonEvent& event)
  {
    if (event.getButton() != DRAG_BUTTON)
      return;

    m_isDragging = true;
    // TODO Should avoid others to get the input event.
  }
  
  void MinimapScript::onMouseButtonReleased(const MouseButtonEvent& event)
  {
    if (event.getButton() != DRAG_BUTTON)
      return;

    m_isDragging = false;
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
  bool MinimapScript::isPointInMinimap(const Vector2f& point) const
  {
    Vector2f minimapTopLeft = m_gameObject->getPosition();
    Vector2f minimapBottomRight = minimapTopLeft + m_minimapSize;

    return point.x >= minimapTopLeft.x
      && point.x <= minimapBottomRight.x
      && point.y >= minimapTopLeft.y
      && point.y <= minimapBottomRight.y;
  }
}