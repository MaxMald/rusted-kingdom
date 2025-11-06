#pragma once

#include <TMR/tmrTileSetType.h>
#include "rkPrerequisites.h"
#include "rkTileDescription.h"

namespace rk
{
  class TileSet
  {
  public:
    TileSet(
      const tmr::tileSetType::Type& type,
      const Int32& firstGuid
    );
    virtual ~TileSet();

    /**
     * @brief Checks if the provided GID is within this tileset's GID range.
     * @param gid Global tile ID to check.
     * @return true if the GID is within range, false otherwise.
     */
    virtual Bool isGidInRange(const Int32& gid) const = 0;

    /**
     * @brief Retrieves the TileDescription for a tile given its local ID.
     * @param localId Local tile ID within this tileset.
     * @return TileDescription corresponding to the local ID.
     */
    virtual TileDescription getTileDescriptionAt(const Int32& localId) const = 0;

    Int32 getFirstGid() const { return m_firstGuid; }
    tmr::tileSetType::Type getType() const { return m_type; }

  private:
    Int32 m_firstGuid;
    tmr::tileSetType::Type m_type;
  };
}
