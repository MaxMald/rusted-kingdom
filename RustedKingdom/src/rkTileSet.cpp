#include "rkTileSet.h"
#include <TMR/tmrTileSet.h>

namespace rk
{
  TileSet::TileSet(
    const tmr::tileSetType::Type& type,
    const Int32& firstGuid
  ) :
    m_type(type),
    m_firstGuid(firstGuid)
  {
  }

  TileSet::~TileSet()
  {
  }
}