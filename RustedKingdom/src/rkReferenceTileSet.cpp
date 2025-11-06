#include "rkReferenceTileSet.h"

#include <TMR/tmrReferenceTileSet.h>

namespace rk
{
  ReferenceTileSet::ReferenceTileSet(
    const Path& mapRootDirectory,
    const tmr::ReferenceTileSet& tmrReferenceTileSet
  ) :
    TileSet(
      tmrReferenceTileSet.getType(),
      tmrReferenceTileSet.getFirstGid()
    ),
    m_source((mapRootDirectory / Path(tmrReferenceTileSet.getSource())))
  {
  }

  ReferenceTileSet::~ReferenceTileSet()
  {
  }

  Bool ReferenceTileSet::isGidInRange(const Int32& gid) const
  {
    return false;
  }

  TileDescription ReferenceTileSet::getTileDescriptionAt(
    const Int32& localId) const
  {
    throw RuntimeErrorException(
      "ReferenceTileSet::getTileDescriptionAt: Not implemented for Reference Tile Sets."
    );
  }
}