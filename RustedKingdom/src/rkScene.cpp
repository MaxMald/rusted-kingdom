#include "rkScene.h"

namespace rk
{
  Scene::Scene(const String& key) :
    m_key(key),
    m_sceneGraph(),
    m_physicsWorld()
  {
  }

  Scene::~Scene()
  {
  }

  void Scene::onLoad()
  {
    // To be overridden by derived classes
  }

  void Scene::onUnload()
  {
    // To be overridden by derived classes
  }

  void Scene::load()
  {
    onLoad();
  }

  void Scene::unload()
  {
    onUnload();
    m_sceneGraph.destroy();
    m_physicsWorld.destroy();
  }

  void Scene::update(float deltaTime)
  {
    m_physicsWorld.update(deltaTime);
    m_sceneGraph.update(deltaTime);
  }

  void Scene::draw(RenderTarget& window, RenderStates states) const
  {
    m_sceneGraph.draw(window, states);
  }
}