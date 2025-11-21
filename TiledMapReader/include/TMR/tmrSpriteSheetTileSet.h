#pragma once

#include "TMR/tmrTileSet.h"

namespace tmr
{
  class Image;

  /**
   * @brief Tileset backed by a single spritesheet image.
   *
   * SpriteSheetTileSet represents a tileset where tiles are packed in a single
   * source image organized in a regular grid.
   */
  class TMR_API SpriteSheetTileSet : public TileSet
  {
  public:

    /**
     * @brief Construct a new SpriteSheetTileSet.
     *
     * @param margin Number of pixels of empty border around the tiles in the
     * source image.
     * @param firstgid The first global tile ID for this tileset (as provided by
     * Tiled).
     * @param columns Number of tile columns in the source image.
     * @param imageHeight Height of the source image in pixels.
     * @param imageWidth Width of the source image in pixels.
     * @param spacing Number of pixels between tiles in the source image.
     * @param tileCount Total number of tiles contained in the tileset.
     * @param tileHeight Height of a single tile in pixels.
     * @param tileWidth Width of a single tile in pixels.
     * @param image Null-terminated path to the source image. The value will be
     * copied.
     * @param name Null-terminated tileset name (from Tiled). The value will be
     * copied.
     */
    SpriteSheetTileSet(
      Image* image,
      const std::int32_t& margin,
      const std::int32_t& firstgid,
      const std::uint32_t& columns,
      const std::uint32_t& spacing,
      const std::uint32_t& tileCount,
      const std::uint32_t& tileHeight,
      const std::uint32_t& tileWidth,
      const char* name
    );

    virtual ~SpriteSheetTileSet();

    /** @return source image */
    const Image* getImage() const noexcept { return m_image; }

    /** @return source image */
    Image* getImage() noexcept { return m_image; }

    /** @return margin in pixels */
    std::int32_t getMargin() const noexcept { return m_margin; }

    /** @return number of columns in the source image */
    std::uint32_t getColumns() const noexcept { return m_columns; }

    /** @return spacing in pixels between tiles */
    std::uint32_t getSpacing() const noexcept { return m_spacing; }

    /** @return number of tiles in the tileset */
    std::uint32_t getTileCount() const noexcept { return m_tileCount; }

    /** @return tile height in pixels */
    std::uint32_t getTileHeight() const noexcept { return m_tileHeight; }

    /** @return tile width in pixels */
    std::uint32_t getTileWidth() const noexcept { return m_tileWidth; }

    /** @return null-terminated copied tileset name*/
    const char* getName() const noexcept { return m_name; }

  private:
    Image* m_image;
    int32_t m_margin;
    uint32_t m_columns;
    uint32_t m_spacing;
    uint32_t m_tileCount;
    uint32_t m_tileHeight;
    uint32_t m_tileWidth;
    char* m_name;
  };
}