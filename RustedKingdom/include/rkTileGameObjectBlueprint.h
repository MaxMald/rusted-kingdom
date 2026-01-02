#pragma once

#include "rkGameObjectBlueprint.h"
#include "rkTiledObjectSpriteDescriptor.h"

namespace rk
{
  class TileGameObjectBlueprint : public GameObjectBlueprint
  {
  public:
    TileGameObjectBlueprint(ComponentFactoryLocator&);
    ~TileGameObjectBlueprint();

    void setDescription(const TiledObjectSpriteDescriptor& description);

    virtual void apply(GameObject& gameObject) const override;

  private:
    TiledObjectSpriteDescriptor m_description;
  };
}