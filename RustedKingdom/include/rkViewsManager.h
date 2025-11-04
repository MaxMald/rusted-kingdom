#pragma once

#include "rkPrerequisites.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf
{
  class RenderWindow;
}

namespace rk
{
  class ViewsManager
  {
  public:

    ViewsManager(sf::RenderWindow& window, sf::FloatRect& worldRect);
    ~ViewsManager();

    const sf::View& getWorldView() const;

    void moveWorldView(const sf::Vector2f& offset);

  private:
    sf::View m_WorldView;
  };
}