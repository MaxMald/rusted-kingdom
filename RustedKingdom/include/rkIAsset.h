#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  /**
   * @brief Interface for all asset types managed by the engine.
   */
  class IAsset : public NonCopyable
  {
  public:
    IAsset();
    virtual ~IAsset();

    /**
    * @brief Sets the unique key for the asset.
    */
    void setAssetKey(const String& assetKey);

    /**
     * @brief Gets the unique key for the asset.
     */
    String getAssetKey() const;

    /**
     * @brief Sets the file path for the asset.
     */
    void setAssetPath(const Path& assetPath);

    /**
     * @brief Gets the file path for the asset.
     */
    Path getAssetPath() const;

  protected:
    /**
     * @brief Loads the asset from a file.
     * 
     * @param filename Path to the asset file.
     * 
     * @return True if loading succeeded, false otherwise.
     */
    virtual bool loadFromFile(const Path& filename) = 0;

    /**
    * @brief Unloads the asset and releases its resources.
    */
    virtual void unload() = 0;

    bool isDependencyTagsEmpty() const;
    bool hasDependencyTag(const String& tag) const;
    void addDependencyTag(const String& tag);
    void removeDependencyTag(const String& tag);

  private:
    Vector<String> m_dependencyTag;
    String m_assetKey;
    Path m_assetPath;

    friend class AssetGroup;
    template<typename T>
    friend class TypedAssetGroup;
  };
}
