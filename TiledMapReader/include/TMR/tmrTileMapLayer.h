#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrNonCopyable.h"

namespace tmr
{
  class Data;

  /**
   * @class TileMapLayer
   * @brief Represents a tile layer in a Tiled map, storing tile data and layer
   * properties.
   */
  class TMR_API TileMapLayer : public NonCopyable
  {
  public:
    TileMapLayer(
      const std::int32_t& id,
      const char* name,
      const std::int32_t& width,
      const std::int32_t& height,
      Data* data
    );

    virtual ~TileMapLayer();

    /**
     * @brief Gets the unique identifier of the layer.
     * @return The layer ID.
     */
    const std::int32_t& getId() const { return m_id; }

    /**
     * @brief Gets the name of the layer.
     * @return The layer name as a C-style string.
     */
    const char* getName() const { return m_name; }

    /**
     * @brief Gets the height of the tile layer in tiles.
     * @return The height of the tile layer.
     */
    const std::int32_t& getHeight() const { return m_height; }

    /**
     * @brief Gets the width of the tile layer in tiles.
     * @return The width of the tile layer.
     */
    const std::int32_t& getWidth() const { return m_width; }

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
    char* m_name;             ///< The name of the layer.
    std::int32_t m_id;        ///< The unique identifier for the layer.    
    std::int32_t m_height;    ///< The height of the tile layer in tiles.
    std::int32_t m_width;     ///< The width of the tile layer in tiles.
    Data* m_data;             ///< The tile data for tile layers.
  };
}