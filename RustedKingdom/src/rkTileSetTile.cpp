#include "rkTileSetTile.h"

#include <TMR/tmrTileSetTile.h>

#include "rkTiledImage.h"

namespace rk
{
  TileSetTile::TileSetTile(
    const Path& mapRootDirectory,
    const tmr::TileSetTile& tileSetTile) :
    m_id(tileSetTile.getId()),
    m_image(nullptr)
  {
    tmr::ObjectGroup* tmrObjectGroup = tileSetTile.getObjectGroup();
    if (tmrObjectGroup)
      m_tiledObjectGroup = TiledObjectGroup(*tmrObjectGroup);

    m_image = new TiledImage(tileSetTile.getImage());
  }

  TileSetTile::~TileSetTile()
  {
    if (m_image)
    {
      delete m_image;
      m_image = nullptr;
    }
  }
}