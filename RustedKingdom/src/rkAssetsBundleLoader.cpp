#include "rkPrerequisites.h"

#include "rkTiledMapAssetsLoader.h"
#include "rkAssetManager.h"
#include "rkTypedAssetGroup.h"
#include "rkJson.h"
#include "rkAssetsBundleItem.h"
#include "rkTexture.h"
#include "rkTiledMap.h"
#include "rkEightDirAnimationDesc.h"

namespace rk
{
  namespace assetsBundleLoader
  {
    static constexpr const char* TEXTURES_NAME = "textures";
    static constexpr const char* TILED_MAPS_NAME = "tiledMaps";
    static constexpr const char* EIGHT_DIR_ANIMATION_DESCS_NAME = "eightDirAnimationDescriptors";

    static bool loadTextures(const Json& texturesJson, AssetManager&);
    static bool loadTiledMaps(const Json& tiledMapsJson, AssetManager&);
    static bool loadEightDirAnimationDescs(
      const Json& eightDirAnimationDescsJson,
      AssetManager&
    );

    static AssetsBundleItem parseAssetsBundleItem(
      const Json& itemJson
    );
  }
}

namespace rk
{
  namespace assetsBundleLoader
  {
    bool loadAssetsBundle(
      const Path& bundleFilePath,
      AssetManager& assetManager
    )
    {
      Json bundle = Json::loadFromFile(bundleFilePath);

      if (bundle.contains(TEXTURES_NAME))
      {
        if (!loadTextures(bundle[TEXTURES_NAME], assetManager))
        {
          return false;
        }
      }

      if (bundle.contains(TILED_MAPS_NAME))
      {
        if (!loadTiledMaps(bundle[TILED_MAPS_NAME], assetManager))
        {
          return false;
        }
      }

      if (bundle.contains(EIGHT_DIR_ANIMATION_DESCS_NAME))
      {
        if (!loadEightDirAnimationDescs(
          bundle[EIGHT_DIR_ANIMATION_DESCS_NAME],
          assetManager
        ))
        {
          return false;
        }
      }

      return true;
    }

    static bool loadTextures(
      const Json& texturesJson,
      AssetManager& assetsManager
    )
    {
      if (!texturesJson.isArray())
        return false;

      TypedAssetGroup<Texture>& textures =
        assetsManager.getAssetGroup<Texture>();

      SizeT size = texturesJson.getSize();
      for (Int32 i = 0; i < static_cast<Int32>(size); ++i)
      {
        AssetsBundleItem item = parseAssetsBundleItem(texturesJson[i]);
        if (!textures.loadFromFile(
          item.getKey(),
          assetsManager.combineAssetDirectoryWithPath(item.getPath())
        ))
          return false;
      }
      return true;
    }

    static bool loadTiledMaps(
      const Json& tiledMapsJson,
      AssetManager& assetsManager
    )
    {
      if (!tiledMapsJson.isArray())
        return false;

      TypedAssetGroup<TiledMap>& tiledMaps =
        assetsManager.getAssetGroup<TiledMap>();

      SizeT size = tiledMapsJson.getSize();
      for (Int32 i = 0; i < static_cast<Int32>(size); ++i)
      {
        AssetsBundleItem item = parseAssetsBundleItem(tiledMapsJson[i]);
        if (!tiledMaps.loadFromFile(
          item.getKey(),
          assetsManager.combineAssetDirectoryWithPath(item.getPath())
        ))
          return false;

        if (!tiledMapAssetLoader::loadTiledMapAssets(assetsManager, item.getKey()))
          return false;
      }
      return true;
    }

    static bool loadEightDirAnimationDescs(
      const Json& eightDirAnimationDescsJson,
      AssetManager& assetsManager
    )
    {
      if (!eightDirAnimationDescsJson.isArray())
        return false;

      TypedAssetGroup<EightDirAnimationDesc>& eightDirAnimationDescs =
        assetsManager.getAssetGroup<EightDirAnimationDesc>();

      SizeT size = eightDirAnimationDescsJson.getSize();
      for (Int32 i = 0; i < static_cast<Int32>(size); ++i)
      {
        AssetsBundleItem item =
          parseAssetsBundleItem(eightDirAnimationDescsJson[i]);

        if (!eightDirAnimationDescs.loadFromFile(
          item.getKey(),
          assetsManager.combineAssetDirectoryWithPath(item.getPath())
        ))
          return false;
      }
      return true;
    }

    AssetsBundleItem parseAssetsBundleItem(const Json& itemJson)
    {
      if (!itemJson.isObject())
        throw LogicErrorException("Invalid AssetsBundleItem JSON format.");

      if (!itemJson.contains("key") || !itemJson.contains("path"))
        throw LogicErrorException("AssetsBundleItem JSON missing required fields.");

      const Json& keyJson = itemJson["key"];
      const Json& pathJson = itemJson["path"];

      if (!keyJson.isString() || !pathJson.isString())
        throw LogicErrorException("AssetsBundleItem fields must be strings.");

      String key = keyJson.getString();
      String pathStr = pathJson.getString();
      Path path(pathStr.c_str());

      return AssetsBundleItem(key, path);
    }
  }
}