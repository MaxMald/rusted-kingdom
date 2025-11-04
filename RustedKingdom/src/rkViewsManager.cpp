#include "rkViewsManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace rk
{
  ViewsManager::ViewsManager(sf::RenderWindow& window, sf::FloatRect& worldRect) :
    m_WorldView(worldRect)
  {
    window.setView(m_WorldView);
  }

  ViewsManager::~ViewsManager()
  {
  }

  const sf::View& ViewsManager::getWorldView() const
  {
    return m_WorldView;
  }

  void ViewsManager::moveWorldView(const sf::Vector2f& offset)
  {
    m_WorldView.move(offset);
  }
}