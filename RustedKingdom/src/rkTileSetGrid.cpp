#include "rkTileSetGrid.h"
#include <TMR/tmrTileSetGrid.h>

namespace rk
{
  TileSetGrid::TileSetGrid(const tmr::TileSetGrid& tmrTileSetGrid)
    : m_width{ tmrTileSetGrid.getWidth() }
    , m_height{ tmrTileSetGrid.getHeight() }
    , m_orientation{ tmrTileSetGrid.getOrientation() }
  {
  }

  TileSetGrid::~TileSetGrid()
  {
  }
}