#pragma once

#include "rkIPositionTransformer.h"

namespace rk
{
  class OrthogonalPositionTransformer : public IPositionTransformer
  {
  public:

    OrthogonalPositionTransformer() = default;
    ~OrthogonalPositionTransformer() = default;
    OrthogonalPositionTransformer(const OrthogonalPositionTransformer&) = default;
    OrthogonalPositionTransformer(OrthogonalPositionTransformer&&) noexcept = default;
    OrthogonalPositionTransformer& operator=(const OrthogonalPositionTransformer&) = default;
    OrthogonalPositionTransformer& operator=(OrthogonalPositionTransformer&&) noexcept = default;

    virtual Vector2f transform(const Vector2f& position) const override { return position; }
    virtual Vector2f transform(float x, float y) const override { return Vector2f(x, y); }
    virtual Vector2f inverseTransform(const Vector2f& position) const override { return position; }
    virtual Vector2f inverseTransform(float x, float y) const override { return Vector2f(x, y); }
  };
}