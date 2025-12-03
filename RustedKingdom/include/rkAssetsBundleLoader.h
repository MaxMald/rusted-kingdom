#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class AssetManager;

  namespace assetsBundleLoader
  {
    bool loadAssetsBundle(const Path& bundleFilePath, AssetManager&);
  }
}