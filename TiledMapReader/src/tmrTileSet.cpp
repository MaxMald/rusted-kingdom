#include "TMR/tmrTileSet.h"


namespace tmr
{
  TileSet::TileSet(
    tileSetType::Type type,
    const std::int32_t& firstgid
  ) :
    m_type(type),
    m_firstgid(firstgid)
  {
  }

  TileSet::~TileSet()
  {
  }
}