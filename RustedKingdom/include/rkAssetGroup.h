#pragma once

#include "rkIAsset.h"

namespace rk
{
  /**
   * @brief Manages a collection of assets of type T.
   *
   * @tparam T Asset type, must derive from IAsset.
   */
  template<typename T>
  class AssetGroup : public NonCopyable
  {
  public:
    AssetGroup() = default;
    virtual ~AssetGroup() = default;

    /**
     * @brief Loads an asset from file and adds it to the group.
     *
     * @param key Unique string identifier for the asset.
     * @param filename Path to the asset file.
     * 
     * @return Shared pointer to the loaded asset.
     * @throws RuntimeErrorException if the key already exists or loading fails.
     */
    SharedPtr<T> loadFromFile(const String& key, const String& filename)
    {
      if (has(key))
      {
        throw RuntimeErrorException(
          String::Format("Asset with key '{}' already exists", key)
        );
      }

      SharedPtr<T> asset = std::make_shared<T>();
      if (!asset->loadFromFile(filename))
      {
        throw RuntimeErrorException(
          String::Format("Failed to load asset from file '{}'", filename)
        );
      }

      m_assets[key] = asset;
      return asset;
    }

    /**
     * @brief Retrieves an asset by key.
     *
     * @param key Unique string identifier for the asset.
     * 
     * @return Shared pointer to the asset.
     * @throws RuntimeErrorException if the asset is not found.
     */
    SharedPtr<T> get(const String& key)
    {
      auto it = m_assets.find(key);
      if (it != m_assets.end())
      {
        return std::static_pointer_cast<T>(it->second);
      }

      throw RuntimeErrorException(
        String::Format("Asset with key '{}' not found", key)
      );
    }

    /**
     * @brief Adds an existing asset to the group.
     *
     * @param key Unique string identifier for the asset.
     * @param asset Shared pointer to the asset.
     * 
     * @throws RuntimeErrorException if the key already exists.
     */
    void add(const String& key, SharedPtr<IAsset> asset)
    {
      if (has(key))
      {
        throw RuntimeErrorException(
          String::Format("Asset with key '{}' already exists", key)
        );
      }

      m_assets[key] = asset;
    }

    /**
     * @brief Checks if an asset exists for the given key.
     *
     * @param key Unique string identifier for the asset.
     * 
     * @return True if the asset exists, false otherwise.
     */
    bool has(const String& key) const
    {
      return m_assets.find(key) != m_assets.end();
    }

    /**
     * @brief Unloads and removes an asset by key.
     *
     * @param key Unique string identifier for the asset.
     */
    void unload(const String& key)
    {
      auto it = m_assets.find(key);
      if (it != m_assets.end())
      {
        it->second->unload();
        m_assets.erase(it);
      }
    }

    /**
     * @brief Unloads and removes all assets.
     */
    void unloadAll()
    {
      for (auto& pair : m_assets)
        pair.second->unload();
      m_assets.clear();
    }

  protected:
    UnorderedMap<String, SharedPtr<IAsset>> m_assets;
  };
}