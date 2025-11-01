#include "rkMapLayer.h"

namespace rk
{
  MapLayer::MapLayer(tmr::MapLayer* tmrMapLayer) :
    m_tmrMapLayer(tmrMapLayer)
  {
  }

  MapLayer::~MapLayer()
  {
    // No ownership of m_tmrMapLayer, so nothing to delete.
    m_tmrMapLayer = nullptr;
  }
}