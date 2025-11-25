#include "rkTiledObjectSpriteDescriptorFactory.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <TMR/tmrTiledMap.h>
#include <TMR/tmrImageCollectionTileSet.h>
#include <TMR/tmrSpriteSheetTileSet.h>
#include <TMR/tmrTileSetTile.h>
#include <TMR/tmrImage.h>

using sf::Vector2f;
using sf::Vector2i;
using sf::IntRect;

namespace rk
{
  namespace tiledObjectSpriteDescriptorFactory
  {
    static tmr::TileSet* getTileSetWithGid(
      tmr::TiledMap* tiledMap,
      Int32 gid
    );

    static TiledObjectSpriteDescriptor createFromImageCollection(
      Int32 gid,
      tmr::TiledMap* tiledMap,
      tmr::ImageCollectionTileSet* tileSet
    );

    static TiledObjectSpriteDescriptor createFromSpriteSheet(
      Int32 gid,
      tmr::TiledMap* tiledMap,
      tmr::SpriteSheetTileSet* tileSet
    );
  }
}

namespace rk
{
  namespace tiledObjectSpriteDescriptorFactory
  {
    TiledObjectSpriteDescriptor create(
      Int32 gid,
      tmr::TiledMap* tiledMap
    )
    {
      tmr::TileSet* tileset = getTileSetWithGid(tiledMap, gid);
      tmr::tileSetType::Type type = tileset->getType();

      if (type == tmr::tileSetType::Type::ImageCollection)
      {
        return createFromImageCollection(
          gid,
          tiledMap,
          static_cast<tmr::ImageCollectionTileSet*>(tileset)
        );
      }
      else if (type == tmr::tileSetType::Type::SpriteSheet)
      {
        return createFromSpriteSheet(
          gid,
          tiledMap,
          static_cast<tmr::SpriteSheetTileSet*>(tileset)
        );
      }
      else
      {
        throw RuntimeErrorException(
          String::Format(
            "Unsupported tileset type: %d",
            static_cast<Int32>(type)
          )
        );
      }
    }

    static tmr::TileSet* getTileSetWithGid(tmr::TiledMap* tiledMap, Int32 gid)
    {
      SizeT tileSetCount = tiledMap->getTileSetsCount();
      for (SizeT i = 0; i < tileSetCount; ++i)
      {
        tmr::TileSet* tileSet = tiledMap->getTileSetAt(i);

        Int32 tileSetLastGid =
          tileSet->getFirstGid() + static_cast<Int32>(tileSet->getSize());

        if (gid >= tileSet->getFirstGid() && gid < tileSetLastGid)
          return tileSet;
      }

      throw RuntimeErrorException(
        String::Format("No tileset found for GID %d", gid)
      );
    }

    static TiledObjectSpriteDescriptor createFromImageCollection(
      Int32 gid,
      tmr::TiledMap* tiledMap,
      tmr::ImageCollectionTileSet* tileSet
    )
    {
      Int32 localId = gid - tileSet->getFirstGid();
      tmr::TileSetTile* tile = tileSet->getTileAt(static_cast<SizeT>(localId));

      if (tile == nullptr)
      {
        throw RuntimeErrorException(
          String::Format(
            "No tile found in ImageCollectionTileSet for local ID %d",
            localId
          )
        );
      }

      IntRect rect(
        Vector2i(0, 0),
        Vector2i(
          static_cast<Int32>(tileSet->getTileWidth()),
          static_cast<Int32>(tileSet->getTileHeight())
        )
      );

      return TiledObjectSpriteDescriptor(
        gid,
        tile->getImage()->getSource(),
        rect,
        Vector2f(0.0f, 0.0f)
      );
    }

    static TiledObjectSpriteDescriptor createFromSpriteSheet(
      Int32 gid,
      tmr::TiledMap* tiledMap,
      tmr::SpriteSheetTileSet* tileSet
    )
    {
      Int32 localId = gid - tileSet->getFirstGid();
      Int32 tileWidth = static_cast<Int32>(tileSet->getTileWidth());
      Int32 tileHeight = static_cast<Int32>(tileSet->getTileHeight());
      Int32 columns = static_cast<Int32>(tileSet->getColumns());

      Int32 tileColumn = localId % columns;
      Int32 tileRow = localId / columns;

      Int32 x = tileWidth * tileColumn;
      Int32 y = tileHeight * tileRow;

      IntRect rect(
        Vector2i(x, y),
        Vector2i(tileWidth, tileHeight)
      );
      ;
      return TiledObjectSpriteDescriptor(
        gid,
        tileSet->getImage()->getSource(),
        rect,
        Vector2f(0.0f, 0.0f)
      );
    }
  }
}