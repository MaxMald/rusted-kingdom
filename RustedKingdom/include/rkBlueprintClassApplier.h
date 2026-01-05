#pragma once

#include "rkITiledClassApplier.h"

namespace rk
{
  class GameObjectBlueprint;

  class BlueprintClassApplier : public ITiledClassApplier
  {
  public:
    BlueprintClassApplier(SharedPtr<GameObjectBlueprint>);
    virtual ~BlueprintClassApplier();

    virtual void apply(
      GameObject&,
      const tmr::Object*,
      const tmr::TiledMap*
    ) override;

  protected:
    SharedPtr<GameObjectBlueprint> m_gameObjectBlueprint;

    virtual void initProperties(
      GameObject&,
      const tmr::Object*
    );

  private:
    void initPosition(GameObject&, const tmr::Object*);
  };
}