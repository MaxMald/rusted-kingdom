#pragma once

#include "rkIAsset.h"

namespace rk
{
  /**
   * @brief Manages a collection of assets of type T.
   *
   * @tparam T Asset type, must derive from IAsset.
   */
  class AssetGroup : public NonCopyable
  {
  public:
    AssetGroup() = default;
    virtual ~AssetGroup() = default;

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
    UnorderedMap<String, SharedPtr<IAsset>> m_assets;
  };
}