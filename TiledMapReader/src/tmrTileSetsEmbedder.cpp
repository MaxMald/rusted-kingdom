#include "TMR/tmrTileSetsEmbedder.h"

#include "TMR/tmrTiledMap.h"
#include "TMR/tmrTileSet.h"
#include "TMR/tmrTileSetTile.h"
#include "TMR/tmrReferenceTileSet.h"
#include "TMR/tmrPathUtilities.h"
#include "TMR/tmrTileSetXmlLoader.h"
#include "TMR/tmrImageCollectionTileSet.h"
#include "TMR/tmrSpriteSheetTileSet.h"
#include "TMR/tmrImage.h"

namespace tmr
{
  namespace tileSetsEmbedder
  {
    void embedTileSets(TiledMap& tiledMap, const char* tiledMapPath)
    {
      size_t tileSetsCount = tiledMap.getTileSetsCount();
      for (size_t i = 0; i < tileSetsCount; ++i)
      {
        TileSet* tileSet = tiledMap.getTileSetAt(i);

        if (tileSet->getType() != tileSetType::Reference)
          continue;

        TileSet* loadedTileSet = loadTileSetFromReference(
          tiledMapPath,
          static_cast<ReferenceTileSet*>(tileSet)
        );

        if (loadedTileSet == nullptr)
          continue;

        tiledMap.replaceTileSetAt(i, loadedTileSet);
      }
    }

    TileSet* loadTileSetFromReference(
      const char* tiledMapPath,
      ReferenceTileSet* tileSet
    )
    {
      if (tileSet == nullptr || tiledMapPath == nullptr)
        return nullptr;

      const char* sourcePath = tileSet->getSource();
      char* tileSetPath = pathUtilities::combinePaths(tiledMapPath, sourcePath);

      TileSet* loadedTileSet = tileSetXmlLoader::loadFromFile(
        tileSetPath,
        tileSet->getFirstGid()
      );

      delete[] tileSetPath;

      resolveTileSetPaths(loadedTileSet, sourcePath);

      return loadedTileSet;
    }

    void resolveTileSetPaths(TileSet* tileSet, const char* tileSetSourcePath)
    {
      if (tileSet == nullptr || tileSetSourcePath == nullptr)
        return;

      if (tileSet->getType() == tileSetType::SpriteSheet)
      {
        resolveSpriteSheetTileSetPaths(
          static_cast<SpriteSheetTileSet*>(tileSet),
          tileSetSourcePath
        );
      }
      else if (tileSet->getType() == tileSetType::ImageCollection)
      {
        resolveImageCollectionTileSetPaths(
          static_cast<ImageCollectionTileSet*>(tileSet),
          tileSetSourcePath
        );
      }
    }

    void resolveSpriteSheetTileSetPaths(
      SpriteSheetTileSet* tileSet,
      const char* tileSetSourcePath
    )
    {
      if (tileSet == nullptr || tileSetSourcePath == nullptr)
        return;

      Image* image = tileSet->getImage();
      if (image == nullptr)
        return;

      resolveImagePath(image, tileSetSourcePath);
    }

    void resolveImageCollectionTileSetPaths(
      ImageCollectionTileSet* tileSet,
      const char* tileSetSourcePath
    )
    {
      if (tileSet == nullptr || tileSetSourcePath == nullptr)
        return;

      size_t tileCount = tileSet->getTileCount();
      for (size_t i = 0; i < tileCount; ++i)
        resolveTileSetTilePath(tileSet->getTileAt(i), tileSetSourcePath);
    }

    void resolveTileSetTilePath(TileSetTile* tile, const char* tileSetSourcePath)
    {
      if (tile == nullptr || tileSetSourcePath == nullptr)
        return;

      Image* image = tile->getImage();
      if (image == nullptr)
        return;

      resolveImagePath(image, tileSetSourcePath);
    }
  
    void resolveImagePath(Image* image, const char* tileSetSourcePath)
    {
      if (image == nullptr || tileSetSourcePath == nullptr)
        return;

      const char* imageSource = image->getSource();
      char* imagePath = pathUtilities::combinePaths(tileSetSourcePath, imageSource);

      image->setSource(imagePath);

      delete[] imagePath;
    }
  }
}