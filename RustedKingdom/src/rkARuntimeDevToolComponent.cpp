#include "rkARuntimeDevToolComponent.h"

namespace rk
{
  void ARuntimeDevToolComponent::update(
    sf::RenderWindow& window,
    const sf::Time& elapsed
  )
  {
    this->onUpdate(window, elapsed);
  }

  void ARuntimeDevToolComponent::draw(sf::RenderWindow& window)
  {
    this->onDraw(window);
  }
}