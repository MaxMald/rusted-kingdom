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
    void embedTileSets(TiledMap& tiledMap, const char* rootPath)
    {
      size_t tileSetsCount = tiledMap.getTileSetsCount();
      for (size_t i = 0; i < tileSetsCount; ++i)
      {
        TileSet* tileSet = tiledMap.getTileSetAt(i);

        if (tileSet->getType() != tileSetType::Reference)
          continue;

        TileSet* loadedTileSet = loadTileSetFromReference(
          rootPath,
          static_cast<ReferenceTileSet*>(tileSet)
        );

        if (loadedTileSet == nullptr)
          continue;

        tiledMap.replaceTileSetAt(i, loadedTileSet);
      }
    }

    TileSet* loadTileSetFromReference(
      const char* rootPath,
      ReferenceTileSet* tileSet
    )
    {
      if (tileSet == nullptr || rootPath == nullptr)
        return nullptr;

      const char* sourcePath = tileSet->getSource();
      char* tileSetAbsolutePath = pathUtilities::combinePaths(rootPath, sourcePath);

      TileSet* loadedTileSet = tileSetXmlLoader::loadFromFile(
        tileSetAbsolutePath,
        tileSet->getFirstGid()
      );

      char* tileSetDirectoryPath = pathUtilities::getDirectoryFromPath(
        tileSetAbsolutePath
      );

      resolveTileSetPaths(loadedTileSet, tileSetDirectoryPath);

      delete[] tileSetAbsolutePath;
      delete[] tileSetDirectoryPath;

      return loadedTileSet;
    }

    void resolveTileSetPaths(TileSet* tileSet, const char* tileSetDirectoryPath)
    {
      if (tileSet == nullptr || tileSetDirectoryPath == nullptr)
        return;

      if (tileSet->getType() == tileSetType::SpriteSheet)
      {
        resolveSpriteSheetTileSetPaths(
          static_cast<SpriteSheetTileSet*>(tileSet),
          tileSetDirectoryPath
        );
      }
      else if (tileSet->getType() == tileSetType::ImageCollection)
      {
        resolveImageCollectionTileSetPaths(
          static_cast<ImageCollectionTileSet*>(tileSet),
          tileSetDirectoryPath
        );
      }
    }

    void resolveSpriteSheetTileSetPaths(
      SpriteSheetTileSet* tileSet,
      const char* tileSetDirectoryPath
    )
    {
      if (tileSet == nullptr || tileSetDirectoryPath == nullptr)
        return;

      Image* image = tileSet->getImage();
      if (image == nullptr)
        return;

      resolveImagePath(image, tileSetDirectoryPath);
    }

    void resolveImageCollectionTileSetPaths(
      ImageCollectionTileSet* tileSet,
      const char* tileSetDirectoryPath
    )
    {
      if (tileSet == nullptr || tileSetDirectoryPath == nullptr)
        return;

      size_t tileCount = tileSet->getTileCount();
      for (size_t i = 0; i < tileCount; ++i)
        resolveTileSetTilePath(tileSet->getTileAt(i), tileSetDirectoryPath);
    }

    void resolveTileSetTilePath(TileSetTile* tile, const char* tileSetDirectoryPath)
    {
      if (tile == nullptr || tileSetDirectoryPath == nullptr)
        return;

      Image* image = tile->getImage();
      if (image == nullptr)
        return;

      resolveImagePath(image, tileSetDirectoryPath);
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