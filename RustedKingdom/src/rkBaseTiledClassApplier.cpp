#include "rkBaseTiledClassApplier.h"

#include <SFML/System/Vector2.hpp>

#include <TMR/tmrObject.h>
#include <TMR/tmrTiledMap.h>
#include <TMR/tmrImageCollectionTileSet.h>
#include <TMR/tmrSpriteSheetTileSet.h>
#include <TMR/tmrTileSetTile.h>
#include <TMR/tmrObjectGroup.h>
#include <TMR/tmrEllipseObject.h>
#include <TMR/tmrTileReferenceObject.h>
#include <TMR/tmrImage.h>

#include "rkGameObject.h"
#include "rkTiledMapUtilities.h"
#include "rkSpriteComponentFactory.h"
#include "rkTiledColliderComponentFactory.h"
#include "rkColliderComponentFactory.h"
#include "rkSpriteComponent.h"
#include "rkColliderComponent.h"

using sf::Vector2i;
using sf::Vector2f;

namespace rk
{
  BaseTiledClassApplier::BaseTiledClassApplier()
  {
  }

  BaseTiledClassApplier::~BaseTiledClassApplier()
  {
  }

  void BaseTiledClassApplier::apply(
    GameObject& gameObject,
    const tmr::Object* tmrObject,
    const tmr::TiledMap* tmrTiledMap
  )
  {
    tmr::objectType::Type objectType = tmrObject->getObjectType();

    switch (objectType)
    {
      case tmr::objectType::Type::TileReference:
      {
        createTileReference(
          gameObject,
          tmrTiledMap,
          static_cast<const tmr::TileReferenceObject*>(tmrObject)
        );
      }
    }
  }

  void BaseTiledClassApplier::createTileReference(
    GameObject& gameObject,
    const tmr::TiledMap* tmrTiledMap,
    const tmr::TileReferenceObject* tmrTileRefObject
  )
  {
    const tmr::TileSet* tileSet = tiledMapUtilities::getTileSetWithGid(
      tmrTiledMap,
      tmrTileRefObject->getGid()
    );

    if (tileSet->getType() == tmr::tileSetType::Type::ImageCollection)
    {
      createTileReferenceFromImageCollection(
        gameObject,
        tmrTileRefObject,
        static_cast<const tmr::ImageCollectionTileSet*>(tileSet)
      );
    }
    else if (tileSet->getType() == tmr::tileSetType::Type::SpriteSheet)
    {
      createTileReferenceFromSpriteSheet(
        gameObject,
        tmrTileRefObject,
        static_cast<const tmr::SpriteSheetTileSet*>(tileSet)
      );
    }
    else
    {
      throw RuntimeErrorException(
        String::Format(
          "Unsupported tileset type: %d",
          static_cast<Int32>(tileSet->getType())
        )
      );
    }
  }

  void BaseTiledClassApplier::createTileReferenceFromImageCollection(
    GameObject& gameObject,
    const tmr::TileReferenceObject* tmrTileRefObject,
    const tmr::ImageCollectionTileSet* imageCollection
  )
  {
    Int32 localTileId = static_cast<Int32>(tmrTileRefObject->getGid()) -
      imageCollection->getFirstGid();

    const tmr::TileSetTile* tile =
      imageCollection->getTileAt(static_cast<std::size_t>(localTileId));

    if (tile == nullptr)
    {
      throw RuntimeErrorException(
        String::Format(
          "Tile with local ID %d not found in Image Collection tileset %s",
          localTileId,
          imageCollection->getName()
        )
      );
    }

    gameObject.setPosition(
      Vector2f(tmrTileRefObject->getX(), tmrTileRefObject->getY())
    );

    addSpriteComponent(gameObject, tile->getImage()->getSource());
    addColliders(gameObject, tile->getObjectGroup(), "plantas");
  }

  void BaseTiledClassApplier::createTileReferenceFromSpriteSheet(
    GameObject& gameObject,
    const tmr::TileReferenceObject* tmrTileRefObject,
    const tmr::SpriteSheetTileSet* spriteSheet
  )
  {
    Int32 localId = static_cast<Int32>(tmrTileRefObject->getGid()) -
      spriteSheet->getFirstGid();

    Int32 tileWidth = static_cast<Int32>(spriteSheet->getTileWidth());
    Int32 tileHeight = static_cast<Int32>(spriteSheet->getTileHeight());
    Int32 columns = static_cast<Int32>(spriteSheet->getColumns());

    Int32 tileColumn = localId % columns;
    Int32 tileRow = localId / columns;
    Int32 x = tileWidth * tileColumn;
    Int32 y = tileHeight * tileRow;

    IntRect rect(
      Vector2i(x, y),
      Vector2i(tileWidth, tileHeight)
    );

    gameObject.setPosition(
      Vector2f(tmrTileRefObject->getX(), tmrTileRefObject->getY())
    );

    addSpriteComponent(gameObject, spriteSheet->getImage()->getSource(), rect);
    // TODO Add colliders for sprite sheets.
  }

  void BaseTiledClassApplier::addSpriteComponent(
    GameObject& gameObject,
    const String& textureKey
  )
  {
    gameObject.addComponent(
      spriteComponentFactory::createSpriteComponent(gameObject, textureKey)
    );
  }

  void BaseTiledClassApplier::addSpriteComponent(
    GameObject& gameObject,
    const String& textureKey,
    const IntRect& textureRect
  )
  {
    gameObject.addComponent(
      spriteComponentFactory::createSpriteComponent(
        gameObject,
        textureKey,
        textureRect
      )
    );
  }
  void BaseTiledClassApplier::addColliders(
    GameObject& gameObject,
    const tmr::ObjectGroup* objectGroup,
    const String& colliderGroupKey
  )
  {
    if (objectGroup == nullptr)
      return;

    SizeT objectCount = objectGroup->getObjectSize();
    for (SizeT i = 0; i < objectCount; ++i)
    {
      const tmr::Object* collider = objectGroup->getObjectAt(static_cast<UInt32>(i));
      if (!collider)
        continue;

      UniquePtr<ColliderComponent> colliderComponent =
        tiledColliderComponentFactory::create(
          collider,
          gameObject,
          colliderGroupKey
        );

      if (!colliderComponent)
        continue;

      gameObject.addComponent(std::move(colliderComponent));

      return; // Only one collider per object is supported for now
    }
  }
}