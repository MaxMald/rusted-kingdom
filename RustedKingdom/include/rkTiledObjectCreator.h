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
}

using sf::IntRect;

namespace rk
{
  class SpriteComponentFactory;
  class GameObject;

  class TiledObjectCreator : public NonCopyable
  {
  public:
    TiledObjectCreator(SpriteComponentFactory&);
    ~TiledObjectCreator();

    GameObject* create(
      const tmr::TiledMap*,
      const tmr::Object*
    );

  private:
    SpriteComponentFactory& m_spriteComponentFactory;

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
  };
}