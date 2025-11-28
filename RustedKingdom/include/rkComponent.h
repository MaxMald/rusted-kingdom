#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

using sf::RenderTarget;
using sf::RenderStates;

namespace rk
{
  class GameObject;

  class Component : NonCopyable
  {
  public:
    Component(GameObject& gameObject);
    virtual ~Component() = default;

  protected:
    GameObject* m_gameObject;

    virtual void onCreate();
    virtual void onUpdate(float deltaTime);
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void onDelete();

    friend class GameObject;
  };
}