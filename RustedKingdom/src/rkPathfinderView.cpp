#include "rkPathfinderView.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "rkPathfinder.h"
#include "rkIsometricTransformation.h"

namespace rk
{
  PathfinderView::PathfinderView(Pathfinder& pathfinder) :
    m_pathfinder(pathfinder)
  {
  }

  void PathfinderView::draw(sf::RenderTarget& target, sf::RenderStates) const
  {
    sf::CircleShape pointShape;
    pointShape.setFillColor(sf::Color::White);

    float radius = 2.0f;
    pointShape.setRadius(radius);
    sf::Vector2f origin(radius, radius);
    sf::Vector2f normalization(1.0f/64.0f, 1.0f/64.0f);

    for (UInt32 y = 0; y < m_pathfinder.getHeight(); ++y)
    {
      for (UInt32 x = 0; x < m_pathfinder.getWidth(); ++x)
      {
        auto node = m_pathfinder.getNodeAt(x, y);
        Vector2f pointPosition = node->getPosition();

        pointPosition.x = pointPosition.x * normalization.x;
        pointPosition.y = pointPosition.y * normalization.y;

        pointPosition = isometricTransformation::isometricToWorld(
          pointPosition,
          64,
          32
        );

        pointShape.setPosition(pointPosition);
        target.draw(pointShape);
      }
    }
  }
}