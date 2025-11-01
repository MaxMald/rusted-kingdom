#pragma once

#include "rkPrerequisites.h"
#include <filesystem>

using std::filesystem::path;

namespace sf
{ 
  class Texture;
}

using sf::Texture;

namespace rk
{
  class TiledMap;

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
    bool loadTexture(const String& name, const String& filename);

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
    bool loadTiledMap(const String& name, const String& filename);

    bool hasTiledMap(const String& name);

    bool removeTiledMap(const String& name);

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
  };
}