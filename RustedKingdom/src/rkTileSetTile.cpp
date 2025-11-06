#include "rkTileSetTile.h"
#include <TMR/tmrTileSetTile.h>

namespace rk
{
  TileSetTile::TileSetTile() :
    m_id(0),
    m_imageWidth(0),
    m_imageHeight(0),
    m_imagePath()
  {
  }

  TileSetTile::TileSetTile(const TileSetTile& other) :
    m_id(other.m_id),
    m_imageWidth(other.m_imageWidth),
    m_imageHeight(other.m_imageHeight),
    m_imagePath(other.m_imagePath)
  {
  }

  TileSetTile& TileSetTile::operator=(const TileSetTile& other)
  {
    if (this == &other)
      return *this;

    m_id = other.m_id;
    m_imageWidth = other.m_imageWidth;
    m_imageHeight = other.m_imageHeight;
    m_imagePath = other.m_imagePath;

    return *this;
  }

  TileSetTile::TileSetTile(TileSetTile&& other) noexcept :
    m_id(other.m_id),
    m_imageWidth(other.m_imageWidth),
    m_imageHeight(other.m_imageHeight),
    m_imagePath(std::move(other.m_imagePath))
  {
    other.m_id = 0;
    other.m_imageWidth = 0;
    other.m_imageHeight = 0;
  }

  TileSetTile& TileSetTile::operator=(TileSetTile&& other) noexcept
  {
    if (this == &other)
      return *this;

    m_id = other.m_id;
    m_imageWidth = other.m_imageWidth;
    m_imageHeight = other.m_imageHeight;
    m_imagePath = std::move(other.m_imagePath);

    other.m_id = 0;
    other.m_imageWidth = 0;
    other.m_imageHeight = 0;

    return *this;
  }

  TileSetTile::TileSetTile(
    const Path& mapRootDirectory,
    const tmr::TileSetTile& tileSetTile) :
    m_id(tileSetTile.getId()),
    m_imageWidth(tileSetTile.getImageWidth()),
    m_imageHeight(tileSetTile.getImageHeight())
  {
    m_imagePath = mapRootDirectory / Path(tileSetTile.getImage());
  }

  TileSetTile::~TileSetTile()
  {
  }
}