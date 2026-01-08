#pragma once

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class ARuntimeDevToolComponent : public NonCopyable
  {
  public:
    virtual ~ARuntimeDevToolComponent() = default;

    void update(sf::RenderWindow& window, const sf::Time& elapsed);
    void draw(sf::RenderWindow& window);

  protected:
    ARuntimeDevToolComponent() = default;

    virtual void onUpdate(sf::RenderWindow& window, const sf::Time& elapsed) = 0;
    virtual void onDraw(sf::RenderWindow& window) = 0;
  };
}