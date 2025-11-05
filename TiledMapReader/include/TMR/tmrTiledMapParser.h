#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"
#include "TMR/tmrOrientation.h"
#include "TMR/tmrRenderOrder.h"
#include "TMR/tmrMapLayerParser.h"
#include "TMR/tmrTileSetParser.h"

namespace tmr
{
  class TiledMap;

  class TiledMapParser
  {
  public:

    TiledMapParser();
    ~TiledMapParser();

    TiledMap* parseFromJson(const Json& json);

  private:

    MapLayerParser m_mapLayerParser;
    TileSetParser m_tileSetParser;

    renderOrder::Type parseRenderOrder(const char* renderOrderStr);
  };
}