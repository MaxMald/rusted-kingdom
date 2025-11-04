#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"

namespace tmr
{
  class ReferenceTileSet;

  class ReferenceTileSetParser
  {
  public:

    ReferenceTileSetParser();
    ~ReferenceTileSetParser();

    ReferenceTileSet* parseFromJson(
      const std::int32_t firstgid,
      const Json& json
    );
  };
}