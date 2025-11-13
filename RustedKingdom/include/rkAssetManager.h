#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace sf
{
  class Texture;
}

using sf::Texture;

namespace rk
{
  class TiledMap;
  class TileSet;
  class SpriteSheetTileSet;
  class ImageCollectionTileSet;
  class EightDirectionsSpriteSheetAnimationDescription;

  /**
   * @brief Manages loading and retrieval of texture assets.
   *
   * AssetManager loads textures from a specified asset directory and provides
   * access to them by name. It owns the loaded Texture objects and releases
   * them on destruction.
   */
  class AssetManager : public NonCopyable
  {
  public:
    explicit AssetManager(const char* assetDirectory);
    ~AssetManager();

    bool loadTexture(const String& key, const Path& filename);
    const Texture& getTexture(const String& key) const;
    Texture& getTexture(const String& key);
    bool hasTexture(const String& key) const;
    bool removeTexture(const String& key);

    bool loadTiledMap(const String& key, const Path& filename);
    bool hasTiledMap(const String& key) const;
    bool removeTiledMap(const String& key);
    const TiledMap& getTiledMap(const String& key) const;
    TiledMap& getTiledMap(const String& key);

    bool loadAssetsFromTiledMap(const String& key);
    bool loadAssetsFromTileSet(const TileSet& tileSet);

    bool loadEightDirectionAnimationBundle(const Path& filePath);

    const EightDirectionsSpriteSheetAnimationDescription&
      getEightDirectionAnimation(const String& key) const;
    
    EightDirectionsSpriteSheetAnimationDescription&
      getEightDirectionAnimation(const String& key);
    
    bool hasEightDirectionAnimation(const String& key) const;

    /**
     * @brief Clears all loaded textures.
     */
    void clear();

    /**
     * @brief Gets the asset directory path.
     * @return The asset directory as a C-string.
     */
    const char* getAssetDirectory() const;

  private:
    const char* m_assetDirectory;
    UnorderedMap<String, Texture*> m_textures;
    UnorderedMap<String, TiledMap*> m_tiledMaps;
    UnorderedMap<String, EightDirectionsSpriteSheetAnimationDescription*> m_eightDirectionAnimations;

    bool loadAssetsFromSpriteSheetTileSet(const SpriteSheetTileSet& tileSet);
    bool loadAssetsFromImageCollectionTileSet(const ImageCollectionTileSet& tileSet);
  };
}