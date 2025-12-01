#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"
#include "rkIPositionTransformer.h"

using sf::Vector2f;

namespace rk
{
  /**
   * @brief Utility for converting between world and isometric coordinates.
   *
   * This class provides methods to transform positions between world
   * (orthogonal) coordinates and isometric coordinates, using the specified tile
   * width and height.
   */
  class IsometricPositionTransformer : public IPositionTransformer
  {
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes the transformer with default tile dimensions.
     */
    IsometricPositionTransformer();

    /**
     * @brief Constructor with tile dimensions.
     *
     * @param tileWidth  Width of a single isometric tile.
     * @param tileHeight Height of a single isometric tile.
     */
    IsometricPositionTransformer(UInt32 tileWidth, UInt32 tileHeight);

    /**
     * @brief Copy constructor.
     */
    IsometricPositionTransformer(const IsometricPositionTransformer&);

    /**
     * @brief Move constructor.
     */
    IsometricPositionTransformer(IsometricPositionTransformer&&) noexcept;

    /**
     * @brief Copy assignment operator.
     */
    IsometricPositionTransformer& operator=(
      const IsometricPositionTransformer&
    );

    /**
     * @brief Move assignment operator.
     */
    IsometricPositionTransformer& operator=(
      IsometricPositionTransformer&&
    ) noexcept;

    virtual Vector2f transform(const Vector2f& position) const override;
    virtual Vector2f transform(float x, float y) const override;
    virtual Vector2f inverseTransform(const Vector2f& position) const override;
    virtual Vector2f inverseTransform(float x, float y) const override;

    /**
     * @brief Convert world coordinates to isometric coordinates.
     *
     * @param x X position in world coordinates.
     * @param y Y position in world coordinates.
     * @return Position in isometric coordinates.
     */
    Vector2f worldToIsometric(float x, float y) const;

    /**
     * @brief Convert world coordinates to isometric coordinates.
     *
     * @param worldPosition Position in world coordinates.
     * @return Position in isometric coordinates.
     */
    Vector2f worldToIsometric(const Vector2f& worldPosition) const;

    /**
     * @brief Convert isometric coordinates to world coordinates.
     *
     * @param x X position in isometric coordinates.
     * @param y Y position in isometric coordinates.
     * @return Position in world coordinates.
     */
    Vector2f isometricToWorld(float x, float y) const;

    /**
     * @brief Convert isometric coordinates to world coordinates.
     *
     * @param isometricPosition Position in isometric coordinates.
     * @return Position in world coordinates.
     */
    Vector2f isometricToWorld(const Vector2f& isometricPosition) const;

  private:
    /**
     * @brief Internal transformation coefficient, usually related to tile width.
     */
    float m_a;

    /**
     * @brief Internal transformation coefficient, usually related to tile
     * height.
     */
    float m_b;
  };
}