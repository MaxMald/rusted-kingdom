#pragma once

#include "TMR/tmrMapLayer.h"

namespace tmr
{
  /**
   * @class TileMapLayer
   * @brief Represents a tile layer in a Tiled map, storing tile data and layer
   * properties.
   */
  class TMR_API TileMapLayer : public MapLayer
  {
  public:

    /**
     * @brief Constructs a TileMapLayer with the specified properties and tile
     * data.
     * @param id The unique identifier for the layer.
     * @param x The x-coordinate of the layer.
     * @param y The y-coordinate of the layer.
     * @param visible Whether the layer is visible.
     * @param opacity The opacity of the layer (0.0f to 1.0f).
     * @param name The name of the layer.
     * @param height The height of the tile layer in tiles.
     * @param width The width of the tile layer in tiles.
     * @param dataSize The size of the tile data array.
     * @param data Pointer to the tile data array. Ownership is transferred to
     * the TileMapLayer.
     *
     * The constructor initializes all layer properties and takes ownership of
     * the provided tile data array. The array will be deleted when the
     * TileMapLayer is destroyed.
     */
    TileMapLayer(
      const std::int32_t& id,
      const std::int32_t& x,
      const std::int32_t& y,
      const bool& visible,
      const float& opacity,
      const char* name,
      const std::int32_t& width,
      const std::int32_t& height,
      const std::size_t& dataSize,
      std::int32_t* data
    );

    virtual ~TileMapLayer();

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
     * @brief Gets the size of the tile data array.
     * @return The size of the data array.
     */
    const std::size_t& getDataSize() const { return m_dataSize; }

    /**
     * @brief Gets the tile data at the specified index.
     * @param index The index of the tile data to retrieve.
     * @return The tile data at the given index.
     */
    const std::int32_t& getDataAt(const std::int32_t index) const;

    /**
     * @brief Gets the tile data at the specified column and row.
     *
     * @param column The column index of the tile.
     * @param row The row index of the tile.
     *
     * @return The tile data at the given column and row.
     */
    const std::int32_t& getDataAt(
      const std::int32_t column,
      const std::int32_t row
    ) const;

  private:
    std::int32_t m_height;    ///< The height of the tile layer in tiles.
    std::int32_t m_width;     ///< The width of the tile layer in tiles.
    std::size_t m_dataSize;   ///< The size of the tile data array.
    std::int32_t* m_data;     ///< The tile data for tile layers.
  };
}