#include "TMR/tmrGridDataLayer.h"

#include <stdexcept>

#include "TMR/tmrData.h"

namespace tmr
{
  GridDataLayer::GridDataLayer(
    const int32_t& id,
    const char* name,
    const int32_t& width,
    const int32_t& height,
    Data* data
  ) :
    Layer(id, name, layerType::GridData),
    m_height(height),
    m_width(width),
    m_data(data)
  {
  }

  GridDataLayer::~GridDataLayer()
  {
    if (m_data)
    {
      delete m_data;
      m_data = nullptr;
    }
  }

  int32_t GridDataLayer::getDataAt(const size_t& index) const
  {
    return m_data->getDataAt(index);
  }

  int32_t GridDataLayer::getDataAt(const int32_t& column, const int32_t& row) const
  {
    if (column < 0 || column >= m_width || row < 0 || row >= m_height)
    {
      throw std::out_of_range(
        "Column or row out of range in TileMapLayer::getDataAt");
    }

    const int32_t index = row * m_width + column;
    return m_data->getDataAt(static_cast<size_t>(index));
  }
}