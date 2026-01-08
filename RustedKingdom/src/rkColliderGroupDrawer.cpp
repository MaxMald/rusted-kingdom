#include "rkColliderGroupDrawer.h"

#include "imgui-SFML.h"
#include "rkColorUtilities.h"
#include "rkCollider.h"
#include "rkPhysicWorld.h"
#include "rkColliderDrawerService.h"

namespace rk
{
  ColliderGroupDrawer::ColliderGroupDrawer(
    const String& colliderGroupKey,
    ColliderDrawerService& drawerService
  ) :
    m_drawerService(drawerService),
    m_colliderGroupKey(colliderGroupKey),
    m_imguiColor(0.0f, 1.0f, 0.0f, 1.0f),
    m_color(sf::Color::Green),
    m_drawColliders(false)
  {
  }

  ColliderGroupDrawer::~ColliderGroupDrawer()
  {
  }

  const String& ColliderGroupDrawer::getColliderGroupKey() const
  {
    return m_colliderGroupKey;
  }

  const sf::Color& ColliderGroupDrawer::getColor() const
  {
    return m_color;
  }

  void ColliderGroupDrawer::setColor(const sf::Color& color)
  {
    m_color = color;
  }

  void  ColliderGroupDrawer::draw(
    sf::RenderWindow& window,
    const PhysicWorld& physicWorld
  )
  {
    String groupLabel = String::Format("Group: %s", m_colliderGroupKey.c_str());

    if (ImGui::TreeNode(groupLabel.c_str()))
    {
      ImGui::Checkbox("Draw Colliders", &m_drawColliders);
      ImGui::ColorEdit4("Color", reinterpret_cast<float*>(&m_imguiColor));
      m_color = colorUtilities::getColorFromImVec4(m_imguiColor);

      ImGui::TreePop();
    }

    if (!m_drawColliders || m_colliderGroupKey.empty())
      return;
    
    const Vector<UniquePtr<Collider>>& colliders =
      physicWorld.getColliders(m_colliderGroupKey);

    for (const auto& collider : colliders)
      m_drawerService.draw(window, *collider, m_color);
  }
}