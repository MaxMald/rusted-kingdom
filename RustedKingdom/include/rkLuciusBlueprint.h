#pragma once

#include "rkPrerequisites.h"
#include "rkGameObjectBlueprint.h"
#include "rkIPositionTransformer.h"

namespace rk
{
  class AnimationFactory;
  class Pathfinder;

  class LuciusBlueprint : public GameObjectBlueprint
  {
  public:
    LuciusBlueprint(
      ComponentFactoryLocator& componentFactoryLocator,
      AnimationFactory& animationFactory,
      SharedPtr<Pathfinder> pathfinder,
      SharedPtr<IPositionTransformer> positionTransform
    );
    ~LuciusBlueprint() override;

    virtual void apply(GameObject& gameObject) const override;

  private:
    AnimationFactory& m_animationFactory;
    SharedPtr<Pathfinder> m_pathfinder;
    SharedPtr<IPositionTransformer> m_positionTransform;
  };
}