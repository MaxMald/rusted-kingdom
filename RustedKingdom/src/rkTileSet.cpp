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
}