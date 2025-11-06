#include "rkImageCollectionTileSet.h"

#include <TMR/tmrImageCollectionTileSet.h>
#include <TMR/tmrTileSetTile.h>

#include "rkAssertions.h"

namespace rk
{
  ImageCollectionTileSet::ImageCollectionTileSet(
    const Path& mapRootDirectory,
    const tmr::ImageCollectionTileSet& tmrImageCollectionTileSet
  ) :
    TileSet(
      tmrImageCollectionTileSet.getType(),
      tmrImageCollectionTileSet.getFirstGid()
    ),
    m_tileCount(tmrImageCollectionTileSet.getTileCount()),
    m_columns(tmrImageCollectionTileSet.getColumns()),
    m_margin(tmrImageCollectionTileSet.getMargin()),
    m_spacing(tmrImageCollectionTileSet.getSpacing()),
    m_tileHeight(tmrImageCollectionTileSet.getTileHeight()),
    m_tileWidth(tmrImageCollectionTileSet.getTileWidth()),
    m_name(tmrImageCollectionTileSet.getName()),
    m_grid(tmrImageCollectionTileSet.getGrid())
  {
    m_tiles.reserve(m_tileCount);
    for (Int32 i = 0; i < m_tileCount; ++i)
    {
      const tmr::TileSetTile* tmrTile = tmrImageCollectionTileSet.getTileAt(i);
      if (tmrTile)
        m_tiles.push_back(TileSetTile(mapRootDirectory, *tmrTile));
    }
  }

  ImageCollectionTileSet::~ImageCollectionTileSet()
  {
  }

  Bool ImageCollectionTileSet::isGidInRange (const Int32& gid) const
  {
    const Int32 firstGid = getFirstGid();
    return (gid >= firstGid && gid < firstGid + static_cast<Int32>(m_tileCount));
  }

  TileDescription ImageCollectionTileSet::getTileDescriptionAt(
    const Int32& localId
  ) const
  {
    assertions::assertIndexInRange(
      localId,
      static_cast<Int32>(m_tiles.size()),
      "tile local id"
    );

    TileSetTile tile = m_tiles[localId];
    return TileDescription(
      tile.getImagePath().string(),
      sf::IntRect(
        sf::Vector2i(0, 0),
        sf::Vector2i(tile.getImageWidth(), tile.getImageHeight())
      )
    );
  }
}