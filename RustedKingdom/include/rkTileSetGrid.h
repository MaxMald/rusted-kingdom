#pragma once

#include <TMR/tmrOrientation.h>
#include "rkPrerequisites.h"

namespace tmr
{
  class TileSetGrid;
}

namespace rk
{
  class TileSetGrid
  {
  public:

    TileSetGrid(const tmr::TileSetGrid& tmrTileSetGrid);
    ~TileSetGrid();

    Int32 getWidth() const { return m_width; }
    Int32 getHeight() const { return m_height; }
    tmr::orientation::Type getOrientation() const { return m_orientation; }

  private:
    Int32 m_width;
    Int32 m_height;
    tmr::orientation::Type m_orientation;
  };
}