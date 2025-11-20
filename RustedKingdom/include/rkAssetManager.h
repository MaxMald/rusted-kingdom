#pragma once

#include "rkIService.h"
#include "rkAssetGroup.h"
#include "rkEightDirAnimationDesc.h"
#include "rkTiledMap.h"
#include "rkTexture.h"

namespace rk
{
  class TileSet;
  class SpriteSheetTileSet;
  class ImageCollectionTileSet;
  //class EightDirAnimationDesc;
  //class Texture;
  //class TiledMap;

  using TextureGroup = AssetGroup<Texture>;
  using EightDirAnimationDescGroup = AssetGroup<EightDirAnimationDesc>;
  using TiledMapGroup = AssetGroup<TiledMap>;

  class AssetManager : public IService
  {
  public:
    AssetManager();
    virtual ~AssetManager();

    const Path& getAssetDirectory() const;
    Path combineAssetDirectoryWithPath(const Path& relativePath) const;

    TextureGroup& getTextureGroup() { return m_textureGroup; }
    const TextureGroup& getTextureGroup() const { return m_textureGroup; }
    TiledMapGroup& getTiledMapGroup() { return m_tiledMapGroup; }
    EightDirAnimationDescGroup& getEightDirAnimationDescGroup() { return m_eightDirAnimationDescGroup; }
    const EightDirAnimationDescGroup& getEightDirAnimationDescGroup() const { return m_eightDirAnimationDescGroup; }

    bool loadAssetsFromTiledMap(const String& key);
    bool loadAssetsFromTileSet(const TileSet& tileSet);

    void unloadAll();

  protected:
    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void destroy() override;

  private:
    Path m_assetDirectory;
    TextureGroup m_textureGroup;
    TiledMapGroup m_tiledMapGroup;
    EightDirAnimationDescGroup m_eightDirAnimationDescGroup;

    bool loadAssetsFromSpriteSheetTileSet(const SpriteSheetTileSet& tileSet);
    bool loadAssetsFromImageCollectionTileSet(const ImageCollectionTileSet& tileSet);
  };
}