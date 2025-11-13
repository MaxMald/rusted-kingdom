#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class AssetManager;
  class Animation;
  class Blackboard;

  class AnimationFactory : public NonCopyable
  {
  public:
    AnimationFactory(const AssetManager& assetManager);
    ~AnimationFactory();

    UniquePtr<Animation> createEightDirectionsAnimation(
      const String& descriptionKey,
      const Blackboard& blackboard
    );

  private:
    const AssetManager& m_assetManager;
  };
}