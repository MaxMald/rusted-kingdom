#include "TMR/tmrTileSetTile.h"
#include <cstring>

namespace tmr
{
  TileSetTile::TileSetTile(
    std::uint32_t id,
    std::uint32_t imageWidth,
    std::uint32_t imageHeight,
    const char* image
  ) :
    m_id(id),
    m_imageWidth(imageWidth),
    m_imageHeight(imageHeight),
    m_image(nullptr)
  {
    m_image = image ? new char[std::strlen(image) + 1] : nullptr;
    if (m_image)
      std::strcpy(m_image, image);
  }

  TileSetTile::~TileSetTile()
  {
    delete[] m_image;
  }
}