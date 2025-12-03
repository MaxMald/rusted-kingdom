#include "rkAssetsBundleItem.h"

namespace rk
{
  AssetsBundleItem::AssetsBundleItem(const String& key, const Path& path) :
    m_key(key),
    m_path(path)
  {
  }

  AssetsBundleItem::AssetsBundleItem(AssetsBundleItem& other) :
    m_key(other.m_key),
    m_path(other.m_path)
  {
  }

  AssetsBundleItem::AssetsBundleItem(AssetsBundleItem&& other) noexcept :
    m_key(std::move(other.m_key)),
    m_path(std::move(other.m_path))
  {
  }

  AssetsBundleItem::~AssetsBundleItem()
  {
  }

  AssetsBundleItem& AssetsBundleItem::operator=(const AssetsBundleItem& other)
  {
    if (this != &other)
    {
      m_key = other.m_key;
      m_path = other.m_path;
    }
    return *this;
  }

  AssetsBundleItem& AssetsBundleItem::operator=(AssetsBundleItem&& other) noexcept
  {
    if (this != &other)
    {
      m_key = std::move(other.m_key);
      m_path = std::move(other.m_path);
    }
    return *this;
  }
}