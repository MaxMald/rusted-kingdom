#pragma once

#include <TMR/tmrPrerequisites.h>
#include <TMR/tmrJson.h>
#include <TMR/tmrObjectGroupParser.h>

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
    ObjectGroupParser m_objectGroupParser;
  };
}