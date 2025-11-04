#include "TMR/tmrReferenceTileSetParser.h"

#include <string>

#include "TMR/tmrReferenceTileSet.h"

namespace tmr
{
  ReferenceTileSetParser::ReferenceTileSetParser()
  {
  }

  ReferenceTileSetParser::~ReferenceTileSetParser()
  {
  }

  ReferenceTileSet* ReferenceTileSetParser::parseFromJson(
    const std::int32_t firstgid,
    const Json& json
  )
  {
    // Parse source string
    std::string sourceStr;
    sourceStr.resize(json["source"].getStringLength() + 1);
    json["source"].getString(&sourceStr[0], sourceStr.size());
    sourceStr.resize(sourceStr.size() - 1);

    return new ReferenceTileSet(
      firstgid,
      sourceStr.c_str()
    );
  }
}