#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class IService : public NonCopyable
  {
  public:
    IService() = default;
    virtual ~IService() = default;

  protected:
    virtual void destroy() = 0;
  };
}