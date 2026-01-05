#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class Animation;
  class Blackboard;

  namespace animationFactory
  {
    UniquePtr<Animation> createEightDirectionsAnimation(
      const String& descriptionKey,
      const Blackboard& blackboard
    );
  }
}