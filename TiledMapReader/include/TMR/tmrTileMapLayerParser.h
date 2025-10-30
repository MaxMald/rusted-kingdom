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
     * @brief Parse a tile-layer from JSON and return a new TileMapLayer.
     *
     * @param id Layer id.
     * @param x Layer x offset.
     * @param y Layer y offset.
     * @param visible Visibility flag.
     * @param opacity Layer opacity.
     * @param name Layer name (null-terminated).
     * @param json JSON object describing the layer.
     * 
     * @return Pointer to a newly allocated TileMapLayer. Ownership is
     * transferred to the caller.
     * 
     * @throws std::runtime_error on missing/invalid JSON fields.
     */
    TileMapLayer* parseFromJson(
      const std::int32_t id,
      const std::int32_t x,
      const std::int32_t y,
      const bool& visible,
      const float& opacity,
      const char* name,
      const Json& json
    );
  };
}