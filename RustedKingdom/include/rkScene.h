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
  class Scene : public NonCopyable
  {
  public:
    Scene(const String& key);
    virtual ~Scene();

    const String& getKey() const { return m_key; }
    SceneGraph& getSceneGraph() { return m_sceneGraph; }
    const SceneGraph& getSceneGraph() const { return m_sceneGraph; }
    PhysicWorld& getPhysicWorld() { return m_physicsWorld; }
    const PhysicWorld& getPhysicWorld() const { return m_physicsWorld; }

  protected:
    SceneGraph m_sceneGraph;
    PhysicWorld m_physicsWorld;

    virtual void onLoad();
    virtual void onUnload();

  private:
    String m_key;

    void load();
    void unload();
    void update(float deltaTime);
    void draw(RenderTarget& window, RenderStates states) const;

    friend class ScenesManager;
  };
}