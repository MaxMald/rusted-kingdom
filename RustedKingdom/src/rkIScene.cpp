#include "rkIScene.h"

namespace rk
{
  IScene::IScene(const String& key, ServiceLocator& serviceLocator) :
    m_key(key),
    m_sceneGraph(),
    m_physicsWorld(),
    m_serviceLocator(serviceLocator)
  {
  }

  IScene::~IScene()
  {
  }

  void IScene::load()
  {
    onLoad();
  }

  void IScene::unload()
  {
    onUnload();
    m_sceneGraph.destroy();
    m_physicsWorld.destroy();
  }

  void IScene::update(float deltaTime)
  {
    m_physicsWorld.update(deltaTime);
    m_sceneGraph.update(deltaTime);
  }

  void IScene::draw(RenderTarget& window, RenderStates states) const
  {
    m_sceneGraph.draw(window, states);
  }
}