#pragma once

#include "TMR/tmrNonCopyable.h"
#include "TMR/tmrOrientation.h"

namespace tmr
{
  /**
   * @brief Represents the grid layout of a TileSet.
   *
   * TileSetGrid encapsulates the dimensions and orientation of a tile grid used
   * in a TileSet.
   */
  class TMR_API TileSetGrid : public NonCopyable
  {
  public:
     /**
     * @brief Construct a new TileSetGrid.
     *
     * @param tileWidth Width of a single tile in pixels.
     * @param tileHeight Height of a single tile in pixels.
     */
    TileSetGrid(
      const int32_t& width,
      const int32_t& height,
      const orientation::Type& orientation
    );

    ~TileSetGrid();

    /** @return grid width. */
    int32_t getWidth() const noexcept { return m_width; }

    /** @return grid height. */
    int32_t getHeight() const noexcept { return m_height; }

    /** @return grid orientation. */
    orientation::Type getOrientation() const noexcept { return m_orientation; }

  private:
    int32_t m_width;
    int32_t m_height;
    orientation::Type m_orientation;
  };
}