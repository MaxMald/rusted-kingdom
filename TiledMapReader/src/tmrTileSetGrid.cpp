#include "TMR/tmrTileSetGrid.h"

namespace tmr
{
  TileSetGrid::TileSetGrid(
    const int32_t& width,
    const int32_t& height,
    const orientation::Type& orientation
  )
    : m_width(width)
    , m_height(height)
    , m_orientation(orientation)
  {
  }

  TileSetGrid::~TileSetGrid()
  {
  }
}