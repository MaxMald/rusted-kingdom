#include "rkAssetManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <TMR/tmrJson.h>

#include "rkTiledMap.h"
#include "rkTileSet.h"
#include "rkImageCollectionTileSet.h"
#include "rkSpriteSheetTileSet.h"
#include "rkEightDirectionsSpriteSheetAnimationDescription.h"

namespace rk
{
  AssetManager::AssetManager(const char* assetDirectory)
    : m_assetDirectory(assetDirectory),
    m_textures(),
    m_tiledMaps(),
    m_eightDirectionAnimations()
  {
  }

  AssetManager::~AssetManager()
  {
    clear();
  }

  bool AssetManager::loadTexture(const String& name, const Path& filename)
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

  const Texture& AssetManager::getTexture(const String& name) const
  {
    auto it = m_textures.find(name);
    if (it != m_textures.end())
      return *(it->second);

    throw RuntimeErrorException(
      String::Format(
        "AssetManager::getTexture: Texture with name '%s' not found.",
        name.c_str()
      )
    );
  }

  Texture& AssetManager::getTexture(const String& name)
  {
    auto it = m_textures.find(name);
    if (it != m_textures.end())
      return *(it->second);

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

  const TiledMap& AssetManager::getTiledMap(const String& name) const
  {
    auto it = m_tiledMaps.find(name);
    if (it != m_tiledMaps.end())
      return *(it->second);

    throw RuntimeErrorException(
      String::Format(
        "AssetManager::getTiledMap: TiledMap with name '%s' not found.",
        name.c_str()
      )
    );
  }

  TiledMap& AssetManager::getTiledMap(const String& key)
  {
    auto it = m_tiledMaps.find(key);
    if (it != m_tiledMaps.end())
      return *(it->second);

    throw RuntimeErrorException(
      String::Format(
        "AssetManager::getTiledMap: TiledMap with name '%s' not found.",
        key.c_str()
      )
    );
  }

  bool AssetManager::loadAssetsFromTiledMap(const String& name)
  {
    TiledMap& tiledMap = getTiledMap(name);
    const TileSetsManager& tileSetmanager = tiledMap.getTileSetsManager();

    SizeT tileSetCount = tileSetmanager.getTileSetsCount();
    for (SizeT i = 0; i < tileSetCount; ++i)
    {
      const TileSet& tileSet = tileSetmanager.getTileSetAt(i);
      if (!loadAssetsFromTileSet(tileSet))
        return false;
    }

    return true;
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

  bool AssetManager::loadEightDirectionAnimationBundle(const Path& filePath)
  {
    try
    {
      Path fullPath = Path(m_assetDirectory) / filePath;

      tmr::Json json = tmr::Json::loadFromFile(fullPath.string().c_str());
      tmr::Json animations = json["animations"];

      if (!animations.isArray())
        return false;

      SizeT numAnimations = animations.getSize();
      for (SizeT i = 0; i < numAnimations; ++i)
      {
        EightDirectionsSpriteSheetAnimationDescription* animDesc = 
          new EightDirectionsSpriteSheetAnimationDescription();

        if (!animDesc->loadFromJson(animations[i]))
        {
          delete animDesc;
          return false;
        }

        String animationKey = animDesc->getAnimationKey();
        if (hasEightDirectionAnimation(animationKey))
        {
          delete animDesc;
          return false;
        }

        m_eightDirectionAnimations[animationKey] = animDesc;
      }

      return true;
    }
    catch (const std::exception&)
    {
      return false;
    }
  }

  const EightDirectionsSpriteSheetAnimationDescription&
    AssetManager::getEightDirectionAnimation(const String& key) const
  {
    auto it = m_eightDirectionAnimations.find(key);
    if (it != m_eightDirectionAnimations.end())
      return *(it->second);

    throw RuntimeErrorException(
      String::Format(
        "AssetManager::getEightDirectionAnimation: EightDirectionsSpriteSheetAnimationDescription with key '%s' not found.",
        key.c_str()
      )
    );
  }

  EightDirectionsSpriteSheetAnimationDescription& 
    AssetManager::getEightDirectionAnimation(const String& key)
  {
    auto it = m_eightDirectionAnimations.find(key);
    if (it != m_eightDirectionAnimations.end())
      return *(it->second);

    throw RuntimeErrorException(
      String::Format(
        "AssetManager::getEightDirectionAnimation: EightDirectionsSpriteSheetAnimationDescription with key '%s' not found.",
        key.c_str()
      )
    );
  }

  bool AssetManager::hasEightDirectionAnimation(const String& key) const
  {
    return m_eightDirectionAnimations.find(key) != m_eightDirectionAnimations.end();
  }

  void AssetManager::clear()
  {
    for (auto& pair : m_eightDirectionAnimations)
      delete pair.second;

    for (auto& pair : m_tiledMaps)
      delete pair.second;

    for (auto& pair : m_textures)
      delete pair.second;

    m_textures.clear();
    m_tiledMaps.clear();
    m_eightDirectionAnimations.clear();
  }

  const char* AssetManager::getAssetDirectory() const
  {
    return m_assetDirectory;
  }

  bool AssetManager::loadAssetsFromSpriteSheetTileSet(
    const SpriteSheetTileSet& tileSet
  )
  {
    const String& textureName = tileSet.getImageKey();
    const Path& texturePath = tileSet.getImageFilepath();
    if (!hasTexture(textureName))
    {
      if (!loadTexture(textureName, texturePath))
      {
        return false;
      }
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
      if (!hasTexture(textureName))
      {
        if (!loadTexture(textureName, texturePath))
        {
          return false;
        }
      }
    }
    return true;
  }
}