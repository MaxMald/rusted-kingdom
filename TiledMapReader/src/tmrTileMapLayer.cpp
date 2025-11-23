#include "TMR/tmrTileMapLayer.h"

#include <stdexcept>

#include "TMR/tmrData.h"

namespace tmr
{
  TileMapLayer::TileMapLayer(
    const std::int32_t& id,
    const char* name,
    const std::int32_t& width,
    const std::int32_t& height,
    Data* data
  ) :
    m_id(id),
    m_height(height),
    m_width(width),
    m_data(data)
  {
    m_name = name ? new char[std::strlen(name) + 1] : nullptr;
    if (m_name)
      std::strcpy(m_name, name);
  }

  TileMapLayer::~TileMapLayer()
  {
    if (m_data)
    {
      delete m_data;
      m_data = nullptr;
    }

    if (m_name)
    {
      delete[] m_name;
      m_name = nullptr;
    }
  }

  int32_t TileMapLayer::getDataAt(const size_t& index) const
  {
    return m_data->getDataAt(index);
  }

  int32_t TileMapLayer::getDataAt(const int32_t& column, const int32_t& row) const
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