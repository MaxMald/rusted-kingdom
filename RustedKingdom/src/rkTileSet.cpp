#include "rkTileSet.h"
#include <TMR/tmrTileSet.h>

namespace rk
{
  TileSet::TileSet(
    const Path& mapRootDirectory,
    const tmr::TileSet* tmrTileSet
  ) :
    m_tmrTileSet(tmrTileSet)
  {
    const char* imageC = tmrTileSet->getImage();
    Path imagePath = imageC ?
      Path(imageC) :
      Path();

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
    m_name = tmrTileSet->getName();
  }

  TileSet::~TileSet()
  {
    // Does not own m_tmrTileSet; do not delete.
  }

  sf::IntRect TileSet::getTileTextureRect(const Int32& localId) const
  {
    const UInt32 columns = getColumns();
    const UInt32 tileWidth = getTileWidth();
    const UInt32 tileHeight = getTileHeight();
    const UInt32 spacing = getSpacing();
    const UInt32 margin = getMargin();

    const UInt32 xIndex = localId % columns;
    const UInt32 yIndex = localId / columns;
    const UInt32 textureXPostion = xIndex * (tileWidth + spacing) + margin;
    const UInt32 textureYPosition = yIndex * (tileHeight + spacing) + margin;

    sf::Vector2i position(textureXPostion, textureYPosition);

    return sf::IntRect(
      sf::Vector2i(textureXPostion, textureYPosition),
      sf::Vector2i(tileWidth, tileHeight)
    );
  }
}