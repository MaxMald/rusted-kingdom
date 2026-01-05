#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace tmr
{
  class TiledMap;
  class Object;
}

namespace rk
{
  class GameObject;

  class ITiledClassApplier : public NonCopyable
  {
  public:
    virtual ~ITiledClassApplier() = default;

    virtual void apply(
      GameObject&,
      const tmr::Object*,
      const tmr::TiledMap*
    ) = 0;

  protected:
    ITiledClassApplier() = default;
  };
}