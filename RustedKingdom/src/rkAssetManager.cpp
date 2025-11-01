#include "rkAssetManager.h"
#include <SFML/Graphics/Texture.hpp>
#include "rkTiledMap.h"

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
    const String& filename
  )
  {
    if (hasTexture(name))
      return false;

    Texture* texture = new Texture();
    String fullPath = String::Format("%s/%s", m_assetDirectory, filename.c_str());
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
    const String& filename
  )
  {
    if (hasTiledMap(name))
      return false;

    TiledMap* tiledMap = new TiledMap();
    path fullPath = path(m_assetDirectory) / filename.c_str();

    // Attempt to load; if loading fails clean up and return false
    if (!tiledMap->loadFromFile(fullPath))
    {
      delete tiledMap;
      return false;
    }

    // Store the successfully loaded map
    m_tiledMaps[name] = tiledMap;
    return true;
  }

  bool AssetManager::hasTiledMap(const String& name)
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

    return nullptr;
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