#pragma once

#include "rkPrerequisites.h"

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
     * @brief Clears all loaded tilesets.
     */
    void clear();

  private:
    /**
     * @brief Owned rk::TileSet pointers created from the parsed TMR tilesets.
     */
    Vector<TileSet*> m_tileSets;
  };
}