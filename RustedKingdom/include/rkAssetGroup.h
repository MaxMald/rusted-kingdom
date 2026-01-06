#pragma once

#include "rkIAsset.h"

namespace rk
{
  /**
   * @brief Manages a collection of assets.
   */
  class AssetGroup : public NonCopyable
  {
  public:
    AssetGroup();
    AssetGroup(const String name);
    virtual ~AssetGroup() = default;

    /**
     * @brief Gets the name of the asset group.
     * 
     * @return Reference to the asset group name.
     */
    const String& getName() const;

    /**
     * @brief Retrieves all asset keys in the group.
     * 
     * @return Vector of all asset keys.
     */
    Vector<String> getAllAssetKeys() const;

    /**
     * @brief Retrieves all assets in the group.
     * 
     * @return Vector of shared pointers to all assets.
     */
    Vector<SharedPtr<IAsset>> getAllAssets() const;

    /**
     * @brief Gets the number of assets in the group.
     */
    SizeT getSize() const;

    /**
     * @brief Checks if an asset exists for the given key.
     *
     * @param key Unique string identifier for the asset.
     * 
     * @return True if the asset exists, false otherwise.
     */
    bool has(const String& key) const;

    /**
     * @brief Unloads and removes an asset by key.
     *
     * @param key Unique string identifier for the asset.
     */
    void unload(const String& key);

    /**
     * @brief Unloads and removes all assets.
     */
    void unloadAll();

  protected:
    String m_groupName;
    UnorderedMap<String, SharedPtr<IAsset>> m_assets;
  };
}