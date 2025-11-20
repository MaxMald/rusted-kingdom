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

  private:
    virtual bool loadFromFile(const String& filename) = 0;
    virtual void unload() = 0;

    template<typename T>
    friend class AssetGroup;
  };
}
