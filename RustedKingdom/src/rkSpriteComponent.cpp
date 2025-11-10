#include "rkSpriteComponent.h"
#include "rkGameObject.h"

namespace rk
{
  SpriteComponent::SpriteComponent(GameObject& gameObject, const Texture& texture) :
    Component(gameObject),
    m_sprite(texture)
  {
  }

  SpriteComponent::~SpriteComponent()
  {
  }

  void SpriteComponent::setTexture(const sf::Texture& texture)
  {
    m_sprite.setTexture(texture);
  }

  void SpriteComponent::setTextureRect(const sf::IntRect& rect)
  {
    m_sprite.setTextureRect(rect);
  }

  void SpriteComponent::onDraw(
    sf::RenderTarget& target,
    sf::RenderStates states
  ) const
  {
    target.draw(m_sprite, states);
  }
}