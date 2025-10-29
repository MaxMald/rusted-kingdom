#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"

namespace tmr
{
  class TileMapLayer;

  /**
   * @class TileMapLayerParser
   * @brief Responsible for parsing JSON data into TileMapLayer objects.
   *
   * This class provides methods to construct a TileMapLayer from a JSON representation,
   * typically as part of loading a Tiled map.
   */
  class TileMapLayerParser
  {
  public:
    /**
     * @brief Constructs a TileMapLayerParser object.
     */
    TileMapLayerParser();

    /**
     * @brief Destroys the TileMapLayerParser object.
     */
    ~TileMapLayerParser();

    /**
     * @brief Parses a TileMapLayer from a JSON object.
     *
     * @param json The JSON object containing tile layer data.
     * @return A pointer to a newly created TileMapLayer object.
     *         Ownership is transferred to the caller.
     * @throws std::runtime_error if required fields are missing or invalid.
     */
    TileMapLayer* parseFromJson(const Json& json);
  };
}