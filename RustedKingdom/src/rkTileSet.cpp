#include "rkTileSet.h"
#include <TMR/tmrTileSet.h>

namespace rk
{
  TileSet::TileSet(
    const std::filesystem::path& mapRootDirectory,
    const tmr::TileSet* tmrTileSet
  ) :
    m_tmrTileSet(tmrTileSet)
  {
    const char* imageC = tmrTileSet->getImage();
    std::filesystem::path imagePath = imageC ?
      std::filesystem::path(imageC) :
      std::filesystem::path();

    std::filesystem::path finalPath;
    if (imagePath.is_absolute())
    {
      finalPath = imagePath;
    }
    else
    {
      finalPath = mapRootDirectory / imagePath;
    }

    m_imageFilepath = finalPath;
    m_imageKey = finalPath.lexically_normal().string();
    m_name = tmrTileSet->getName();
  }

  TileSet::~TileSet()
  {
  }
}