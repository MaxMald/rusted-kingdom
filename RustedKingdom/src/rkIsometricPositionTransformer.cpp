#include "rkIsometricPositionTransformer.h"

namespace rk
{
  IsometricPositionTransformer::IsometricPositionTransformer() :
    m_a(0.0f),
    m_b(0.0f)
  {
  }

  IsometricPositionTransformer::IsometricPositionTransformer(
    UInt32 tileWidth,
    UInt32 tileHeight
  )
  {
    if (tileHeight == 0 || tileWidth == 0)
    {
      throw InvalidArgumentException(
        "IsometricPositionTransformer constructor: "
        "tileWidth and tileHeight must be greater than zero"
      );
    }
    
    float halfWidth = static_cast<float>(tileWidth) * 0.5f;
    float halfHeight = static_cast<float>(tileHeight) * 0.5f;
    float oneOverHeight = 1.0f / static_cast<float>(tileHeight);

    m_a = halfWidth * oneOverHeight;
    m_b = halfHeight * oneOverHeight;
  }

  IsometricPositionTransformer::IsometricPositionTransformer(
    const IsometricPositionTransformer& other
  ) :
    m_a(other.m_a),
    m_b(other.m_b)
  {
  }

  IsometricPositionTransformer::IsometricPositionTransformer(
    IsometricPositionTransformer&& other
  ) noexcept :
    m_a(other.m_a),
    m_b(other.m_b)
  {
  }

  IsometricPositionTransformer& IsometricPositionTransformer::operator=(
    const IsometricPositionTransformer& other
    )
  {
    if (this != &other)
    {
      m_a = other.m_a;
      m_b = other.m_b;
    }
    return *this;
  }

  IsometricPositionTransformer& IsometricPositionTransformer::operator=(
    IsometricPositionTransformer&& other
    ) noexcept
  {
    if (this != &other)
    {
      m_a = other.m_a;
      m_b = other.m_b;
    }
    return *this;
  }

  Vector2f IsometricPositionTransformer::worldToIsometric(
    float x,
    float y
  ) const
  {
   // Inverse of isometricToWorld:
   // isometricToWorld(x, y):
   //   worldX = (x - y) * a
   //   worldY = (x + y) * b
   // 
   // Solve for x and y in terms of worldX and worldY:
   // x = (worldX / a + worldY / b) / 2
   // y = (worldY / b - worldX / a) / 2

    return Vector2f(
      ((x / m_a) + (y / m_b)) * 0.5f,
      ((y / m_b) - (x / m_a)) * 0.5f
    );
  }

  Vector2f IsometricPositionTransformer::worldToIsometric(
    const Vector2f& worldPosition
  ) const
  {
    return worldToIsometric(
      worldPosition.x,
      worldPosition.y
    );
  }

  Vector2f IsometricPositionTransformer::isometricToWorld(
    float x,
    float y
  ) const
  {
    return Vector2f(
      (x - y) * m_a,
      (x + y) * m_b
    );
  }

  Vector2f IsometricPositionTransformer::isometricToWorld(
    const Vector2f& isometricPosition
  ) const
  {
    return isometricToWorld(
      isometricPosition.x,
      isometricPosition.y
    );
  }
}