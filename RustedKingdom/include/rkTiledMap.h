#pragma once

#include "rkPrerequisites.h"
#include "rkTileSetsManager.h"

namespace rk
{
  /**
  * @class TiledMap
  * @brief Wrapper around a parsed Tiled map used by the engine.
  *
  * This class owns or references the parsed representation returned by the
  * project's TMR reader and coordinates creation/loading of engine-facing
  * tileset wrappers via rk::TileSetsManager.
  */
  class TiledMap
  {
  public:
    /**
     * @brief Constructs an empty TiledMap wrapper.
     *
     * The constructed instance is empty and must be initialized by calling
     * loadFromFile(...) before being used.
     */
    TiledMap();

    /**
     * @brief Destructor.
     */
    ~TiledMap();

    /**
     * @brief Loads a Tiled map from a file.
     *
     * @param filename Filesystem path to the Tiled map file.
     * @return true if the file was successfully parsed and the map loaded;
     *         false on error.
     */
    bool loadFromFile(const Path& filename);

  private:

    /**
     * @brief Pointer to the parsed TMR tiled map representation.
     */
    tmr::TiledMap* m_tmrTiledMap;

    /**
     * @brief Manager that loads and holds rk::TileSet wrappers for the map.
     *
     * Each TileSet holds metadata and a resolved image filepath for engine use.
     */
    TileSetsManager m_tileSetsManager;

    /**
     * @brief Clears internal state and releases resources.
     */
    void clear();
  };
}