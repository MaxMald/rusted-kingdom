#include "rkSpriteSheet.h"

#include <SFML/Graphics/Texture.hpp>

#include "rkTexture.h"

namespace rk
{
  SpriteSheet::SpriteSheet() :
    m_texture(nullptr),
    m_spriteWidth(0),
    m_spriteHeight(0),
    m_numSpritesX(0),
    m_numSpritesY(0),
    m_totalNumSprites(0)
  {
  }

  SpriteSheet::SpriteSheet(
  SharedPtr<Texture> texture,
  UInt32 spriteWidth,
  UInt32 spriteHeight
  ) :
    m_texture(texture),
    m_spriteWidth(spriteWidth),
    m_spriteHeight(spriteHeight)
  {
    const sf::Texture& sfmlTexture = m_texture->getSFMLTexture();
    m_numSpritesX = sfmlTexture.getSize().x / m_spriteWidth;
    m_numSpritesY = sfmlTexture.getSize().y / m_spriteHeight;
    m_totalNumSprites = m_numSpritesX * m_numSpritesY;
  }

  SpriteSheet::SpriteSheet(const SpriteSheet& other) :
    m_texture(other.m_texture),
    m_spriteWidth(other.m_spriteWidth),
    m_spriteHeight(other.m_spriteHeight),
    m_numSpritesX(other.m_numSpritesX),
    m_numSpritesY(other.m_numSpritesY),
    m_totalNumSprites(other.m_totalNumSprites)
  {
  }

  SpriteSheet::SpriteSheet(SpriteSheet&& spriteSheet) :
    m_texture(std::move(spriteSheet.m_texture)),
    m_spriteWidth(spriteSheet.m_spriteWidth),
    m_spriteHeight(spriteSheet.m_spriteHeight),
    m_numSpritesX(spriteSheet.m_numSpritesX),
    m_numSpritesY(spriteSheet.m_numSpritesY),
    m_totalNumSprites(spriteSheet.m_totalNumSprites)
  {
  }

  SpriteSheet::~SpriteSheet()
  {
    // No ownership of texture, nothing to clean up
  }

  SpriteSheet& SpriteSheet::operator=(const SpriteSheet& other)
  {
    if (this != &other)
    {
      m_texture = other.m_texture;
      m_spriteWidth = other.m_spriteWidth;
      m_spriteHeight = other.m_spriteHeight;
      m_numSpritesX = other.m_numSpritesX;
      m_numSpritesY = other.m_numSpritesY;
      m_totalNumSprites = other.m_totalNumSprites;
    }
    return *this;
  }

  SpriteSheet& SpriteSheet::operator=(SpriteSheet&& spriteSheet)
  {
    if (this != &spriteSheet)
    {
      m_texture = std::move(spriteSheet.m_texture);
      m_spriteWidth = spriteSheet.m_spriteWidth;
      m_spriteHeight = spriteSheet.m_spriteHeight;
      m_numSpritesX = spriteSheet.m_numSpritesX;
      m_numSpritesY = spriteSheet.m_numSpritesY;
      m_totalNumSprites = spriteSheet.m_totalNumSprites;
    }
    return *this;
  }

  const SharedPtr<Texture>& SpriteSheet::getTexture() const
  {
    return m_texture;
  }

  sf::IntRect SpriteSheet::getSpriteRect(UInt32 index) const
  {
    if (m_numSpritesX == 0 || m_numSpritesY == 0)
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
    if (xIndex >= m_numSpritesX || yIndex >= m_numSpritesY)
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