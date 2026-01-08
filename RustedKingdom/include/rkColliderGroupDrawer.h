#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "rkPrerequisites.h"
#include "imgui.h"

namespace rk
{
  class PhysicWorld;
  class ColliderDrawerService;

  class ColliderGroupDrawer
  {
  public:
    ColliderGroupDrawer(const String& colliderGroupKey, ColliderDrawerService&);
    ~ColliderGroupDrawer();

    const String& getColliderGroupKey() const;
    const sf::Color& getColor() const;
    void setColor(const sf::Color& color);

    void draw(sf::RenderWindow& window, const PhysicWorld&);

  protected:
    ColliderDrawerService& m_drawerService;
    String m_colliderGroupKey;
    ImVec4 m_imguiColor;
    sf::Color m_color;
    bool m_drawColliders;
  };
}