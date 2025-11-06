#pragma once

#include "rkTileSet.h"

namespace tmr
{
  class ReferenceTileSet;
}

namespace rk
{
  class ReferenceTileSet : public TileSet
  {
  public:
    ReferenceTileSet(
      const Path& mapRootDirectory,
      const tmr::ReferenceTileSet& tmrReferenceTileSet
    );

    ~ReferenceTileSet();

    Bool isGidInRange(const Int32& gid) const override;
    TileDescription getTileDescriptionAt(const Int32& localId) const override;

  private:
    Path m_source;
  };
}