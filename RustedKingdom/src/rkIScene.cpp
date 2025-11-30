#include "rkIScene.h"

namespace rk
{
  IScene::IScene() :
    m_sceneGraph(),
    m_physicsWorld()
  {
  }

  IScene::~IScene()
  {
  }

  void IScene::postDraw(RenderTarget&, RenderStates) const
  {
    // Implement in derived classes if needed
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

    preUpdate(deltaTime);
    m_sceneGraph.update(deltaTime);
    postUpdate(deltaTime);
  }

  void IScene::draw(RenderTarget& window, RenderStates states) const
  {
    m_sceneGraph.draw(window, states);
    postDraw(window, states);
  }
}