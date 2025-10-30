#include "TMR/tmrTileSet.h"
#include <cstring>

namespace tmr
{
  TileSet::TileSet(
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
  ) :
    m_margin(margin),
    m_firstgid(firstgid),
    m_columns(columns),
    m_imageHeight(imageHeight),
    m_imageWidth(imageWidth),
    m_spacing(spacing),
    m_tileCount(tileCount),
    m_tileHeight(tileHeight),
    m_tileWidth(tileWidth),
    m_image(nullptr),
    m_name(nullptr)
  {
    m_image = image ? new char[std::strlen(image) + 1] : nullptr;
    if (m_image)
      std::strcpy(m_image, image);

    m_name = name ? new char[std::strlen(name) + 1] : nullptr;
    if (m_name)
      std::strcpy(m_name, name);
  }

  TileSet::~TileSet()
  {
    delete[] m_image;
    delete[] m_name;
  }
}