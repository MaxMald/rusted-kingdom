#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"
#include "rkColliderType.h"

using sf::Vector2f;

namespace rk
{
  class Collider
  {
  public:
    Collider();
    Collider(colliderType::Type type);
    Collider(const Collider&);
    Collider(Collider&&) noexcept;
    virtual ~Collider();

    Collider& operator=(const Collider&);
    Collider& operator=(Collider&&) noexcept;

    virtual const Vector2f& getCenter() const = 0;
    virtual void setCenter(const Vector2f& center) = 0;
    colliderType::Type getType() const { return m_type; }

    virtual bool checkCollision(const Collider& other) const = 0;

  private:
    colliderType::Type m_type;
  };
}