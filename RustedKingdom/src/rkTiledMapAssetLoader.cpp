#include "rkTiledMapAssetsLoader.h"

#include <TMR/tmrImageCollectionTileSet.h>
#include <TMR/tmrSpriteSheetTileSet.h>
#include <TMR/tmrTileSetTile.h>
#include <TMR/tmrImage.h>
#include <TMR/tmrTiledMap.h>

#include "rkAssetManager.h"
#include "rkTexture.h"
#include "rkAssetGroup.h"
#include "rkTiledMap.h"

using tmr::ImageCollectionTileSet;
using tmr::SpriteSheetTileSet;
using tmr::TileSetTile;
using tmr::Image;

namespace rk
{
  namespace tiledMapAssetLoader
  {
    static bool loadImage(AssetManager& assetManager, const Image* image);
    static bool loadAssetsFromSpriteSheetTileSet(AssetManager& assetManager, tmr::SpriteSheetTileSet* tileSet);
    static bool loadAssetsFromImageCollection(AssetManager& assetManager, tmr::ImageCollectionTileSet* tileSet);
    static bool loadAssetsFromTileSet(AssetManager& assetManager, tmr::TileSet* tileSet);
  }
}

namespace rk
{
  namespace tiledMapAssetLoader
  {
    bool loadTiledMapAssets(
      AssetManager& assetManager,
      const String& tiledMapKey
    )
    {
      SharedPtr<rk::TiledMap> tiledMap =
        assetManager.getAssetGroup<rk::TiledMap>().get(tiledMapKey);

      tmr::TiledMap* tmrTiledMap = tiledMap->getTmrTiledMap();
      if (!tmrTiledMap)
        return false;

      SizeT tileSetsCount = tmrTiledMap->getTileSetsCount();
      for (SizeT i = 0; i < tileSetsCount; ++i)
      {
        if (!loadAssetsFromTileSet(assetManager, tmrTiledMap->getTileSetAt(i)))
          return false;
      }

      return true;
    }

    static bool loadImage(AssetManager& assetManager, const Image* image)
    {
      if (!image)
        return false;

      const char* source = image->getSource();
      if (!source)
        return false;

      TypedAssetGroup<Texture>& textureGroup = assetManager.getAssetGroup<Texture>();
      if (textureGroup.has(source))
        return true;

      return textureGroup.loadFromFile(source, source) != nullptr;
    }

    static bool loadAssetsFromSpriteSheetTileSet(
      AssetManager& assetManager,
      tmr::SpriteSheetTileSet* tileSet
    )
    {
      if (!tileSet)
        return false;

      // TODO: load spritesheet
      return loadImage(assetManager, tileSet->getImage());
    }

    static bool loadAssetsFromImageCollection(
      AssetManager& assetManager,
      tmr::ImageCollectionTileSet* tileSet
    )
    {
      if (!tileSet)
        return false;

      for (std::size_t i = 0; i < tileSet->getTileCount(); ++i)
      {
        const TileSetTile* tile = tileSet->getTileAt(i);
        if (!tile)
          continue;

        if (!loadImage(assetManager, tile->getImage()))
          return false;
      }

      return true;
    }

    static bool loadAssetsFromTileSet(
      AssetManager& assetManager,
      tmr::TileSet* tileSet
    )
    {
      if (!tileSet)
        return false;

      if (tileSet->getType() == tmr::tileSetType::SpriteSheet)
      {
        return loadAssetsFromSpriteSheetTileSet(
          assetManager,
          static_cast<tmr::SpriteSheetTileSet*>(tileSet)
        );
      }
      else if (tileSet->getType() == tmr::tileSetType::ImageCollection)
      {
        return loadAssetsFromImageCollection(
          assetManager,
          static_cast<tmr::ImageCollectionTileSet*>(tileSet)
        );
      }
      else
      {
        return false;
      }
    }
  }
}