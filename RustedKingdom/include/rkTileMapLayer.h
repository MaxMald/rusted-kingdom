#pragma once

#include <TMR/tmrTileMapLayer.h>
#include "rkMapLayer.h"

namespace rk
{
  class TileMapLayer : public MapLayer
  {
  public:

    TileMapLayer(tmr::TileMapLayer* tmrTileMapLayer);
    virtual ~TileMapLayer();

    /**
     * @brief Get the height of the tile layer in tiles.
     *
     * @return const reference to the underlying height value.
     */
    const Int32& getHeight() const
    {
      return static_cast<tmr::TileMapLayer*>(m_tmrMapLayer)->getHeight();
    }

    /**
     * @brief Get the width of the tile layer in tiles.
     *
     * @return const reference to the underlying width value.
     */
    const Int32& getWidth() const
    {
      return static_cast<tmr::TileMapLayer*>(m_tmrMapLayer)->getWidth();
    }

    /**
     * @brief Get the size of the tile data array.
     *
     * @return const reference to the underlying data size value.
     */
    const SizeT& getDataSize() const
    {
      return static_cast<tmr::TileMapLayer*>(m_tmrMapLayer)->getDataSize();
    }

    /**
     * @brief Get the tile data at the specified index.
     *
     * @param index The index of the tile data to retrieve.
     *
     * @return const reference to the tile data at the given index.
     */
    const Int32& getDataAt(const Int32& index) const
    {
      return static_cast<tmr::TileMapLayer*>(m_tmrMapLayer)->getDataAt(
        index
      );
    }

    /**
     * @brief Get the tile data at the specified column and row.
     *
     * @param column The column index of the tile.
     * @param row The row index of the tile.
     *
     * @return const reference to the tile data at the given column and row.
     */
    const Int32& getDataAt(
      const Int32& column,
      const Int32& row
    ) const
    {
      return static_cast<tmr::TileMapLayer*>(m_tmrMapLayer)->getDataAt(
        column,
        row
      );
    }

    /**
     * @brief Check if the tile data at the specified column and row is empty.
     *
     * @param column The column index of the tile.
     * @param row The row index of the tile.
     *
     * @return const reference to a boolean indicating if the tile data is
     * empty (0).
     */
    const bool& isEmptyDataAt(
      const Int32& column,
      const Int32& row
    ) const
    {
      const Int32& data = this->getDataAt(column, row);
      return data == 0;
    }
  };
}