#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace tmr
{
  class TiledMap;
  class TileReferenceObject;
  class ImageCollectionTileSet;
  class SpriteSheetTileSet;
  class Object;
  class ObjectGroup;
}

using sf::IntRect;

namespace rk
{
  class TiledColliderComponentFactory;
  class SpriteComponentFactory;
  class GameObject;

  class TiledObjectCreator : public NonCopyable
  {
  public:
    TiledObjectCreator(
      SpriteComponentFactory&,
      TiledColliderComponentFactory&
    );
    ~TiledObjectCreator();

    GameObject* create(
      const tmr::TiledMap*,
      const tmr::Object*
    );

    void setColliderGroupKey(const String& colliderGroupKey) { m_colliderGroupKey = colliderGroupKey; }

  private:
    String m_colliderGroupKey;
    SpriteComponentFactory& m_spriteComponentFactory;
    TiledColliderComponentFactory& m_tiledColliderComponentFactory;

    GameObject* createTileReference(
      const tmr::TiledMap*,
      const tmr::TileReferenceObject*
    );

    GameObject* createTileReferenceFromImageCollection(
      const tmr::TileReferenceObject*,
      const tmr::ImageCollectionTileSet*
    );

    GameObject* createTileReferenceFromSpriteSheet(
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
      const tmr::ObjectGroup*,
      GameObject&,
      const String& colliderGroupKey
    );
  };
}