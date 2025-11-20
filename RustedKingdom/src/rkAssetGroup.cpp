#include "rkAssetGroup.h"

namespace rk
{
  bool AssetGroup::has(const String& key) const
  {
    return m_assets.find(key) != m_assets.end();
  }

  void AssetGroup::unload(const String& key)
  {
    auto it = m_assets.find(key);
    if (it != m_assets.end())
    {
      it->second->unload();
      m_assets.erase(it);
    }
  }

  void AssetGroup::unloadAll()
  {
    for (auto& pair : m_assets)
      pair.second->unload();
    m_assets.clear();
  }
}