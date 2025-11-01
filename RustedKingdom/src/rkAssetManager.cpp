#include "rkAssetManager.h"
#include <SFML/Graphics/Texture.hpp>
#include "rkTiledMap.h"
#include "rkTileSet.h"

namespace rk
{
  AssetManager::AssetManager(const char* assetDirectory)
    : m_assetDirectory(assetDirectory),
    m_textures(),
    m_tiledMaps()
  {
  }

  AssetManager::~AssetManager()
  {
    clear();
  }

  bool AssetManager::loadTexture(
    const String& name,
    const Path& filename
  )
  {
    if (hasTexture(name))
      return false;

    Texture* texture = new Texture();
    Path fullPath = Path(m_assetDirectory) / filename.c_str();
    if (!texture->loadFromFile(fullPath.c_str()))
    {
      delete texture;
      return false;
    }

    m_textures[name] = texture;
    return true;
  }

  bool AssetManager::loadTiledMap(
    const String& name,
    const Path& filename
  )
  {
    if (hasTiledMap(name))
      return false;

    TiledMap* tiledMap = new TiledMap();
    Path fullPath = Path(m_assetDirectory) / filename.c_str();

    if (!tiledMap->loadFromFile(fullPath))
    {
      delete tiledMap;
      return false;
    }

    m_tiledMaps[name] = tiledMap;
    return true;
  }

  bool AssetManager::hasTiledMap(const String& name) const
  {
    return m_tiledMaps.find(name) != m_tiledMaps.end();
  }

  bool AssetManager::removeTiledMap(const String& name)
  {
    auto it = m_tiledMaps.find(name);

    if (it != m_tiledMaps.end())
    {
      delete it->second;
      m_tiledMaps.erase(it);
      return true;
    }

    return false;
  }

  Texture* AssetManager::getTexture(const String& name) const
  {
    auto it = m_textures.find(name);
    if (it != m_textures.end())
      return it->second;

    throw RuntimeErrorException(
      String::Format(
        "AssetManager::getTexture: Texture with name '%s' not found.",
        name.c_str()
      )
    );
  }

  bool AssetManager::hasTexture(const String& name) const
  {
    return m_textures.find(name) != m_textures.end();
  }

  bool AssetManager::removeTexture(const String& name)
  {
    auto it = m_textures.find(name);

    if (it != m_textures.end())
    {
      delete it->second;
      m_textures.erase(it);
      return true;
    }

    return false;
  }

  TiledMap* AssetManager::getTiledMap(const String& name) const
  {
    auto it = m_tiledMaps.find(name);
    if (it != m_tiledMaps.end())
      return it->second;

    throw RuntimeErrorException(
      String::Format(
        "AssetManager::getTiledMap: TiledMap with name '%s' not found.",
        name.c_str()
      )
    );
  }

  bool AssetManager::loadAssetsFromTiledMap(const String& name)
  {
    TiledMap* tiledMap = getTiledMap(name);
    const TileSetsManager& tileSetmanager = tiledMap->getTileSetsManager();

    SizeT tileSetCount = tileSetmanager.getTileSetsCount();
    for (SizeT i = 0; i < tileSetCount; ++i)
    {
      const TileSet* tileSet = tileSetmanager.getTileSetAt(i);

      const String& textureName = tileSet->getImageKey();
      const Path& texturePath = tileSet->getImageFilepath();
      if (!hasTexture(textureName))
      {
        if (!loadTexture(textureName, texturePath))
        {
          return false;
        }
      }
    }
  }

  void AssetManager::clear()
  {
    for (auto& pair : m_textures)
    {
      delete pair.second;
    }

    m_textures.clear();
  }

  const char* AssetManager::getAssetDirectory() const
  {
    return m_assetDirectory;
  }
}