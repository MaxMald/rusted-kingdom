#include "rkSceneGraphRuntimeDevToolView.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkScenesManager.h"
#include "rkIScene.h"
#include "rkSceneGraph.h"

namespace rk
{
  SceneGraphRuntimeDevToolView::SceneGraphRuntimeDevToolView(
    SharedPtr<ScenesManager> scenesManager
  ) :
    ARuntimeDevToolView("Scene Graph"),
    m_scenesManager(scenesManager),
    m_gameObjectView(),
    m_selectedGameObject(nullptr)
  {
    m_gameObjectView.isOpen = true;
  }

  SceneGraphRuntimeDevToolView::~SceneGraphRuntimeDevToolView()
  {
  }

  void SceneGraphRuntimeDevToolView::onUpdate(sf::RenderWindow&, const sf::Time&)
  {
  }

  void SceneGraphRuntimeDevToolView::onDraw(sf::RenderWindow& window)
  {
    if (!m_scenesManager)
      return;

    SharedPtr<IScene> activeScene = m_scenesManager->getActiveScene();
    if (!activeScene)
      return;

    SceneGraph& sceneGraph = activeScene->getSceneGraph();

    drawGameObjectTree(*sceneGraph.getRoot());

    if (m_selectedGameObject)
    {
      m_gameObjectView.setActiveGameObject(m_selectedGameObject);
      m_gameObjectView.draw(window);
    }
  }

  void SceneGraphRuntimeDevToolView::drawGameObjectTree(GameObject& node)
  {
    String label = getGameObjectName(node);

    // Use a unique ID to avoid ImGui ID conflicts
    ImGui::PushID(&node);

    bool nodeOpen = ImGui::TreeNode(label.c_str());

    if (ImGui::IsItemClicked())
    {
      m_selectedGameObject = &node;
    }

    if (m_selectedGameObject == &node)
    {
      ImGui::SameLine();
      ImGui::TextColored(ImVec4(1, 1, 0, 1), "<-- Selected");
    }

    if (nodeOpen)
    {
      for (const auto& child : node.getChildren())
      {
        drawGameObjectTree(*child);
      }
      ImGui::TreePop();
    }

    ImGui::PopID();
  }

  String SceneGraphRuntimeDevToolView::getGameObjectName(const GameObject& gameObject)
  {
    String gameObjectName = gameObject.getName();
    if (gameObjectName.empty())
      gameObjectName = "<unnamed>";

    return String::Format("%s (%p)", gameObjectName.c_str(), &gameObject);
  }
}