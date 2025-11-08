#pragma once

#include "rkPrerequisites.h"

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
  class AssetManager
  {
  public:
    /**
     * @brief Constructs an AssetManager with the given asset directory.
     *
     * @param assetDirectory Path to the directory containing assets.
     */
    explicit AssetManager(const char* assetDirectory);

    /**
     * @brief Destructor. Releases all loaded textures.
     */
    ~AssetManager();

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = delete;
    AssetManager& operator=(AssetManager&&) = delete;

    /**
     * @brief Loads a texture from file and stores it by name.
     * @param name The key/name to associate with the texture.
     * @param filename The file path to load the texture from.
     * @return True if loading succeeded, false otherwise.
     */
    bool loadTexture(const String& name, const Path& filename);

    /**
     * @brief Retrieves a texture by name.
     * @param name The key/name of the texture.
     * @return Pointer to the texture, or nullptr if not found.
     */
    Texture* getTexture(const String& name) const;

    /**
     * @brief Checks if a texture with the given name exists.
     * @param name The key/name of the texture.
     * @return True if the texture exists, false otherwise.
     */
    bool hasTexture(const String& name) const;

    /**
     * @brief Removes a texture by name.
     * @param name The key/name of the texture.
     * @return True if the texture was removed, false if not found.
     */
    bool removeTexture(const String& name);

    /**
     * @brief Loads a tiled map from file and stores by name.
     */
    bool loadTiledMap(const String& key, const Path& filename);

    /**
     * @brief Retrieves a tiled map by name.
     * @param name The key/name of the tiled map.
     */
    bool hasTiledMap(const String& key) const;

    /**
     * @brief Removes a tiled map by name.
     * @param name The key/name of the tiled map.
     */
    bool removeTiledMap(const String& key);

    /**
     * @brief Retrieves a tiled map by name.
     * @param name The key/name of the tiled map.
     * @return Pointer to the tiled map, or nullptr if not found.
     */
    TiledMap* getTiledMap(const String& key) const;

    /**
     * @brief Loads all assets (textures) referenced by the specified tiled map.
     * @param name The key/name of the tiled map.
     * @return True if all assets were loaded successfully, false otherwise.
     */
    bool loadAssetsFromTiledMap(const String& name);

    /**
     * @brief Loads all assets (textures) referenced by the specified tile set.
     * @param tileSet The tile set to load assets from.
     * @return True if all assets were loaded successfully, false otherwise.
     */
    bool loadAssetsFromTileSet(const TileSet& tileSet);

    /**
     * @brief Loads an eight-direction animation bundle from the specified directory.
     * @param directory The directory containing the animation frames.
     * @return True if loading succeeded, false otherwise.
     */
    bool loadEightDirectionAnimationBundle(const Path& filePath);

    /**
     * @brief Retrieves an eight-direction animation description by name.
     * @param name The key/name of the animation.
     * @return Pointer to the animation description, or nullptr if not found.
     */
    EightDirectionsSpriteSheetAnimationDescription* getEightDirectionAnimation(
      const String& key
    ) const;

    /**
     * @brief Checks if an eight-direction animation with the given name exists.
     * @param name The key/name of the animation.
     * @return True if the animation exists, false otherwise.
     */
    bool hasEightDirectionAnimation(
      const String& key
    ) const;

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