#include "TMR/tmrImageCollectionTileSet.h"
#include <memory>

namespace tmr
{
    ImageCollectionTileSet::ImageCollectionTileSet(
      const std::int32_t& firstgid,
      const TileSetGrid& grid,
      TileSetTile** tiles,
      const std::size_t& tileCount,
      const std::uint32_t& columns,
      const std::int32_t& margin,
      const std::uint32_t& spacing,
      const std::uint32_t& tileHeight,
      const std::uint32_t& tileWidth,
      const char* name) :
      TileSet(tileSetType::ImageCollection, firstgid),
      m_grid(grid),
      m_tiles(tiles),
      m_tileCount(tileCount),
      m_columns(columns),
      m_margin(margin),
      m_spacing(spacing),
      m_tileHeight(tileHeight),
      m_tileWidth(tileWidth),
      m_name(nullptr)
    {
      m_name = name ? new char[std::strlen(name) + 1] : nullptr;
      if (m_name)
        std::strcpy(m_name, name);
    }

    ImageCollectionTileSet::~ImageCollectionTileSet()
    {
      if (m_tiles)
      {
        for (std::size_t i = 0; i < m_tileCount; ++i)
          delete m_tiles[i];

        delete[] m_tiles;
        m_tiles = nullptr;
      }

      delete[] m_name;
      m_name = nullptr;
    }
}