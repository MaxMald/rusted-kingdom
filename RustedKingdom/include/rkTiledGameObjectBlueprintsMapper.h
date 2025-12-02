#pragma once

#include "rkPrerequisites.h"
#include "rkTiledGameObjectBlueprint.h"
#include "rkNonCopyable.h"

namespace rk
{
  class TiledGameObjectBlueprintMapper : NonCopyable
  {
  public:
    TiledGameObjectBlueprintMapper();
    ~TiledGameObjectBlueprintMapper();

    bool hasBlueprint(const String& name) const;
    SharedPtr<TiledGameObjectBlueprint> getBlueprint(const String& name) const;    
    void registerBlueprint(
      const String& name,
      const SharedPtr<TiledGameObjectBlueprint>& blueprint
    );

  private:
    UnorderedMap<String, SharedPtr<TiledGameObjectBlueprint>> m_blueprints;
  };
}