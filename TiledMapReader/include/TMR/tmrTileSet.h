#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  /**
   * @class TileSet
   * @brief Represents a tileset from a Tiled map.
   *
   * TileSet stores tileset metadata parsed from a Tiled JSON file.
   */
  class TMR_API TileSet
  {
  public:
    /**
     * @brief Constructs a TileSet with the specified properties.
     *
     * @param margin Pixel margin around the tiles in the source image.
     * @param firstgid The first global tile id for this tileset.
     * @param columns Number of tile columns in the source image.
     * @param imageHeight Height of the source image in pixels.
     * @param imageWidth Width of the source image in pixels.
     * @param spacing Pixel spacing between tiles in the source image.
     * @param tileCount Total number of tiles in the tileset.
     * @param tileHeight Height of a single tile in pixels.
     * @param tileWidth Width of a single tile in pixels.
     * @param image Null-terminated path/filename of the source image. A deep
     * copy is made; the original pointer may be freed by caller.
     * @param name Null-terminated tileset name. A deep copy is made. the
     * original pointer may be freed by caller.
     *
     * The constructor performs deep copies of \p image and \p name. The copies
     * are released when the TileSet is destroyed.
     */
    TileSet(
      const std::int32_t& margin,
      const std::int32_t& firstgid,
      const std::uint32_t& columns,
      const std::uint32_t& imageHeight,
      const std::uint32_t& imageWidth,
      const std::uint32_t& spacing,
      const std::uint32_t& tileCount,
      const std::uint32_t& tileHeight,
      const std::uint32_t& tileWidth,
      const char* image,
      const char* name
    );

    /**
     * @brief Destroys the TileSet and releases owned string memory.
     */
    ~TileSet();

    /** @return margin in pixels */
    std::int32_t getMargin() const noexcept { return m_margin; }

    /** @return first global tile id */
    std::int32_t getFirstGid() const noexcept { return m_firstgid; }
    
    /** @return number of columns in the source image */
    std::uint32_t getColumns() const noexcept { return m_columns; }
    
    /** @return source image height in pixels */
    std::uint32_t getImageHeight() const noexcept { return m_imageHeight; }
    
    /** @return source image width in pixels */
    std::uint32_t getImageWidth() const noexcept { return m_imageWidth; }
    
    /** @return spacing in pixels between tiles */
    std::uint32_t getSpacing() const noexcept { return m_spacing; }
    
    /** @return number of tiles in the tileset */
    std::uint32_t getTileCount() const noexcept { return m_tileCount; }
    
    /** @return tile height in pixels */
    std::uint32_t getTileHeight() const noexcept { return m_tileHeight; }
    
    /** @return tile width in pixels */
    std::uint32_t getTileWidth() const noexcept { return m_tileWidth; }
    
    /** @return null-terminated copied image path */
    const char* getImage() const noexcept { return m_image; }
    
    /** @return null-terminated copied tileset name*/
    const char* getName() const noexcept { return m_name; }

  private:
    std::int32_t m_margin;
    std::int32_t m_firstgid;
    std::uint32_t m_columns;
    std::uint32_t m_imageHeight;
    std::uint32_t m_imageWidth;
    std::uint32_t m_spacing;
    std::uint32_t m_tileCount;
    std::uint32_t m_tileHeight;
    std::uint32_t m_tileWidth;
    char* m_image;
    char* m_name;
  };
}