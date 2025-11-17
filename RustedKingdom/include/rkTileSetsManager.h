#pragma once

#include "rkPrerequisites.h"
#include "rkTileDescription.h"

namespace tmr
{
  class TiledMap;
  class TileSet;
}

namespace rk
{
  class TileSet;
  class TileSetTile;

  /**
   * @class TileSetsManager
   * @brief Loads and owns lightweight rk::TileSet wrappers for a Tiled map.
   */
  class TileSetsManager
  {
  public:

    TileSetsManager();
    ~TileSetsManager();

    bool load(const Path& mapRootDirectory, const tmr::TiledMap& tiledMap);

    SizeT getTileSetsCount() const { return m_tileSets.size(); }
    const TileSet& getTileSetAt(const SizeT& index) const;
    const TileSetTile& getTileSetTileByGid(const Int32& gid) const;
    TileDescription getTileDescriptionByGid(const Int32& gid) const;

    void clear();

  private:
    Vector<TileSet*> m_tileSets;

    TileSet* createTileSetFromTmrTileSet(
      const Path& mapRootDirectory,
      const tmr::TileSet& tmrTileSet
    ) const;
  };
}