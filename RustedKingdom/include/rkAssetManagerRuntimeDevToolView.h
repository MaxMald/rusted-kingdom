#pragma once

#include "rkARuntimeDevToolView.h"

namespace rk
{
  class AssetManager;
  class AssetGroup;
  class IAsset;

  class AssetManagerRuntimeDevToolView : public ARuntimeDevToolView
  {
  public:
    AssetManagerRuntimeDevToolView(SharedPtr<AssetManager> assetManager);
    virtual ~AssetManagerRuntimeDevToolView();

  protected:
    SharedPtr<AssetManager> m_assetManager;

    virtual void onUpdate(sf::RenderWindow&, const sf::Time&) override;
    virtual void onDraw(sf::RenderWindow&) override;

    String getAssetGroupName(const AssetGroup&);
    void drawAssetGroupTree(const AssetGroup&);
    void drawAssetTreeElement(const IAsset&);
  };
}