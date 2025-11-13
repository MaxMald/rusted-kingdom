#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace sf
{
  class Texture;
}

namespace rk
{
  /**
   * @brief Represents a sprite sheet, providing access to individual sprite
   * rectangles.
   *
   * SpriteSheet manages a grid of equally sized sprites within a single SFML
   * texture. It provides methods to retrieve the texture, calculate sprite
   * rectangles by index or grid position, and query the number of sprites in
   * each dimension.
   */
  class SpriteSheet : public NonCopyable
  {
  public:
      /**
       * @brief Constructs a SpriteSheet from a texture and sprite dimensions.
       *
       * @param texture Pointer to the SFML texture containing the sprite sheet.
       * @param spriteWidth Width of each individual sprite in pixels.
       * @param spriteHeight Height of each individual sprite in pixels.
       */
      SpriteSheet(const sf::Texture& texture, UInt32 spriteWidth, UInt32 spriteHeight);

      /**
       * @brief Destructor.
       *
       * Does not delete the texture, which is managed externally.
       */
      ~SpriteSheet();

      /**
       * @brief Gets the underlying SFML texture.
       *
       * @return Reference to the texture.
       */
      const sf::Texture& getTexture() const;

      /**
       * @brief Gets the rectangle of a sprite by linear index.
       *
       * @param index Linear index of the sprite (row-major order).
       * @return Rectangle representing the sprite's position and size in the
       * texture.
       */
      sf::IntRect getSpriteRect(UInt32 index) const;

      /**
       * @brief Gets the rectangle of a sprite by grid coordinates.
       *
       * @param xIndex X index (column) of the sprite.
       * @param yIndex Y index (row) of the sprite.
       * @return Rectangle representing the sprite's position and size in the
       * texture.
       */
      sf::IntRect getSpriteRect(UInt32 xIndex, UInt32 yIndex) const;

      /**
       * @brief Gets the number of sprites horizontally in the sheet.
       *
       * @return Number of sprites along the X axis.
       */
      UInt32 getNumSpritesX() const;

      /**
       * @brief Gets the number of sprites vertically in the sheet.
       *
       * @return Number of sprites along the Y axis.
       */
      UInt32 getNumSpritesY() const;

      /**
       * @brief Gets the total number of sprites in the sheet.
       *
       * @return Total number of sprites.
       */
      UInt32 getTotalNumSprites() const;
    
  private:
      const sf::Texture& m_texture;
      UInt32 m_spriteWidth;
      UInt32 m_spriteHeight;
      UInt32 m_numSpritesX;
      UInt32 m_numSpritesY;
      UInt32 m_totalNumSprites;
  };
}