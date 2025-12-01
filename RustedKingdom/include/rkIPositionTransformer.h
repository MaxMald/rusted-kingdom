#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"

using sf::Vector2f;

namespace rk
{
  class IPositionTransformer
  {
  public:
    virtual Vector2f transform(const Vector2f& position) const = 0;
    virtual Vector2f transform(float x, float y) const = 0;
    virtual Vector2f inverseTransform(const Vector2f& position) const = 0;
    virtual Vector2f inverseTransform(float x, float y) const = 0;

  protected:
    IPositionTransformer() = default;
    virtual ~IPositionTransformer() = default;
  };
}