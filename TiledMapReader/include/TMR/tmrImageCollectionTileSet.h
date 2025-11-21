#pragma once

#include "TMR/tmrTileSet.h"

namespace tmr
{
  class TileSetTile;
  class TileSetGrid;

  /**
   * @brief Tileset backed by a collection of individual images.
   */
  class TMR_API ImageCollectionTileSet : public TileSet
  {
  public:
    /**
     * @brief Construct a new ImageCollectionTileSet instance.
     *
     * @param firstgid The first global tile ID for this tileset (as provided by
     * Tiled).
     * @param grid Grid metadata that describes how tiles are arranged when
     * applicable.
     * @param tiles Pointer to an array of TileSetTile objects. Ownership is
     * transferred to this object; may be nullptr if \p tileCount is 0.
     * @param tileCount Number of tiles contained in the \p tiles array.
     * @param columns Number of columns in the tileset (used by consumers to
     * compute texture rectangles).
     * @param margin Pixel margin around tiles in the source images.
     * @param spacing Pixel spacing between tiles in the source images.
     * @param tileHeight Tile image height in pixels.
     * @param tileWidth Tile image width in pixels.
     * @param name Optional null-terminated tileset display name. The value will
     * be copied and owned by this object; may be nullptr.
     */
    ImageCollectionTileSet(
      const std::int32_t& firstgid,
      TileSetGrid* grid,
      TileSetTile** tiles,
      const std::size_t& tileCount,
      const std::uint32_t& columns,
      const std::int32_t& margin,
      const std::uint32_t& spacing,
      const std::uint32_t& tileHeight,
      const std::uint32_t& tileWidth,
      const char* name
    );

    /** Virtual destructor */
    virtual ~ImageCollectionTileSet();

    /** @return tileset grid */
    const TileSetGrid* getGrid() const noexcept { return m_grid; }

    /** @return tile at position. */
    const TileSetTile* getTileAt(const std::size_t& index) const
    {
      if (index >= m_tileCount)
        return nullptr;
      return m_tiles[index];
    }

    /** @return tile at position. */
    TileSetTile* getTileAt(const std::size_t& index)
    {
      if (index >= m_tileCount)
        return nullptr;
      return m_tiles[index];
    }

    /** @return number of tiles in the tileset */
    std::size_t getTileCount() const noexcept { return m_tileCount; }

    /** @return number of columns in the tileset */
    std::uint32_t getColumns() const noexcept { return m_columns; }

    /** @return margin in pixels */
    std::int32_t getMargin() const noexcept { return m_margin; }

    /** @return spacing in pixels */
    std::uint32_t getSpacing() const noexcept { return m_spacing; }

    /** @return tile height in pixels */
    std::uint32_t getTileHeight() const noexcept { return m_tileHeight; }

    /** @return tile width in pixels */
    std::uint32_t getTileWidth() const noexcept { return m_tileWidth; }

    /** @return tileset name */
    const char* getName() const noexcept { return m_name; }

  private:
    TileSetGrid* m_grid;
    TileSetTile** m_tiles;
    std::size_t m_tileCount;
    std::uint32_t m_columns;
    std::int32_t m_margin;
    std::uint32_t m_spacing;
    std::uint32_t m_tileHeight;
    std::uint32_t m_tileWidth;
    char* m_name;
  };
}