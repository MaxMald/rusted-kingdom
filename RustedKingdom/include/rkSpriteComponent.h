#pragma once

#include "rkComponent.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

using sf::Vector2f;

namespace rk
{
  class SpriteComponent : public Component
  {
  public:
    SpriteComponent(GameObject& gameObject, const sf::Texture& texture);
    SpriteComponent(
      GameObject& gameObject,
      const sf::Texture& texture,
      const sf::IntRect& textureRect
    );
    virtual ~SpriteComponent();

    sf::Sprite& getSprite() { return m_sprite; }
    const sf::Sprite& getSprite() const { return m_sprite; }
    void setOrigin(const Vector2f& origin);
    Vector2f getOrigin() const;
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