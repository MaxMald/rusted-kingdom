#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  /**
   * @brief Represents a single tile in a tileset.
   *
   * TileSetTile represents a single tile in a tileset, including its unique
   * identifier and image properties.
   */
  class TMR_API TileSetTile
  {
  public:
    /**
     * @brief Constructor for TileSetTile
     *
     * @param id The unique identifier for the tile
     * @param imageWidth The width of the tile image
     * @param imageHeight The height of the tile image
     * @param image Null-terminated image source path. The value will be copied.
     */
    TileSetTile(
      std::uint32_t id,
      std::uint32_t imageWidth,
      std::uint32_t imageHeight,
      const char* image
    );

    ~TileSetTile();

    /** @return The unique identifier for the tile. */
    std::uint32_t getId() const { return m_id; }

    /** @return The width of the tile image. */
    std::uint32_t getImageWidth() const { return m_imageWidth; }

    /** @return The height of the tile image. */
    std::uint32_t getImageHeight() const { return m_imageHeight; }

    /** @return Null-terminated image source path. */
    const char* getImage() const { return m_image; }

  private:
    std::uint32_t m_id;
    std::uint32_t m_imageWidth;
    std::uint32_t m_imageHeight;
    char* m_image;
  };
}