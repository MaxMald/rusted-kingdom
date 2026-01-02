#pragma once

#include "rkBaseTiledClassApplier.h"

namespace rk
{
  class RigidBodyComponentFactory;
  class AnimationStateMachine;

  class UnitClassApplier : public BaseTiledClassApplier
  {
  public:
    UnitClassApplier(
      SpriteComponentFactory&,
      TiledColliderComponentFactory&,
      RigidBodyComponentFactory&
    );
    virtual ~UnitClassApplier();

    virtual void apply(
      GameObject&,
      const tmr::Object*,
      const tmr::TiledMap*
    ) override;

  protected:
    RigidBodyComponentFactory& m_rigidBodyComponentFactory;

  private:
  };
}