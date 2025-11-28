#include "rkPathfinderComponent.h"
#include "rkPathfinder.h"

namespace rk
{
  PathfinderComponent::PathfinderComponent(
    GameObject& gameObject,
    SharedPtr<Pathfinder> pathfinder
  ) :
    Component(gameObject),
    m_pathfinder(nullptr),
    m_drawPoints(false)
  {
    if (!pathfinder)
    {
      throw InvalidArgumentException(
        "PathfinderComponent constructor: pathfinder is a null pointer"
      );
    }

    m_pathfinder = pathfinder;
  }

  PathfinderComponent::~PathfinderComponent()
  {
  }

  Vector<Vector2f> PathfinderComponent::findPath(
    const Vector2f& start,
    const Vector2f& end
  )
  {
    return m_pathfinder->findPath(start, end);
  }
}