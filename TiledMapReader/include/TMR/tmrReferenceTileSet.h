#pragma once

#include "TMR/tmrTileSet.h"

namespace tmr
{
  /**
   * @brief Tileset defined in an external file.
   *
   * ReferenceTileSet represents a tileset that is defined in an external file
   * and referenced from the map file.
   */
  class TMR_API ReferenceTileSet : public TileSet
  {
  public:

    /**
     * @brief Construct a new ReferenceTileSet.
     *
     * @param firstGid The first global tile ID for this tileset (as provided by
     * Tiled).
     * @param source Null-terminated path to the external tileset file. The
     * value will be copied.
     */
    ReferenceTileSet(
      const std::int32_t firstGid,
      const char* source
    );

    virtual ~ReferenceTileSet();

    /** @return source file path */
    const char* getSource() const noexcept { return m_source; }

  private:
    char* m_source;
  };
}