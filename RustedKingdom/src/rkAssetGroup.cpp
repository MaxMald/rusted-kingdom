#include "rkAssetGroup.h"

namespace rk
{
  AssetGroup::AssetGroup() : m_groupName("")
  {
  }

  AssetGroup::AssetGroup(const String name) : m_groupName(name)
  {
  }

  const String& AssetGroup::getName() const
  {
    return m_groupName;
  }

  Vector<String> AssetGroup::getAllAssetKeys() const
  {
    Vector<String> keys;
    for (const auto& pair : m_assets)
      keys.push_back(pair.first);
    return keys;
  }

  Vector<SharedPtr<IAsset>> AssetGroup::getAllAssets() const
  {
    Vector<SharedPtr<IAsset>> assets;
    for (const auto& pair : m_assets)
      assets.push_back(pair.second);
    return assets;
  }

  SizeT AssetGroup::getSize() const
  {
    return m_assets.size();
  }

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