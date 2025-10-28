#include "rkSpriteSheet.h"
#include <SFML/Graphics/Texture.hpp>

namespace rk
{
  SpriteSheet::SpriteSheet(
    sf::Texture* texture,
    UInt32 spriteWidth,
    UInt32 spriteHeight
  )
    : m_texture(texture)
    , m_spriteWidth(spriteWidth)
    , m_spriteHeight(spriteHeight)
  {
    if (m_texture)
    {
      m_numSpritesX = m_texture->getSize().x / m_spriteWidth;
      m_numSpritesY = m_texture->getSize().y / m_spriteHeight;
      m_totalNumSprites = m_numSpritesX * m_numSpritesY;
    }
    else
    {
      m_numSpritesX = 0;
      m_numSpritesY = 0;
      m_totalNumSprites = 0;
    }
  }

  SpriteSheet::~SpriteSheet()
  {
    // No ownership of texture, nothing to clean up
  }

  const sf::Texture& SpriteSheet::getTexture() const
  {
    return *m_texture;
  }

  sf::IntRect SpriteSheet::getSpriteRect(UInt32 index) const
  {
    if (m_numSpritesX == 0 || m_numSpritesY == 0 || !m_texture)
    {
      throw OutOfRangeException(
        "SpriteSheet::getSpriteRect: No sprites available in the sprite sheet."
      );
    }

    UInt32 xIndex = index % m_numSpritesX;
    UInt32 yIndex = index / m_numSpritesX;
    return getSpriteRect(xIndex, yIndex);
  }

  sf::IntRect SpriteSheet::getSpriteRect(UInt32 xIndex, UInt32 yIndex) const
  {
    if (!m_texture || xIndex >= m_numSpritesX || yIndex >= m_numSpritesY)
    {
      throw OutOfRangeException(
        String::Format(
          "SpriteSheet::getSpriteRect: Sprite index (%u, %u) is out of range. Max indices are (%u, %u).",
          xIndex, yIndex, m_numSpritesX - 1, m_numSpritesY - 1
        )
      );
    }

    return sf::IntRect(
      sf::Vector2i(
        static_cast<int>(xIndex * m_spriteWidth),
        static_cast<int>(yIndex * m_spriteHeight)
      ),
      sf::Vector2i(
        static_cast<int>(m_spriteWidth),
        static_cast<int>(m_spriteHeight))
    );
  }

  UInt32 SpriteSheet::getNumSpritesX() const
  {
    return m_numSpritesX;
  }

  UInt32 SpriteSheet::getNumSpritesY() const
  {
    return m_numSpritesY;
  }

  UInt32 SpriteSheet::getTotalNumSprites() const
  {
    return m_totalNumSprites;
  }
}