#include "rkPathfinderComponent.h"
#include "rkPathfinder.h"

namespace rk
{
  PathfinderComponent::PathfinderComponent(GameObject& gameObject) :
    Component(gameObject),
    m_pathfinder(nullptr),
    m_drawPoints(false)
  {
  }

  PathfinderComponent::~PathfinderComponent()
  {
  }

  void PathfinderComponent::setPathfinder(SharedPtr<Pathfinder> pathfinder)
  {
    m_pathfinder = pathfinder;
  }

  Vector<Vector2f> PathfinderComponent::findPath(
    const Vector2f& start,
    const Vector2f& end
  )
  {
    if (!m_pathfinder)
      return Vector<Vector2f>();

    return m_pathfinder->findPath(start, end);
  }
}