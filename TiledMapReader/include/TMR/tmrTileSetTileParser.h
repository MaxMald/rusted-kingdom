#pragma once

#include <TMR/tmrPrerequisites.h>
#include <TMR/tmrJson.h>
#include <TMR/tmrObjectGroupMapLayerParser.h>

namespace tmr
{
  class TileSetTile;

  class TileSetTileParser
  {
  public:
    TileSetTileParser();
    ~TileSetTileParser();

    TileSetTile* parseFromJson(const Json& json);

  private:
    ObjectGroupMapLayerParser m_objectGroupParser;
  };
}