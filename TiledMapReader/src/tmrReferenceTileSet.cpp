#include "TMR/tmrReferenceTileSet.h"
#include <memory>

namespace tmr
{
  ReferenceTileSet::ReferenceTileSet(
    const std::int32_t firstGid,
    const char* source
  ) :
    TileSet(tileSetType::Reference, firstGid, 0)
  {
    m_source = source ? new char[std::strlen(source) + 1] : nullptr;
    if (m_source)
      std::strcpy(m_source, source);
  }

  ReferenceTileSet::~ReferenceTileSet()
  {
    delete[] m_source;
  }
}