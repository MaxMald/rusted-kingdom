#pragma once

#include "rkGameObjectBlueprint.h"

namespace tmr
{
  class TiledMap;
  class Object;
}

namespace rk
{
  class TiledObjectBlueprint : public GameObjectBlueprint
  {
  public:
    TiledObjectBlueprint(ComponentFactoryLocator&);
    virtual ~TiledObjectBlueprint();

    void prepare(
      tmr::TiledMap* tmrTiledMap,
      tmr::Object* tmrObject
   );

  protected:
    tmr::Object* m_tmrObject;
    tmr::TiledMap* m_tmrTiledMap;
  };
}