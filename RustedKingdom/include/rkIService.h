#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class ServiceLocator;

  class IService : public NonCopyable
  {
  public:
    IService() = default;
    virtual ~IService() = default;

  protected:

    virtual void init(ServiceLocator& serviceLocator) = 0;
    virtual void destroy() = 0;

    friend class ServiceLocator;
  };
}