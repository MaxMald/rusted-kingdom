#pragma once

#include "TMR/tmrNonCopyable.h"
#include "TMR/tmrTileSetType.h"

namespace tmr
{
  /**
   * @class TileSet
   * @brief Represents a tileset from a Tiled map.
   *
   * TileSet stores tileset metadata parsed from a Tiled JSON file.
   */
  class TMR_API TileSet : public NonCopyable
  {
  public:
    /**
     * @brief Constructs a TileSet with the specified properties.
     *
     * @param margin Pixel margin around the tiles in the source image.
     * @param firstgid The first global tile id for this tileset.
     */
    TileSet(
      tileSetType::Type type,
      const int32_t& firstgid
    );

    /**
     * @brief Destroys the TileSet and releases owned string memory.
     */
    virtual ~TileSet();

    /** @return tileset type */
    tileSetType::Type getType() const noexcept { return m_type; }

    /** @return first global tile id */
    int32_t getFirstGid() const noexcept { return m_firstgid; }

  private:
    tileSetType::Type m_type;
    int32_t m_firstgid;
  };
}