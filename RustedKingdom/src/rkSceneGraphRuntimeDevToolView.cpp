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
    m_scenesManager(scenesManager)
  {
  }

  SceneGraphRuntimeDevToolView::~SceneGraphRuntimeDevToolView()
  {
  }

  void SceneGraphRuntimeDevToolView::onUpdate(sf::RenderWindow&, const sf::Time&)
  {
  }

  void SceneGraphRuntimeDevToolView::onDraw(sf::RenderWindow&)
  {
    if (!m_scenesManager)
      return;

    SharedPtr<IScene> activeScene = m_scenesManager->getActiveScene();
    if (!activeScene)
      return;

    SceneGraph& sceneGraph = activeScene->getSceneGraph();
    drawGameObjectTree(*sceneGraph.getRoot());
  }

  void SceneGraphRuntimeDevToolView::drawGameObjectTree(const GameObject& root)
  {
    String label = getGameObjectName(root);
    if (ImGui::TreeNode(label.c_str()))
    {
      for (const auto& child : root.getChildren())
      {
        drawGameObjectTree(*child);
      }

      ImGui::TreePop();
    }
  }

  String SceneGraphRuntimeDevToolView::getGameObjectName(const GameObject& gameObject)
  {
    String gameObjectName = gameObject.getName();
    if (!gameObjectName.empty())
      return gameObjectName;

    return String::Format("<unnamed> &(%p)", &gameObject);
  }
}