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
    IScene(const String& key, ServiceLocator&);
    virtual ~IScene();

    const String& getKey() const { return m_key; }
    SceneGraph& getSceneGraph() { return m_sceneGraph; }
    const SceneGraph& getSceneGraph() const { return m_sceneGraph; }
    PhysicWorld& getPhysicWorld() { return m_physicsWorld; }
    const PhysicWorld& getPhysicWorld() const { return m_physicsWorld; }

  protected:
    SceneGraph m_sceneGraph;
    PhysicWorld m_physicsWorld;
    ServiceLocator& m_serviceLocator;

    virtual void onLoad() = 0;
    virtual void onUnload() = 0;

  private:
    String m_key;

    void load();
    void unload();
    void update(float deltaTime);
    void draw(RenderTarget& window, RenderStates states) const;

    friend class ScenesManager;
  };
}