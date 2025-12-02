#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "rkITiledClassApplier.h"

namespace tmr
{
  class TileReferenceObject;
  class ImageCollectionTileSet;
  class SpriteSheetTileSet;
  class ObjectGroup;
}

using sf::IntRect;

namespace rk
{
  class TiledColliderComponentFactory;
  class SpriteComponentFactory;

  class BaseTiledClassApplier : public ITiledClassApplier
  {
  public:
    BaseTiledClassApplier(SpriteComponentFactory&, TiledColliderComponentFactory&);
    virtual ~BaseTiledClassApplier();

    void apply(GameObject&, const tmr::Object*, const tmr::TiledMap*) override;

  protected:
    SpriteComponentFactory& m_spriteComponentFactory;
    TiledColliderComponentFactory& m_tiledColliderComponentFactory;

  private:
    void createTileReference(
      GameObject&,
      const tmr::TiledMap*,
      const tmr::TileReferenceObject*
    );

    void createTileReferenceFromImageCollection(
      GameObject&,
      const tmr::TileReferenceObject*,
      const tmr::ImageCollectionTileSet*
    );

    void createTileReferenceFromSpriteSheet(
      GameObject&,
      const tmr::TileReferenceObject*,
      const tmr::SpriteSheetTileSet*
    );

    void addSpriteComponent(GameObject&, const String& textureKey);
    void addSpriteComponent(
      GameObject&,
      const String& textureKey,
      const IntRect& textureRect
    );

    void addColliders(
      GameObject&,
      const tmr::ObjectGroup*,
      const String& colliderGroupKey
    );
  };
}