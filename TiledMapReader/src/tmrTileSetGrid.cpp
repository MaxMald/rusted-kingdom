#include "TMR/tmrTileSetGrid.h"

namespace tmr
{
  TileSetGrid::TileSetGrid(
    const std::int32_t& width,
    const std::int32_t& height,
    const orientation::Type& orientation
  )
    : m_width(width)
    , m_height(height)
    , m_orientation(orientation)
  {
  }

  TileSetGrid::TileSetGrid(const TileSetGrid& other) :
    m_width(other.m_width),
    m_height(other.m_height),
    m_orientation(other.m_orientation)
  {
  }

  TileSetGrid::~TileSetGrid()
  {
  }
}