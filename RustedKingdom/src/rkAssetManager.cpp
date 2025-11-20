#include "rkAssetManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <TMR/tmrJson.h>

#include "rkTiledMap.h"
#include "rkTileSet.h"
#include "rkSpriteSheetTileSet.h"
#include "rkImageCollectionTileSet.h"
#include "rkEightDirAnimationDesc.h"
#include "rkTexture.h"

namespace rk
{
  AssetManager::AssetManager() :
    m_assetDirectory(),
    m_assetGroups()
  {
    //String assetsPath = "C:/Users/nuup2/OneDrive/Documentos/Repositories/MaxMald/rusted-kingdom/assets";
    m_assetDirectory = "F:/Repositories/MaxMald/rusted-kingdom/assets";
  }

  AssetManager::~AssetManager()
  {
  }

  bool AssetManager::loadAssetsFromTiledMap(const String& name)
  {
    SharedPtr<TiledMap> tiledMap = getAssetGroup<TiledMap>().get(name);
    const TileSetsManager& tileSetmanager = tiledMap->getTileSetsManager();

    SizeT tileSetCount = tileSetmanager.getTileSetsCount();
    for (SizeT i = 0; i < tileSetCount; ++i)
    {
      const TileSet& tileSet = tileSetmanager.getTileSetAt(i);
      if (!loadAssetsFromTileSet(tileSet))
        return false;
    }

    return true;
  }

  void AssetManager::unloadAll()
  {
    for (auto& pair : m_assetGroups)
      pair.second->unloadAll();
  }

  const Path& AssetManager::getAssetDirectory() const
  {
    return m_assetDirectory;
  }

  Path AssetManager::combineAssetDirectoryWithPath(const Path& relativePath) const
  {
    return Path(m_assetDirectory) / relativePath;
  }

  void AssetManager::init(ServiceLocator&)
  {
    registerAssetGroups();
  }

  void AssetManager::destroy()
  {
    unloadAll();
  }

  bool AssetManager::loadAssetsFromTileSet(const TileSet& tileSet)
  {
    tmr::tileSetType::Type tileSetType = tileSet.getType();
    if (tileSetType == tmr::tileSetType::SpriteSheet)
    {
      return loadAssetsFromSpriteSheetTileSet(
        static_cast<const SpriteSheetTileSet&>(tileSet)
      );
    }

    else if (tileSetType == tmr::tileSetType::ImageCollection)
    {
      return loadAssetsFromImageCollectionTileSet(
        static_cast<const ImageCollectionTileSet&>(tileSet)
      );
    }

    return true;
  }

  bool AssetManager::loadAssetsFromSpriteSheetTileSet(
    const SpriteSheetTileSet& tileSet
  )
  {
    const String& textureName = tileSet.getImageKey();
    const Path& texturePath = tileSet.getImageFilepath();    
    TypedAssetGroup<Texture>& textureGroup = getAssetGroup<Texture>();
    if (!textureGroup.has(textureName))
    {
      if (!textureGroup.loadFromFile(textureName, texturePath))
        return false;
    }
    return true;
  }

  bool AssetManager::loadAssetsFromImageCollectionTileSet(
    const ImageCollectionTileSet& tileSet
  )
  {
    const Vector<TileSetTile>& tiles = tileSet.getTiles();
    for (const TileSetTile& tile : tiles)
    {
      const String& textureName = tile.getImagePath().string();
      const Path& texturePath = tile.getImagePath();
      TypedAssetGroup<Texture>& textureGroup = getAssetGroup<Texture>();
      if (!textureGroup.has(textureName))
      {
        if (!textureGroup.loadFromFile(textureName, texturePath))
          return false;
      }
    }
    return true;
  }

  void AssetManager::registerAssetGroups()
  {
    m_assetGroups[typeid(Texture)] = MakeShared<TypedAssetGroup<Texture>>();
    m_assetGroups[typeid(TiledMap)] = MakeShared<TypedAssetGroup<TiledMap>>();
    m_assetGroups[typeid(EightDirAnimationDesc)] = MakeShared<TypedAssetGroup<EightDirAnimationDesc>>();
  }
}