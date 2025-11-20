#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class IAsset : public NonCopyable
  {
  public:
    IAsset() = default;
    virtual ~IAsset() = default;

  protected:
    virtual bool loadFromFile(const Path& filename) = 0;
    virtual void unload() = 0;

    template<typename T>
    friend class AssetGroup;
  };
}
