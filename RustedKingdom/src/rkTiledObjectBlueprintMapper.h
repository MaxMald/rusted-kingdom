#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class TiledObjectBlueprint;

  class TiledObjectBlueprintMapper : public NonCopyable
  {
  public:
    TiledObjectBlueprintMapper();
    ~TiledObjectBlueprintMapper();

    void registerBlueprint(
      const String& objectType,
      UniquePtr<TiledObjectBlueprint> blueprint
    );

    TiledObjectBlueprint* getBlueprintForObjectType(
      const String& objectType
    ) const;

  private:
    UnorderedMap<String, UniquePtr<TiledObjectBlueprint>> m_blueprints;
  };
}