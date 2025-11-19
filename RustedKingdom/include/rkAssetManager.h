#pragma once

#include "rkIService.h"

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

  class AssetManager : public IService
  {
  public:
    AssetManager();
    virtual ~AssetManager();

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

    void clear();
    const Path& getAssetDirectory() const;

  protected:
    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void destroy() override;

  private:
    Path m_assetDirectory;
    UnorderedMap<String, Texture*> m_textures;
    UnorderedMap<String, TiledMap*> m_tiledMaps;
    UnorderedMap<String, EightDirectionsSpriteSheetAnimationDescription*> m_eightDirectionAnimations;

    bool loadAssetsFromSpriteSheetTileSet(const SpriteSheetTileSet& tileSet);
    bool loadAssetsFromImageCollectionTileSet(const ImageCollectionTileSet& tileSet);
  };
}