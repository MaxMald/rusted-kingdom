#pragma once

#include "rkPrerequisites.h"
#include "rkTileDescription.h"

namespace tmr
{
  class TiledMap;
}

namespace rk
{
  class TileSet;

  /**
   * @class TileSetsManager
   * @brief Loads and owns lightweight rk::TileSet wrappers for a Tiled map.
   */
  class TileSetsManager
  {
  public:
    /**
     * @brief Constructs an empty TileSetsManager.
     *
     * The manager starts with no tilesets loaded. Call load(...) to populate
     * it from a parsed tmr::TiledMap.
     */
    TileSetsManager();

    /**
     * @brief Destructor.
     *
     * Releases any rk::TileSet instances owned by the manager.
     */
    ~TileSetsManager();

    /**
     * @brief Loads tilesets for the provided TMR tiled map.
     *
     * @param mapRootDirectory Base directory used to resolve relative image
     * paths.
     * @param tiledMap Pointer to a parsed tmr::TiledMap (not owned).
     * 
     * @return true if tilesets were loaded successfully; false on error.
     */
    bool load(
      const Path& mapRootDirectory,
      const tmr::TiledMap* tiledMap
    );

    /**
     * @brief Gets the number of loaded tilesets.
     * 
     * @return Number of tilesets.
     */
    SizeT getTileSetsCount() const { return m_tileSets.size(); }

    /**
     * @brief Retrieves the tileset at the specified index.
     * 
     * @param index Index of the tileset to retrieve.
     * @return Pointer to the rk::TileSet at the given index.
     * 
     * @throws RuntimeErrorException if the index is out of bounds.
     */
    const TileSet* getTileSetAt(const SizeT& index) const;

    /**
     * @brief Build a TileDescription for the given global tile id (GID).
     *
     * @param gid Global tile id (GID) as stored in Tiled layer data.
     *
     * @return TileDescription describing the tile's texture region and tileset
     * texture key.
     */
    TileDescription getTileDescriptionByGid(const Int32& gid) const;

    /**
     * @brief Clears all loaded tilesets.
     */
    void clear();

  private:
    /**
     * @brief Owned rk::TileSet pointers created from the parsed TMR tilesets.
     */
    Vector<TileSet*> m_tileSets;

    /**
     * @brief Check whether the provided global tile id (GID) belongs to the
     * supplied tileset.
     *
     * @param tileSet Pointer to the rk::TileSet to test (not owned).
     * @param gid Global tile id to check.
     * 
     * @return true if the gid lies within the tileset's range, false otherwise.
     */
    bool isGidInTileSetRange(
      const TileSet* tileSet,
      const Int32& gid
    ) const;
  };
}