#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  class Image;
  class TiledMap;
  class TileSet;
  class TileSetTile;
  class ReferenceTileSet;
  class SpriteSheetTileSet;
  class ImageCollectionTileSet;

  /**
   * @brief Provides functions for embedding and loading tilesets in a Tiled map.
   */
  namespace tileSetsEmbedder
  {
    /**
     * @brief Embeds all external tilesets into the given TiledMap instance.
     *
     * Loads and attaches tileset data from external sources referenced in the map file.
     * After calling this function, the TiledMap will contain all tileset data locally.
     *
     * @param tiledMap Reference to the TiledMap to embed tilesets into.
     * @param tiledMapPath Path to the Tiled map file.
     */
    TMR_API void embedTileSets(TiledMap& tiledMap, const char* tiledMapPath);

    /**
     * @brief Loads a tileset from a reference in the Tiled map.
     *
     * @param tiledMapPath Path to the Tiled map file.
     * @param tileSet Pointer to the ReferenceTileSet to load.
     * @return Pointer to the loaded TileSet, or nullptr on failure.
     */
    TMR_API TileSet* loadTileSetFromReference(
      const char* tiledMapPath,
      ReferenceTileSet* tileSet
    );

    TMR_API void resolveTileSetPaths(
      TileSet* tileSet,
      const char* tileSetSourcePath
    );

    TMR_API void resolveSpriteSheetTileSetPaths(
      SpriteSheetTileSet* tileSet,
      const char* tileSetSourcePath
    );

    TMR_API void resolveImageCollectionTileSetPaths(
      ImageCollectionTileSet* tileSet,
      const char* tileSetSourcePath
    );

    TMR_API void resolveTileSetTilePath(
      TileSetTile* tile,
      const char* tileSetSourcePath
    );

    TMR_API void resolveImagePath(
      Image* image,
      const char* tileSetSourcePath
    );
  }
}