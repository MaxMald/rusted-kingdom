#include "TMR/tmrTileSet.h"


namespace tmr
{
  TileSet::TileSet(
    tileSetType::Type type,
    const int32_t& firstgid,
    const size_t& size
  ) :
    m_type(type),
    m_firstgid(firstgid),
    m_size(size)
  {
  }

  TileSet::~TileSet()
  {
  }
}