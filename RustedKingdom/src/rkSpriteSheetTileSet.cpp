#include "rkSpriteSheetTileSet.h"

#include <TMR/tmrSpriteSheetTileSet.h>

#include "rkAssertions.h"

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
    m_imageKey(),
    m_imageFilepath(),
    m_margin(tmrSpriteSheetTileSet.getMargin()),
    m_columns(tmrSpriteSheetTileSet.getColumns()),
    m_imageHeight(tmrSpriteSheetTileSet.getImageHeight()),
    m_imageWidth(tmrSpriteSheetTileSet.getImageWidth()),
    m_spacing(tmrSpriteSheetTileSet.getSpacing()),
    m_tileCount(tmrSpriteSheetTileSet.getTileCount()),
    m_tileHeight(tmrSpriteSheetTileSet.getTileHeight()),
    m_tileWidth(tmrSpriteSheetTileSet.getTileWidth())
  {
    const char* imageC = tmrSpriteSheetTileSet.getImage();
    Path imagePath = imageC ? Path(imageC) : Path();

    Path finalPath;
    if (imagePath.is_absolute())
    {
      finalPath = imagePath;
    }
    else
    {
      finalPath = mapRootDirectory / imagePath;
    }

    m_imageFilepath = finalPath;
    m_imageKey = finalPath.lexically_normal().string().c_str();
  }

  SpriteSheetTileSet::~SpriteSheetTileSet()
  {
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