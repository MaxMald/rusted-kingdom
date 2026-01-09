#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkAGameObjectComponentDrawer.h"

namespace sf
{
  class Sprite;
}

namespace rk
{
  class SpriteGameObjectComponentDrawer : public AGameObjectComponentDrawer
  {
  public:
    SpriteGameObjectComponentDrawer();
    virtual ~SpriteGameObjectComponentDrawer() = default;

  protected:
    virtual void onDraw(Component& component, sf::RenderWindow& window) override;

  private:
    sf::Vector2f calculateImageSize(const sf::Sprite& sprite);
  };
}