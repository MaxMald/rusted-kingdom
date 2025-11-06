#pragma once

#include "rkTileSet.h"
#include "rkTileSetTile.h"
#include "rkTileSetGrid.h"

namespace tmr
{
  class ImageCollectionTileSet;
}

namespace rk
{
  class ImageCollectionTileSet : public TileSet
  {
  public:
    ImageCollectionTileSet(
      const Path& mapRootDirectory,
      const tmr::ImageCollectionTileSet& tmrImageCollectionTileSet
    );
    virtual ~ImageCollectionTileSet();

    Bool isGidInRange (const Int32& gid) const override;
    TileDescription getTileDescriptionAt(const Int32& localId) const override;

    const Vector<TileSetTile>& getTiles() const { return m_tiles; }
    const TileSetGrid& getGrid() const { return m_grid; }
    SizeT getTileCount() const { return m_tileCount; }
    UInt32 getColumns() const { return m_columns; }
    Int32 getMargin() const { return m_margin; }
    UInt32 getSpacing() const { return m_spacing; }
    UInt32 getTileHeight() const { return m_tileHeight; }
    UInt32 getTileWidth() const { return m_tileWidth; }
    String getName() const { return m_name; }

  private:
    Vector<TileSetTile> m_tiles;
    TileSetGrid m_grid;
    SizeT m_tileCount;
    UInt32 m_columns;
    Int32 m_margin;
    UInt32 m_spacing;
    UInt32 m_tileHeight;
    UInt32 m_tileWidth;
    String m_name;
  };
}