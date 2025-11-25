#include "rkTiledObjectBlueprintMapper.h"

namespace rk
{
  TiledObjectBlueprintMapper::TiledObjectBlueprintMapper()
    : NonCopyable(),
    m_blueprints()
  {
  }

  TiledObjectBlueprintMapper::~TiledObjectBlueprintMapper()
  {
  }

  void TiledObjectBlueprintMapper::registerBlueprint(
    const String& objectType,
    UniquePtr<TiledObjectBlueprint> blueprint
  )
  {
    m_blueprints.emplace(objectType, std::move(blueprint));
  }

  TiledObjectBlueprint* TiledObjectBlueprintMapper::getBlueprintForObjectType(
    const String& objectType
  ) const
  {
    auto it = m_blueprints.find(objectType);
    if (it != m_blueprints.end())
      return it->second.get();

    throw RuntimeErrorException(
      String::Format(
        "TiledObjectBlueprintMapper::getBlueprintForObjectType: "
        "No blueprint registered for object type '%s'.",
        objectType.c_str()
      )
    );
  }
}