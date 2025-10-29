#include "TMR/tmrMapLayer.h"
#include <cstring>
#include <stdexcept>

namespace tmr
{
  MapLayer::MapLayer(
    const mapLayerType::Type& type,
    const std::int32_t& id,
    const std::int32_t& x,
    const std::int32_t& y,
    const bool& visible,
    const float& opacity,
    const char* name
  ) :
    m_type(type),
    m_id(id),
    m_x(x),
    m_y(y),
    m_visible(visible),
    m_opacity(opacity)
  {
    m_name = name ? new char[std::strlen(name) + 1] : nullptr;
    if (m_name)
    {
      std::strcpy(m_name, name);
    }
  }

  MapLayer::~MapLayer()
  {
    delete[] m_name;
  }
}