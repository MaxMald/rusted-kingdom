#pragma once

#include "rkPrerequisites.h"
#include "rkTileSetsManager.h"
#include <filesystem>

namespace rk
{
  class TileSet;

  class TiledMap
  {
  public:
    TiledMap();
    ~TiledMap();

    bool loadFromFile(const std::filesystem::path& filename);

  private:

    tmr::TiledMap* m_tmrTiledMap;
    TileSetsManager m_tileSetsManager;
    
    void clear();
  };
}