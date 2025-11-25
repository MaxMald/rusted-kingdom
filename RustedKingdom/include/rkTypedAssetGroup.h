#pragma once

#include "rkAssetGroup.h"

namespace rk
{
  /**
   * @brief Manages a collection of typed assets.
   */
  template<typename T>
  class TypedAssetGroup : public AssetGroup
  {
  public:
    TypedAssetGroup() = default;
    virtual ~TypedAssetGroup() = default;
    
    /**
     * @brief Loads an asset from file and adds it to the group.
     *
     * @param key Unique string identifier for the asset.
     * @param filename Path to the asset file.
     *
     * @return Shared pointer to the loaded asset.
     * @throws RuntimeErrorException if the key already exists or loading fails.
     */
    SharedPtr<T> loadFromFile(const String& key, const Path& filename)
    {
      if (has(key))
      {
        throw RuntimeErrorException(
          String::Format("Asset with key '{}' already exists", key.c_str())
        );
      }

      SharedPtr<T> asset = std::make_shared<T>();
      SharedPtr<IAsset> assetBase = std::static_pointer_cast<IAsset>(asset);
      if (!assetBase->loadFromFile(filename))
      {
        throw RuntimeErrorException(
          String::Format("Failed to load asset from file '{}'", filename.c_str())
        );
      }

      m_assets[key] = assetBase;
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
    const SharedPtr<T> get(const String& key) const
    {
      auto it = m_assets.find(key);
      if (it != m_assets.end())
      {
        return std::static_pointer_cast<T>(it->second);
      }

      throw RuntimeErrorException(
        String::Format("Asset with key '%s' not found", key.c_str())
      );
    }
  };
}