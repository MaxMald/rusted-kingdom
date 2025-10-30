#include "TMR/tmrTileMapLayerParser.h"
#include "TMR/tmrTileMapLayer.h"
#include <stdexcept>

namespace tmr
{
  TileMapLayerParser::TileMapLayerParser()
  {
  }

  TileMapLayerParser::~TileMapLayerParser()
  {
  }

  TileMapLayer* TileMapLayerParser::parseFromJson(
    const std::int32_t id,
    const std::int32_t x,
    const std::int32_t y,
    const bool& visible,
    const float& opacity,
    const char* name,
    const Json& json
  )
  {
    std::int32_t height = json["height"].getInt32();
    std::int32_t width = json["width"].getInt32();

    // Read data array
    Json dataJson = json["data"];
    if (!dataJson.isArray())
      throw std::runtime_error("Layer 'data' is not an array.");

    const std::size_t dataSize = dataJson.getSize();
    std::int32_t* data = new std::int32_t[dataSize];
    dataJson.getArrayInt32(data, dataSize);

    return new TileMapLayer(
      id,
      x,
      y,
      visible,
      opacity,
      name,
      width,
      height,
      dataSize,
      data
    );
  }
}