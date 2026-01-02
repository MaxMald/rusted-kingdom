#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class IComponentFactory : public NonCopyable
  {
  protected:
    IComponentFactory() = default;
    virtual ~IComponentFactory() = default;
  };
}