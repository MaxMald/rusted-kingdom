#include "rkSpriteGameObject.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace rk
{
  SpriteGameObject::SpriteGameObject(const sf::Texture* texture)
    : m_texture(texture),
    m_sprite(*texture)
  {
    if (m_texture)
      m_sprite.setTexture(*m_texture);
  }

  void SpriteGameObject::setTexture(const sf::Texture* texture)
  {
    m_texture = texture;
    if (m_texture)
      m_sprite.setTexture(*m_texture);
  }

  sf::Sprite& SpriteGameObject::getSprite()
  {
    return m_sprite;
  }

  void SpriteGameObject::draw(
    RenderTarget& renderTarget,
    RenderStates states) const
  {
    renderTarget.draw(m_sprite, states);
  }
}