#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"

namespace rk
{
  /**
   * @brief Describes a single tile within a tilemap.
   *
   * This class stores the minimal information required to render or identify a
   * tile: the key of the texture (tileset) that contains the tile graphic, the
   * source rectangle within that texture.
   */
  class TileDescription
  {
  public:
    /**
     * @brief Construct a TileDescription.
     *
     * @param textureKey Key identifying the texture/tileset that contains the
     * tile graphic.
     * @param textureRect Rectangle (in pixels) within the texture that defines
     * the tile graphic.
     */
    TileDescription(
      const String& textureKey,
      const sf::IntRect& textureRect
    ) :
      m_textureKey(textureKey),
      m_textureRect(textureRect)
    {
    }

    /**
     * @brief Copy constructor.
     */
    TileDescription(const TileDescription& other) :
      m_textureKey(other.m_textureKey),
      m_textureRect(other.m_textureRect)
    {
    }

    /**
     * @return Reference to the texture key identifying the tileset/texture.
     */
    const String& getTextureKey() const
    {
      return m_textureKey;
    }

    /**
     * @return Reference to the rectangle (pixels) describing the tile image in
     * the tileset texture.
     */
    const sf::IntRect& getTextureRect() const
    {
      return m_textureRect;
    }

  private:
    String m_textureKey;
    sf::IntRect m_textureRect;
  };
}