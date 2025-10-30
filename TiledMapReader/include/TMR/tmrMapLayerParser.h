#pragma once

#include "TMR/tmrTileMapLayerParser.h"

namespace tmr
{
  class MapLayer;

  /**
   * @brief Parses map layer JSON into runtime MapLayer objects.
   *
   * MapLayerParser provides a small façade that composes a
   * TileMapLayerParser to parse the tile-specific contents and
   * produce a higher-level MapLayer instance representing a
   * single layer inside a tiled map.
   */
  class MapLayerParser
  {
  public:

    MapLayerParser() = default;
    ~MapLayerParser() = default;

    /**
     * @brief Parses a MapLayer from a JSON object.
     * @param json The JSON object containing map layer data.
     * @return A pointer to a newly created MapLayer object.
     */
    MapLayer* parseFromJson(const Json& json);

  private:
    TileMapLayerParser m_TileMapLayerParser;
  };
}