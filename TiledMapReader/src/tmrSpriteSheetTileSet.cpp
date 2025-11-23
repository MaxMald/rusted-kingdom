#include "TMR/tmrSpriteSheetTileSet.h"

#include <cstring>

#include "TMR/tmrImage.h"

namespace tmr
{
  SpriteSheetTileSet::SpriteSheetTileSet(
    TileSetGrid* grid,
    Image* image,
    const int32_t& margin,
    const int32_t& firstgid,
    const uint32_t& columns,
    const uint32_t& spacing,
    const uint32_t& tileCount,
    const uint32_t& tileHeight,
    const uint32_t& tileWidth,
    const char* name
  ) :
    TileSet(tileSetType::Type::SpriteSheet, firstgid),
    m_grid(grid),
    m_image(image),
    m_margin(margin),
    m_columns(columns),
    m_spacing(spacing),
    m_tileCount(tileCount),
    m_tileHeight(tileHeight),
    m_tileWidth(tileWidth),
    m_name(nullptr)
  {
    m_name = name ? new char[std::strlen(name) + 1] : nullptr;
    if (m_name)
      std::strcpy(m_name, name);
  }

  SpriteSheetTileSet::~SpriteSheetTileSet()
  {
    if (m_image)
    {
      delete m_image;
      m_image = nullptr;
    }

    if (m_name)
    {
      delete[] m_name;
      m_name = nullptr;
    }
  }
}