#include "rkPathfinderCollisionMaskUpdater.h"
#include "rkPathfinder.h"
#include "rkPhysicWorld.h"
#include "rkCollider.h"
#include "rkNode.h"

namespace rk
{
  PathfinderCollisionMaskUpdater::PathfinderCollisionMaskUpdater(
    SharedPtr<Pathfinder> pathfinder,
    PhysicWorld& physicWorld,
    const String& collidersGroupKey,
    SharedPtr<IPositionTransformer> positionTransformer
  ) : 
    m_pathfinder(pathfinder),
    m_physicWorld(physicWorld),
    m_collidersGroupKey(collidersGroupKey),
    m_positionTransformer(positionTransformer)
  {
    m_physicWorld.addListener(this);

    setNodesAsWalkable();
    updateNodesWalkableStates();
  }

  PathfinderCollisionMaskUpdater::~PathfinderCollisionMaskUpdater()
  {
    m_physicWorld.removeListener(this);
  }

  void PathfinderCollisionMaskUpdater::onColliderChanged(Collider* collider)
  {
    if (collider->getCollidersGroupKey() != m_collidersGroupKey)
      return;

    setNodesAsWalkable();
    updateNodesWalkableStates();
  }

  void PathfinderCollisionMaskUpdater::setNodesAsWalkable()
  {
    for (UInt32 x = 0; x < m_pathfinder->getWidth(); ++x)
    {
      for (UInt32 y = 0; y < m_pathfinder->getHeight(); ++y)
      {
        SharedPtr<Node> node = m_pathfinder->getNodeAt(x, y);
        node->setWalkable(true);
      }
    }
  }

  void PathfinderCollisionMaskUpdater::updateNodesWalkableStates()
  {
    const Vector<UniquePtr<Collider>>& colliders = m_physicWorld
      .getColliders(m_collidersGroupKey);

    for (const UniquePtr<Collider>& collider : colliders)
      updateNodesAgainstCollider(collider.get());
  }

  void PathfinderCollisionMaskUpdater::updateNodesAgainstCollider(Collider* collider)
  {
    for (UInt32 x = 0; x < m_pathfinder->getWidth(); ++x)
    {
      for (UInt32 y = 0; y < m_pathfinder->getHeight(); ++y)
      {
        SharedPtr<Node> node = m_pathfinder->getNodeAt(x, y);
        Vector2f nodePosition = node->getPosition();
        Vector2f transformedPosition = 
          m_positionTransformer->inverseTransform(nodePosition);

        if (collider->checkCollision(transformedPosition))
          node->setWalkable(false);
      }
    }
  }
}