#include "rkAssetManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <TMR/tmrJson.h>

#include "rkTiledMap.h"
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

  void AssetManager::registerAssetGroups()
  {
    m_assetGroups[typeid(Texture)] = MakeShared<TypedAssetGroup<Texture>>();
    m_assetGroups[typeid(TiledMap)] = MakeShared<TypedAssetGroup<TiledMap>>();
    m_assetGroups[typeid(EightDirAnimationDesc)] = MakeShared<TypedAssetGroup<EightDirAnimationDesc>>();
  }
}