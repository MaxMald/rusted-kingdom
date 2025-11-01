#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"

namespace rk
{
  class TileDescription
  {
  public:
    
    TileDescription(
      const String& textureKey,
      const sf::IntRect& textureRect,
      const sf::Vector2i& position
    ) :
      m_textureKey(textureKey),
      m_textureRect(textureRect),
      m_position(position)
    {
    }

    const String& getTextureKey() const
    {
      return m_textureKey;
    }

    const sf::IntRect& getTextureRect() const
    {
      return m_textureRect;
    }

    const sf::Vector2i& getPosition() const
    {
      return m_position;
    }

  private:
    String m_textureKey;
    sf::IntRect m_textureRect;
    sf::Vector2i m_position;
  };
}