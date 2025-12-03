#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class AssetsBundleItem
  {
  public:
    AssetsBundleItem(const String& key, const Path& path);
    AssetsBundleItem(AssetsBundleItem& other);
    AssetsBundleItem(AssetsBundleItem&& other) noexcept;
    virtual ~AssetsBundleItem();

    AssetsBundleItem& operator=(const AssetsBundleItem& other);
    AssetsBundleItem& operator=(AssetsBundleItem&& other) noexcept;

    const String& getKey() const { return m_key; }
    const Path& getPath() const { return m_path; }

  private:
    String m_key;
    Path m_path;
  };
}