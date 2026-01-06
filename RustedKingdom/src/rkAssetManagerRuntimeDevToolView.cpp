#include "rkAssetManagerRuntimeDevToolView.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkAssetManager.h"
#include "rkAssetGroup.h"
#include "rkIAsset.h"

namespace rk
{
  AssetManagerRuntimeDevToolView::AssetManagerRuntimeDevToolView(
    SharedPtr<AssetManager> assetManager
  ) : ARuntimeDevToolView("Asset Manager"),
    m_assetManager(assetManager)
  {
  }

  AssetManagerRuntimeDevToolView::~AssetManagerRuntimeDevToolView()
  {
  }

  void AssetManagerRuntimeDevToolView::onUpdate(sf::RenderWindow&, const sf::Time&)
  {
    // No update logic needed for now
  }

  void AssetManagerRuntimeDevToolView::onDraw(sf::RenderWindow&)
  {
    if (!m_assetManager)
      return;

    String assetDirectoryStr = m_assetManager->getAssetDirectory().string();
    ImGui::Text("Asset Directory: %s",assetDirectoryStr.c_str());

    ImGui::Text("Asset Groups:");
    Vector<SharedPtr<AssetGroup>> assetsGroups = 
      m_assetManager->getAllAssetGroups();

    for (const SharedPtr<AssetGroup>& group : assetsGroups)
    {
      ImGui::Separator();
      drawAssetGroupTree(*group);
    }
  }

  void AssetManagerRuntimeDevToolView::drawAssetGroupTree(const AssetGroup& group)
  {
    String assetGroupName = getAssetGroupName(group);
    if (ImGui::TreeNode(assetGroupName.c_str()))
    {
      Vector<SharedPtr<IAsset>> assets = group.getAllAssets();
      for (const SharedPtr<IAsset>& asset : assets)
        drawAssetTreeElement(*asset);

      ImGui::TreePop();
    }
  }

  String AssetManagerRuntimeDevToolView::getAssetGroupName(
    const AssetGroup& assetGroup
  )
  {
    String name = assetGroup.getName();
    if (name.empty())
      name = "<unnamed>";

    return String::Format(
      "%s (size: %d)",
      name.c_str(),
      static_cast<Int32>(assetGroup.getSize())
    );
  }

  void AssetManagerRuntimeDevToolView::drawAssetTreeElement(const IAsset& asset)
  {
    String assetName = asset.getAssetKey();
    Path assetPath = asset.getAssetPath();

    if (assetName.empty())
      assetName = String::Format("<unnamed> &(%p)", &asset);

    if (assetPath.empty())
      assetPath = "<no path>";

    if (ImGui::TreeNode(assetName.c_str()))
    {
      String pathStr = assetPath.string();
      ImGui::Text("Asset Path: %s", pathStr.c_str());
      ImGui::TreePop();
    }
  }
}