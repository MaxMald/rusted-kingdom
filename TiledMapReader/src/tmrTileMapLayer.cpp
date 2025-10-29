#include "TMR/tmrTileMapLayer.h"
#include <stdexcept>

namespace tmr
{
  TileMapLayer::TileMapLayer(
    const std::int32_t& id,
    const std::int32_t& x,
    const std::int32_t& y,
    const bool& visible,
    const float& opacity,
    const char* name,
    const std::int32_t& height,
    const std::int32_t& width,
    const std::int32_t& dataSize,
    std::int32_t* data
  ) :
    MapLayer(
      mapLayerType::TileLayer,
      id,
      x,
      y,
      visible,
      opacity,
      name
    ),
    m_height(height),
    m_width(width),
    m_dataSize(dataSize),
    m_data(data)
  {
  }

  TileMapLayer::~TileMapLayer()
  {
    delete[] m_data;
  }

  const std::int32_t& TileMapLayer::getDataAt(const std::int32_t index) const
  {
    if (index < 0 || index >= m_dataSize)
    {
      throw std::out_of_range("Index out of range in TileMapLayer::getDataAt");
    }

    return m_data[index];
  }

  const std::int32_t& TileMapLayer::getDataAt(
    const std::int32_t column,
    const std::int32_t row
  ) const
  {
    if (column < 0 || column >= m_width || row < 0 || row >= m_height)
    {
      throw std::out_of_range(
        "Column or row out of range in TileMapLayer::getDataAt");
    }

    const std::int32_t index = row * m_width + column;
    return m_data[index];
  }
}