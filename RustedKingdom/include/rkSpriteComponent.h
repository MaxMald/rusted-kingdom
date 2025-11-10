#pragma once

#include "rkComponent.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

using sf::Texture;

namespace rk
{
  class SpriteComponent : public Component
  {
  public:
    SpriteComponent(GameObject& gameObject, const Texture& texture);
    virtual ~SpriteComponent();

    void setTexture(const sf::Texture& texture);
    void setTextureRect(const sf::IntRect& rect);

  protected:
    sf::Sprite m_sprite;

    virtual void onDraw(
      sf::RenderTarget& target,
      sf::RenderStates states
    ) const override;
  };
}