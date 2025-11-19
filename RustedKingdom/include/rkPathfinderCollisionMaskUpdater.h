#pragma once

#include "rkPrerequisites.h"
#include "rkIsometricPositionTransformer.h"
#include "rkPhysicWorldListener.h"
#include "rkNonCopyable.h"

namespace rk
{
  class Pathfinder;
  class PhysicWorld;
  class Node;

  class PathfinderCollisionMaskUpdater :
    public PhysicWorldListener,
    public NonCopyable
  {
  public:
    PathfinderCollisionMaskUpdater(
      SharedPtr<Pathfinder> pathfinder,
      PhysicWorld& physicWorld,
      const String& collidersGroupKey,
      const IsometricPositionTransformer& isometricPositionTransformer
    );
    virtual ~PathfinderCollisionMaskUpdater();

    virtual void onColliderChanged(Collider* collider) override;

  private:
    SharedPtr<Pathfinder> m_pathfinder;
    PhysicWorld& m_physicWorld;
    IsometricPositionTransformer m_isometricPositionTransformer;
    String m_collidersGroupKey;

    void setNodesAsWalkable();
    void updateNodesWalkableStates();
    void updateNodesAgainstCollider(Collider* collider);
  };
}