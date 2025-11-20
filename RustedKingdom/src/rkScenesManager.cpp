#include "rkScenesManager.h"
#include "rkIScene.h"

namespace rk
{
  ScenesManager::ScenesManager() :
    m_scenes(),
    m_activeScene(nullptr)
  {
  }

  ScenesManager::~ScenesManager()
  {
  }

  void ScenesManager::registerScene(
    const String& key,
    SharedPtr<IScene> scene
  )
  {
    m_scenes[key] = scene;
  }

  void ScenesManager::setNextScene(const String& key)
  {
    auto it = m_scenes.find(key);
    if (it != m_scenes.end())
    {
      m_nextScene = it->second;
      return;
    }

    throw RuntimeErrorException(
      String::Format("Scene with key '%s' not found.", key.c_str())
    );
  }

  void ScenesManager::init(ServiceLocator&)
  {
    // Intentionally left blank.
  }

  void ScenesManager::destroy()
  {
    if (m_activeScene)
      m_activeScene->unload();

    m_scenes.clear();
    m_activeScene = nullptr;
    m_nextScene = nullptr;
  }

  void ScenesManager::update(float deltaTime)
  {
    if (m_nextScene)
    {
      if (m_activeScene)
        m_activeScene->unload();

      m_activeScene = m_nextScene;
      m_nextScene = nullptr;
      m_activeScene->load();
    }

    if (m_activeScene)
      m_activeScene->update(deltaTime);
  }

  void ScenesManager::draw(
    RenderTarget& window,
    RenderStates states
  ) const
  {
    if (m_activeScene)
      m_activeScene->draw(window, states);
  }

  void ScenesManager::initScenes(ServiceLocator& serviceLocator)
  {
    for (auto& pair : m_scenes)
      pair.second->init(serviceLocator);
  }
}