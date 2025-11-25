#pragma once

#include "TMR/tmrLayer.h"

namespace tmr
{
  class Data;

  class TMR_API GridDataLayer : public Layer
  {
  public:
    GridDataLayer(
      const int32_t& id,
      const char* name,
      const int32_t& width,
      const int32_t& height,
      Data* data
    );

    virtual ~GridDataLayer();

    /**
     * @brief Gets the height of the tile layer in tiles.
     * @return The height of the tile layer.
     */
    const int32_t& getHeight() const { return m_height; }

    /**
     * @brief Gets the width of the tile layer in tiles.
     * @return The width of the tile layer.
     */
    const int32_t& getWidth() const { return m_width; }

    /**
     * @brief Gets the tile data at the specified index.
     * @param index The index of the tile data to retrieve.
     * @return The tile data at the given index.
     */
    int32_t getDataAt(const size_t& index) const;

    /**
     * @brief Gets the tile data at the specified column and row.
     *
     * @param column The column index of the tile.
     * @param row The row index of the tile.
     *
     * @return The tile data at the given column and row.
     */
    int32_t getDataAt(const int32_t& column, const int32_t& row) const;

  private:
    int32_t m_height;    ///< The height of the tile layer in tiles.
    int32_t m_width;     ///< The width of the tile layer in tiles.
    Data* m_data;        ///< The tile data for tile layers.
  };
}