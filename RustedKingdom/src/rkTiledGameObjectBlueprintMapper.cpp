#include "rkTiledGameObjectBlueprintsMapper.h"

namespace rk
{
  TiledGameObjectBlueprintMapper::TiledGameObjectBlueprintMapper() :
    m_blueprints()
  {
  }

  TiledGameObjectBlueprintMapper::~TiledGameObjectBlueprintMapper()
  {
  }

  bool TiledGameObjectBlueprintMapper::hasBlueprint(const String& name) const
  {
    return m_blueprints.find(name) != m_blueprints.end();
  }

  SharedPtr<TiledGameObjectBlueprint> TiledGameObjectBlueprintMapper::getBlueprint(
    const String& name
  ) const
  {
    auto it = m_blueprints.find(name);
    if (it != m_blueprints.end())
      return it->second;

    return nullptr;
  }

  void TiledGameObjectBlueprintMapper::registerBlueprint(
    const String& name,
    const SharedPtr<TiledGameObjectBlueprint>& blueprint
  )
  {
    m_blueprints[name] = blueprint;
  }
}