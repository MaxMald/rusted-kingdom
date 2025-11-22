#include "rkSpriteSheetTileSet.h"

#include <TMR/tmrSpriteSheetTileSet.h>

#include "rkAssertions.h"
#include "rkTiledImage.h"

namespace rk
{
  SpriteSheetTileSet::SpriteSheetTileSet(
    const Path& mapRootDirectory,
    const tmr::SpriteSheetTileSet& tmrSpriteSheetTileSet
  ) :
    TileSet(
      tmrSpriteSheetTileSet.getType(),
      tmrSpriteSheetTileSet.getFirstGid()
    ),
    m_name(tmrSpriteSheetTileSet.getName()),
    m_image(nullptr),
    m_margin(tmrSpriteSheetTileSet.getMargin()),
    m_columns(tmrSpriteSheetTileSet.getColumns()),
    m_spacing(tmrSpriteSheetTileSet.getSpacing()),
    m_tileCount(tmrSpriteSheetTileSet.getTileCount()),
    m_tileHeight(tmrSpriteSheetTileSet.getTileHeight()),
    m_tileWidth(tmrSpriteSheetTileSet.getTileWidth())
  {
    m_image = new TiledImage(tmrSpriteSheetTileSet.getImage());
  }

  SpriteSheetTileSet::~SpriteSheetTileSet()
  {
    if (m_image)
    {
      delete m_image;
      m_image = nullptr;
    }
  }

  Bool SpriteSheetTileSet::isGidInRange(const Int32& gid) const
  {
    const Int32 firstGid = getFirstGid();
    return (gid >= firstGid && gid < firstGid + static_cast<Int32>(m_tileCount));
  }

  TileDescription SpriteSheetTileSet::getTileDescriptionAt(
    const Int32& localId
  ) const
  {
    assertions::assertIndexInRange(localId, static_cast<Int32>(m_tileCount), "tile local id");

    return TileDescription(
      m_imageKey,
      getTileTextureRect(localId)
    );
  }

  sf::IntRect SpriteSheetTileSet::getTileTextureRect(const Int32& localId) const
  {
    const UInt32 xIndex = localId % m_columns;
    const UInt32 yIndex = localId / m_columns;
    const UInt32 textureXPostion = xIndex * (m_tileWidth + m_spacing) + m_margin;
    const UInt32 textureYPosition = yIndex * (m_tileHeight + m_spacing) + m_margin;

    sf::Vector2i position(textureXPostion, textureYPosition);

    return sf::IntRect(
      sf::Vector2i(textureXPostion, textureYPosition),
      sf::Vector2i(m_tileWidth, m_tileHeight)
    );
  }
}