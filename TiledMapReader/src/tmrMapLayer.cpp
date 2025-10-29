#include "TMR/tmrMapLayer.h"
#include <cstring>

namespace tmr
{
  TiledMapLayer::TiledMapLayer(
    mapLayerType::Type type,
    std::int32_t id,
    std::int32_t x,
    std::int32_t y,
    bool visible,
    float opacity,
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

  TiledMapLayer::~TiledMapLayer()
  {
    delete[] m_name;
  }
}