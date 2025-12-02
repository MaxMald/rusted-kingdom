#pragma once

#include "rkGameObjectBlueprint.h"

namespace tmr
{
  class Object;
}

namespace rk
{
  class GameObject;

  class TiledGameObjectBlueprint : public GameObjectBlueprint
  {
  public:
    TiledGameObjectBlueprint();
    virtual ~TiledGameObjectBlueprint();

    void setBaseGameObject(GameObject* gameObject) { m_baseGameObject = gameObject; }
    void setTmrObject(const tmr::Object* object) { m_tmrObject = object; }
    void apply(GameObject& baseGameObject, const tmr::Object* tmrObject);
    // Usar el Apply en lugar de un blueprint como tal

  protected:
    GameObject* m_baseGameObject;
    const tmr::Object* m_tmrObject;
  };
}