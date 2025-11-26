#include "rkTiledObjectCreator.h"

#include <SFML/System/Vector2.hpp>

#include <TMR/tmrTiledMap.h>
#include <TMR/tmrImageCollectionTileSet.h>
#include <TMR/tmrSpriteSheetTileSet.h>
#include <TMR/tmrTileSetTile.h>
#include <TMR/tmrObject.h>
#include <TMR/tmrEllipseObject.h>
#include <TMR/tmrTileReferenceObject.h>
#include <TMR/tmrImage.h>

#include "rkTiledMapUtilities.h"
#include "rkGameObject.h"
#include "rkSpriteComponentFactory.h"
#include "rkSpriteComponent.h"

using sf::Vector2f;
using sf::Vector2i;

namespace rk
{
  TiledObjectCreator::TiledObjectCreator(
    SpriteComponentFactory& spriteComponentFactory
  ) :
    m_spriteComponentFactory(spriteComponentFactory)
  {
  }

  TiledObjectCreator::~TiledObjectCreator()
  {
  }

  GameObject* TiledObjectCreator::create(
    const tmr::TiledMap* tmrTiledMap,
    const tmr::Object* tmrObject
  )
  {
    tmr::objectType::Type objectType = tmrObject->getObjectType();
    switch (objectType)
    {
    case tmr::objectType::Type::TileReference:
    {
      return createTileReference(
        tmrTiledMap,
        static_cast<const tmr::TileReferenceObject*>(tmrObject)
      );
    }

    default:
      return nullptr;
    }
  }

  GameObject* TiledObjectCreator::createTileReference(
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
      return createTileReferenceFromImageCollection(
        tmrTileRefObject,
        static_cast<const tmr::ImageCollectionTileSet*>(tileSet)
      );
    }
    else if (tileSet->getType() == tmr::tileSetType::Type::SpriteSheet)
    {
      return createTileReferenceFromSpriteSheet(
        tmrTileRefObject,
        static_cast<const tmr::SpriteSheetTileSet*>(tileSet)
      );
    }

    throw RuntimeErrorException(
      String::Format(
        "Unsupported tileset type: %d",
        static_cast<Int32>(tileSet->getType())
      )
    );
  }

  GameObject* TiledObjectCreator::createTileReferenceFromImageCollection(
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

    GameObject* tileGameObject = new GameObject(tmrTileRefObject->getName());
    tileGameObject->setPosition(
      Vector2f(tmrTileRefObject->getX(), tmrTileRefObject->getY())
    );

    addSpriteComponent(*tileGameObject, tile->getImage()->getSource());

    // TODO Add colliders
    return tileGameObject;
  }

  GameObject* TiledObjectCreator::createTileReferenceFromSpriteSheet(
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

    GameObject* tileGameObject = new GameObject(tmrTileRefObject->getName());
    tileGameObject->setPosition(
      Vector2f(tmrTileRefObject->getX(), tmrTileRefObject->getY())
    );

    addSpriteComponent(
      *tileGameObject,
      spriteSheet->getImage()->getSource(),
      rect
    );

    // TODO Add colliders
    return tileGameObject;
  }

  void TiledObjectCreator::addSpriteComponent(
    GameObject& gameObject,
    const String& textureKey
  )
  {
    gameObject.addComponent(
      m_spriteComponentFactory.createSpriteComponent(gameObject, textureKey)
    );
  }

  void TiledObjectCreator::addSpriteComponent(
    GameObject& gameObject,
    const String& textureKey,
    const IntRect& textureRect
  )
  {
    gameObject.addComponent(
      m_spriteComponentFactory.createSpriteComponent(
        gameObject,
        textureKey,
        textureRect
      )
    );
  }
}