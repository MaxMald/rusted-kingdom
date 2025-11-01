#pragma once

#include "rkPrerequisites.h"
#include <filesystem>

namespace tmr
{
  class TiledMap;
}

namespace rk
{
  class TileSet;

  class TileSetsManager
  {
  public:
    TileSetsManager();
    ~TileSetsManager();

    bool load(
      const std::filesystem::path& mapRootDirectory,
      const tmr::TiledMap* tiledMap
    );

    void clear();

  private:
    std::vector<TileSet*> m_tileSets;
  };
}