#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "rkPrerequisites.h"
#include "rkComponentType.h"
#include "rkNonCopyable.h"

using sf::RenderTarget;
using sf::RenderStates;

namespace rk
{
  class GameObject;

  class Component : NonCopyable
  {
  public:
    Component(GameObject& gameObject, componentType::Type type);
    virtual ~Component() = default;

    componentType::Type getType() const { return m_type; }

  protected:
    GameObject* m_gameObject;

    virtual void onCreate();
    virtual void onUpdate(float deltaTime);
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void onDelete();

  private:
    componentType::Type m_type;

    friend class GameObject;
  };
}