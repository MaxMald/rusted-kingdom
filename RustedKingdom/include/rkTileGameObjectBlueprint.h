#pragma once

#include "rkGameObjectBlueprint.h"
#include "rkTiledObjectSpriteDescriptor.h"

namespace rk
{
  class SpriteComponentFactory;

  class TileGameObjectBlueprint : public GameObjectBlueprint
  {
  public:
    TileGameObjectBlueprint(SpriteComponentFactory&);
    ~TileGameObjectBlueprint();

    void setDescription(const TiledObjectSpriteDescriptor& description);

  protected:
    virtual GameObject* instantiate(
      const String& name,
      GameObject& parent
    ) const override;

  private:
    SpriteComponentFactory& m_spriteComponentFactory;
    TiledObjectSpriteDescriptor m_description;
  };
}