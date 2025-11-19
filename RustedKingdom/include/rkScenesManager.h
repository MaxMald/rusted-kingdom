#pragma once

#include <SFML/Graphics/RenderStates.hpp>

#include "rkIService.h"

namespace sf
{
  class RenderTarget;
}

using sf::RenderTarget;
using sf::RenderStates;

namespace rk
{
  class Scene;

  class ScenesManager : public IService
  {
  public:
    ScenesManager();
    virtual ~ScenesManager();

    void registerScene(const String& key, SharedPtr<Scene> scene);
    void setNextScene(const String& key);

  protected:
    virtual void destroy() override;

  private:
    void update(float deltaTime);
    void draw(RenderTarget& window, RenderStates states) const;

    UnorderedMap<String, SharedPtr<Scene>> m_scenes;
    SharedPtr<Scene> m_activeScene;
    SharedPtr<Scene> m_nextScene;
  };
}