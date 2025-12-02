#include "rkTiledGameObjectBlueprint.h"

namespace rk
{
  TiledGameObjectBlueprint::TiledGameObjectBlueprint() :
    m_tmrObject(nullptr)
  {
  }

  TiledGameObjectBlueprint::~TiledGameObjectBlueprint()
  {
    m_tmrObject = nullptr;
  }
}