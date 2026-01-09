#include "rkGameObjectRuntimeDevToolView.h"
#include "imgui.h"
#include "rkGameObject.h"
#include "rkComponent.h"

namespace rk
{
  GameObjectRuntimeDevToolView::GameObjectRuntimeDevToolView()
    : ARuntimeDevToolView("Game Object View"),
    m_activeGameObject(nullptr),
    m_componentDrawerService()
  {
  }

  GameObjectRuntimeDevToolView::~GameObjectRuntimeDevToolView()
  {
  }

  void GameObjectRuntimeDevToolView::setActiveGameObject(GameObject* gameObject)
  {
    m_activeGameObject = gameObject;
  }

  void GameObjectRuntimeDevToolView::onUpdate(
    sf::RenderWindow&,
    const sf::Time&
  )
  {
    // Nothing to update for now
  }

  void GameObjectRuntimeDevToolView::onDraw(sf::RenderWindow& window)
  {
    if (!m_activeGameObject)
      return;

    drawBaseInformation();
    drawComponents(window);
  }

  void GameObjectRuntimeDevToolView::drawBaseInformation()
  {
    if (!m_activeGameObject)
      return;

    String gameObjectName = m_activeGameObject->getName();
    if (gameObjectName.empty())
      gameObjectName = "<unnamed>";

    ImGui::Text("Name: %s", gameObjectName.c_str());

    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
      ImGui::Text("Position: (%f, %f)", m_activeGameObject->getPosition().x, m_activeGameObject->getPosition().y);
      ImGui::Text("World Position: (%f, %f)", m_activeGameObject->getWorldPosition().x, m_activeGameObject->getWorldPosition().y);
      ImGui::Text("Scale: (%f, %f)", m_activeGameObject->getScale().x, m_activeGameObject->getScale().y);
      ImGui::Text("Rotation: %f degrees", m_activeGameObject->getRotation().asDegrees());
      ImGui::Text("Origin : (%f, %f)", m_activeGameObject->getOrigin().x, m_activeGameObject->getOrigin().y);

      if (ImGui::CollapsingHeader("Transform Matrix"))
      {
        const float* mat = m_activeGameObject->getTransform().getMatrix();
        for (int row = 0; row < 4; ++row)
        {
          ImGui::Text("%8.3f %8.3f %8.3f %8.3f", mat[row * 4 + 0], mat[row * 4 + 1], mat[row * 4 + 2], mat[row * 4 + 3]);
        }
      }
    }
  }

  void GameObjectRuntimeDevToolView::drawComponents(sf::RenderWindow& window)
  {
    if (!m_activeGameObject)
      return;
    
    const Vector<UniquePtr<Component>>& components = 
      m_activeGameObject->getAllComponents();

    for (const auto& component : components)
      m_componentDrawerService.draw(window, *component);
  }
}