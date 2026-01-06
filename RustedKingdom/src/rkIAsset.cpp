#include "rkIAsset.h"

namespace rk
{
  IAsset::IAsset() :
    m_assetPath(""),
    m_assetKey(""),
    m_dependencyTag()
  {
  }
  
  IAsset::~IAsset()
  {
  }

  void IAsset::setAssetKey(const String& assetKey)
  {
    m_assetKey = assetKey;
  }

  String IAsset::getAssetKey() const
  {
    return m_assetKey;
  }

  void IAsset::setAssetPath(const Path& assetPath)
  {
    m_assetPath = assetPath;
  }

  Path IAsset::getAssetPath() const
  {
    return m_assetPath;
  }

  bool IAsset::isDependencyTagsEmpty() const
  {
    return m_dependencyTag.empty();
  }

  bool IAsset::hasDependencyTag(const String& tag) const
  {
    return std::find(
      m_dependencyTag.begin(),
      m_dependencyTag.end(),
      tag
    ) != m_dependencyTag.end();
  }

  void IAsset::addDependencyTag(const String& tag)
  {
    if (!hasDependencyTag(tag))
      m_dependencyTag.push_back(tag);
  }

  void IAsset::removeDependencyTag(const String& tag)
  {
    auto it = std::find(
      m_dependencyTag.begin(),
      m_dependencyTag.end(),
      tag
    );

    if (it != m_dependencyTag.end())
      m_dependencyTag.erase(it);
  }
}