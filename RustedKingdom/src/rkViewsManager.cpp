#include "rkViewsManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "rkWindowManager.h"
#include "rkServiceLocator.h"

namespace rk
{
  ViewsManager::ViewsManager() :
    m_worldView(),
    m_renderWindow(nullptr)
  {
  }

  ViewsManager::~ViewsManager()
  {
  }

  const sf::View& ViewsManager::getWorldView() const
  {
    return m_worldView;
  }

  void ViewsManager::moveWorldView(const sf::Vector2f& offset)
  {
    m_worldView.move(offset);
  }

  void ViewsManager::update(const float& deltaTime)
  {
    sf::Vector2f moveOffset(0.f, 0.f);
    const float moveSpeed = 400.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
      moveOffset.y -= moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
      moveOffset.y += moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
      moveOffset.x -= moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
      moveOffset.x += moveSpeed;

    // Normalize so diagonal movement does not exceed moveSpeed
    if (moveOffset.x != 0.f || moveOffset.y != 0.f)
    {
      float len = std::sqrt(moveOffset.x * moveOffset.x + moveOffset.y * moveOffset.y);
      if (len > 0.f)
      {
        moveOffset.x = (moveOffset.x / len) * moveSpeed;
        moveOffset.y = (moveOffset.y / len) * moveSpeed;
      }

      moveWorldView(moveOffset * deltaTime);
    }

    updateRenderWindowView();
  }

  void ViewsManager::init(ServiceLocator& serviceLocator)
  {
    SharedPtr<WindowManager> windowManager =
      serviceLocator.getService<WindowManager>();

    RenderWindow& renderWindow = windowManager->getRenderWindow();
    m_worldView = renderWindow.getDefaultView();

    m_renderWindow = &renderWindow;
  }

  void ViewsManager::destroy()
  {
    m_renderWindow = nullptr;
  }

  void ViewsManager::updateRenderWindowView()
  {
    if (m_renderWindow)
      m_renderWindow->setView(m_worldView);
  }
}