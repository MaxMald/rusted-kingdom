#include "rkAssetManager.h"
#include <SFML/Graphics/Texture.hpp>

namespace rk
{
  AssetManager::AssetManager(const char* assetDirectory)
    : m_assetDirectory(assetDirectory)
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