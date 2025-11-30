#pragma once

#include <SFML/Graphics/RenderStates.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkSceneGraph.h"
#include "rkPhysicWorld.h"

namespace sf
{
  class RenderTarget;
}

using sf::RenderTarget;
using sf::RenderStates;

namespace rk
{
  class ServiceLocator;

  class IScene : public NonCopyable
  {
  public:
    IScene();
    virtual ~IScene();

    SceneGraph& getSceneGraph() { return m_sceneGraph; }
    const SceneGraph& getSceneGraph() const { return m_sceneGraph; }
    PhysicWorld& getPhysicWorld() { return m_physicsWorld; }
    const PhysicWorld& getPhysicWorld() const { return m_physicsWorld; }

  protected:
    SceneGraph m_sceneGraph;
    PhysicWorld m_physicsWorld;

    virtual void init(ServiceLocator&) = 0;
    virtual void onLoad() = 0;
    virtual void onUnload() = 0;
    virtual void preUpdate(float deltaTime) = 0;
    virtual void postUpdate(float deltaTime) = 0;
    virtual void postDraw(RenderTarget& window, RenderStates states) const;

  private:
    void load();
    void unload();
    void update(float deltaTime);
    void draw(RenderTarget& window, RenderStates states) const;

    friend class ScenesManager;
  };
}