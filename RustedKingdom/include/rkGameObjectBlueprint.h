#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkDependenciesLocator.h"

namespace rk
{ 
  class GameObject;

  class GameObjectBlueprint : public NonCopyable
  {
  public:
    GameObjectBlueprint(ComponentFactoryLocator&);
    virtual ~GameObjectBlueprint();

    virtual void apply(GameObject& gameObject) const;
    GameObject* instantiate(const String& name, GameObject& parent) const;

  protected:
    ComponentFactoryLocator& m_componentFactoryLocator;
  };
}