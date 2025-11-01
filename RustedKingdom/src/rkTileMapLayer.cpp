#include "rkTileMapLayer.h"

namespace rk
{
  TileMapLayer::TileMapLayer(tmr::TileMapLayer* tmrTileMapLayer) :
    MapLayer(tmrTileMapLayer)
  {
  }

  TileMapLayer::~TileMapLayer()
  {
    // No ownership of m_tmrMapLayer, so nothing to delete.
  }
}