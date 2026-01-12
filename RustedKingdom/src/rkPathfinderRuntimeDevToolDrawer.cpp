#include "rkPathfinderRuntimeDevToolDrawer.h"

#include <SFML/OpenGL.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include "rkPathfinder.h"

namespace
{
  constexpr float PATHFINDER_GRID_POINT_SIZE = 3.0f;
}

namespace rk
{
  PathfinderRuntimeDevToolDrawer::PathfinderRuntimeDevToolDrawer(
    const String& name,
    SharedPtr<Pathfinder> pathfinder
  ) :
    m_name(name),
    m_drawPathfindingGrid(false),
    m_pathfinder(pathfinder)
  {
  }

  PathfinderRuntimeDevToolDrawer::~PathfinderRuntimeDevToolDrawer()
  {
  }

  const String& PathfinderRuntimeDevToolDrawer::getName() const
  {
    return m_name;
  }

  void PathfinderRuntimeDevToolDrawer::draw(sf::RenderWindow& window)
  {
    if (!m_pathfinder)
      return;

    String label = String::Format("Pathfinder: %s", m_name.c_str());
    if (ImGui::CollapsingHeader(label.c_str()))
    {
      ImGui::Text("Dimensions: (%u x %u)", m_pathfinder->getWidth(), m_pathfinder->getHeight());
      ImGui::Text("Total of %u nodes", m_pathfinder->getWidth() * m_pathfinder->getHeight());
      ImGui::Checkbox("Draw Pathfinding Grid", &m_drawPathfindingGrid);
    }

    if (m_drawPathfindingGrid)
      drawPathfinderGrid(window);
  }

  void PathfinderRuntimeDevToolDrawer::drawPathfinderGrid(sf::RenderWindow& window)
  {
    if (!m_pathfinder)
      return;

    const UInt32 width = m_pathfinder->getWidth();
    const UInt32 height = m_pathfinder->getHeight();

    Vector<sf::Vertex> vertices;
    vertices.reserve(width * height);

    for (UInt32 y = 0; y < height; ++y)
    {
      for (UInt32 x = 0; x < width; ++x)
      {
        SharedPtr<Node> node = m_pathfinder->getNodeAt(x, y);
        if (!node)
          continue;

        sf::Color color = node->isWalkable() ? sf::Color::Green : sf::Color::Red;

        sf::Vertex vertex = { node->getPosition(), color };
        vertices.emplace_back(vertex);
      }
    }

    if (!vertices.empty())
    {
      glPointSize(PATHFINDER_GRID_POINT_SIZE); // Set point size
      window.draw(&vertices[0], static_cast<unsigned>(vertices.size()), sf::PrimitiveType::Points);
      glPointSize(1.0f); // Reset to default after drawing
    }
  }
}