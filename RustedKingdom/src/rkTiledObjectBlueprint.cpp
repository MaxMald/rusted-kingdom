#include "rkTiledObjectBlueprint.h"

namespace rk
{
  TiledObjectBlueprint::TiledObjectBlueprint(ComponentFactoryLocator& componentFactoryLocator)
    : GameObjectBlueprint(componentFactoryLocator), m_tmrObject(nullptr)
  {
  }
  
  TiledObjectBlueprint::~TiledObjectBlueprint()
  {
  }

  void TiledObjectBlueprint::prepare(
    tmr::TiledMap* tmrTiledMap,
    tmr::Object* tmrObject
  )
  {
    m_tmrTiledMap = tmrTiledMap;
    m_tmrObject = tmrObject;
  }
}