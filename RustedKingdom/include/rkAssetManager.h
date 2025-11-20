#pragma once

#include "rkIService.h"
#include "rkTypedAssetGroup.h"

namespace rk
{
  class TileSet;
  class SpriteSheetTileSet;
  class ImageCollectionTileSet;

  /**
   * @brief Manages loading, retrieval, and organization of game assets.
   *
   * AssetManager provides access to asset groups by type, handles asset
   * directory management.
   */
  class AssetManager : public IService
  {
  public:
    AssetManager();
    virtual ~AssetManager();

    /**
     * @brief Gets the root directory where assets are stored.
     * 
     * @return Reference to the asset directory path.
     */
    const Path& getAssetDirectory() const;

    /**
     * @brief Combines the asset directory with a relative path.
     * 
     * @param relativePath Path relative to the asset directory.
     * 
     * @return Combined absolute path.
     */
    Path combineAssetDirectoryWithPath(const Path& relativePath) const;

    /**
     * @brief Retrieves the asset group for the specified asset type.
     * 
     * @tparam T Asset type, must derive from IAsset.
     * 
     * @return Reference to the asset group for type T.
     * @throws RuntimeErrorException if the asset group is not found.
     */
    template<typename T>
    TypedAssetGroup<T>& getAssetGroup()
    {
      static_assert(
        IsBaseOf<IAsset, T>::value,
        "T must derive from IAsset"
      );

      TypeIndex typeIndex = typeid(T);
      auto it = m_assetGroups.find(typeIndex);
      if (it == m_assetGroups.end())
      {
        throw RuntimeErrorException(
          String::Format("Asset group for type %s not found.", typeIndex.name())
        );
      }

      SharedPtr<TypedAssetGroup<T>> typedGroup =
        std::static_pointer_cast<TypedAssetGroup<T>>(it->second);

      return *typedGroup;
    }

    /**
     * @brief Retrieves the asset group for the specified asset type (const
     * version).
     * 
     * @tparam T Asset type, must derive from IAsset.
     * 
     * @return Const reference to the asset group for type T.
     * @throws RuntimeErrorException if the asset group is not found.
     */
    template<typename T>
    const TypedAssetGroup<T>& getAssetGroup() const
    {
      static_assert(
        IsBaseOf<IAsset, T>::value,
        "T must derive from IAsset"
        );

      TypeIndex typeIndex = typeid(T);
      auto it = m_assetGroups.find(typeIndex);
      if (it == m_assetGroups.end())
      {
        throw RuntimeErrorException(
          String::Format("Asset group for type %s not found.", typeIndex.name())
        );
      }

      SharedPtr<TypedAssetGroup<T>> typedGroup =
        std::static_pointer_cast<TypedAssetGroup<T>>(it->second);

      return *typedGroup;
    }

    /**
     * @brief Loads all assets referenced by the specified tiled map.
     * 
     * @param key Unique string identifier for the tiled map.
     * 
     * @return True if assets were loaded successfully, false otherwise.
     */
    bool loadAssetsFromTiledMap(const String& key);

    /**
     * @brief Unloads all assets managed by the AssetManager.
     */
    void unloadAll();

  protected:
    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void destroy() override;

  private:
    Path m_assetDirectory;
    UnorderedMap<TypeIndex, SharedPtr<AssetGroup>> m_assetGroups;

    // TODO this type of loaders should be handle by other kind of class.
    bool loadAssetsFromTileSet(const TileSet& tileSet);
    bool loadAssetsFromSpriteSheetTileSet(const SpriteSheetTileSet& tileSet);
    bool loadAssetsFromImageCollectionTileSet(const ImageCollectionTileSet& tileSet);

    void registerAssetGroups();
  };
}