#include "rkTiledObjectSpriteDescriptorFactory.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <TMR/tmrTiledMap.h>
#include <TMR/tmrImageCollectionTileSet.h>
#include <TMR/tmrSpriteSheetTileSet.h>
#include <TMR/tmrTileSetTile.h>
#include <TMR/tmrImage.h>

#include "rkTiledMapUtilities.h"

using sf::Vector2f;
using sf::Vector2i;
using sf::IntRect;

namespace rk
{
  namespace tiledObjectSpriteDescriptorFactory
  {
    static TiledObjectSpriteDescriptor createFromImageCollection(
      Int32 gid,
      const tmr::ImageCollectionTileSet* tileSet
    );

    static TiledObjectSpriteDescriptor createFromSpriteSheet(
      Int32 gid,
      const tmr::SpriteSheetTileSet* tileSet
    );
  }
}

namespace rk
{
  namespace tiledObjectSpriteDescriptorFactory
  {
    TiledObjectSpriteDescriptor create(
      Int32 gid,
      const tmr::TiledMap* tiledMap
    )
    {
      const tmr::TileSet* tileset = tiledMapUtilities::getTileSetWithGid(tiledMap, gid);
      tmr::tileSetType::Type type = tileset->getType();

      if (type == tmr::tileSetType::Type::ImageCollection)
      {
        return createFromImageCollection(
          gid,
          static_cast<const tmr::ImageCollectionTileSet*>(tileset)
        );
      }
      else if (type == tmr::tileSetType::Type::SpriteSheet)
      {
        return createFromSpriteSheet(
          gid,
          static_cast<const tmr::SpriteSheetTileSet*>(tileset)
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

    static TiledObjectSpriteDescriptor createFromImageCollection(
      Int32 gid,
      const tmr::ImageCollectionTileSet* tileSet
    )
    {
      Int32 localId = gid - tileSet->getFirstGid();
      const tmr::TileSetTile* tile = tileSet->getTileAt(
        static_cast<SizeT>(localId)
      );

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
      const tmr::SpriteSheetTileSet* tileSet
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

      return TiledObjectSpriteDescriptor(
        gid,
        tileSet->getImage()->getSource(),
        rect,
        Vector2f(0.0f, 0.0f)
      );
    }
  }
}