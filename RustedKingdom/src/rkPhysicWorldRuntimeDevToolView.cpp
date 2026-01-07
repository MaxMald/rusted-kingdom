#include "rkPhysicWorldRuntimeDevToolView.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkScenesManager.h"
#include "rkIScene.h"
#include "rkPhysicWorld.h"
#include "rkCollidersGroup.h"
#include "rkCollider.h"
#include "rkCircleCollider.h"
#include "rkGameObject.h"

namespace rk
{
  PhysicWorldRuntimeDevToolView::PhysicWorldRuntimeDevToolView(
    SharedPtr<ScenesManager> scenesManager
  ) : ARuntimeDevToolView("Physic World"),
    m_scenesManager(scenesManager)
  {
  }

  PhysicWorldRuntimeDevToolView::~PhysicWorldRuntimeDevToolView()
  {
  }

  void PhysicWorldRuntimeDevToolView::onUpdate(
    sf::RenderWindow&,
    const sf::Time&
  )
  {
  }

  void PhysicWorldRuntimeDevToolView::onDraw(
    sf::RenderWindow&
  )
  {
    if (!m_scenesManager)
      return;

    SharedPtr<IScene> currentScene = m_scenesManager->getActiveScene();
    if (!currentScene)
      return;

    drawPhysicWorldInfo(currentScene->getPhysicWorld());
  }

  void PhysicWorldRuntimeDevToolView::drawPhysicWorldInfo(
    const PhysicWorld& physicworld
  )
  {
    drawColliderGroupsInfo(
      physicworld.getCollidersGroupKeys(),
      physicworld
    );
  }

  void PhysicWorldRuntimeDevToolView::drawColliderGroupsInfo(
    const Vector<String>& groupKeys,
    const PhysicWorld& physicWorld
  )
  {
    String label = String::Format("Collider Groups (%zu)", groupKeys.size());
    if (ImGui::TreeNode(label.c_str()))
    {
      for (const String& key : groupKeys)
        drawColliderGroupInfo(key, physicWorld.getColliders(key));

      ImGui::TreePop();
    }
  }

  void PhysicWorldRuntimeDevToolView::drawColliderGroupInfo(
    const String& groupKey,
    const Vector<UniquePtr<Collider>>& colliders
  )
  {
    String groupLabel = String::Format(
      "%s (%zu colliders)",
      groupKey.c_str(),
      colliders.size()
    );

    if (ImGui::TreeNode(groupLabel.c_str()))
    {
      for (const UniquePtr<Collider>& collider : colliders)
        drawColliderInfo(*collider);

      ImGui::TreePop();
    }
  }

  void PhysicWorldRuntimeDevToolView::drawColliderInfo(const Collider& collider)
  {
    const GameObject& gameObject = collider.getGameObject();
    String gameObjectName = gameObject.getName();

    if (gameObjectName.empty())
      gameObjectName = "<unnamed gameobject>";

    String colliderLabel = String::Format(
      "%s (%p)",
      gameObjectName.c_str(),
      &gameObject
    );

    if (ImGui::TreeNode(colliderLabel.c_str()))
    {
      String colliderTypeStr = colliderType::toString(collider.getType());
      ImGui::Text("Type: %s", colliderTypeStr.c_str());
      ImGui::Text("Center: (%.2f, %.2f)",
        collider.getCenter().x,
        collider.getCenter().y
      );
      ImGui::Text("Position: (%.2f, %.2f)",
        collider.getPosition().x,
        collider.getPosition().y
      );
      ImGui::Text("Is Dirty: %s",
        collider.isDirty() ? "True" : "False"
      );

      drawColliderTypeInfo(collider);

      ImGui::TreePop();
    }
  }

  void PhysicWorldRuntimeDevToolView::drawColliderTypeInfo(const Collider& collider)
  {
    switch (collider.getType())
    {
      case colliderType::Type::Circle:
        drawCircleColliderInfo(static_cast<const CircleCollider&>(collider));
        break;

      default:
        ImGui::Text("(!) Unknown Collider Type");
        break;
    }
  }

  void PhysicWorldRuntimeDevToolView::drawCircleColliderInfo(const CircleCollider& circleCollider)
  {
    ImGui::Separator();
    ImGui::Text("Circle Collider Info:");
    ImGui::Text("Radius: %.2f", circleCollider.getRadius());
  }
}