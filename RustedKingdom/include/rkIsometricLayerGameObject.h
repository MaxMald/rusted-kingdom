#pragma once

#include "rkGameObject.h"

namespace rk
{
  /**
   * @brief Represents a game object that acts as an isometric layer in the scene
   * graph.
   *
   * It provides functionality to update itself and sort its children by their Y
   * position, which is useful for rendering order in isometric or 2D scenes.
   */
  class IsometricLayerGameObject : public GameObject
  {
  public:
    /**
     * @brief Constructs a IsometricLayerGameObject with the given name.
     * @param name The name of the isometric layer game object.
     */
    IsometricLayerGameObject(const String& name);

    /**
     * @brief Destructor.
     */
    virtual ~IsometricLayerGameObject();

    /**
     * @brief Sets whether the isometric layer is static.
     *
     * @param isStatic True if the layer is static, false otherwise.
     */
    void setStaticLayer(bool isStatic) { m_staticLayer = isStatic; }

    /**
     * @brief Updates the isometric layer game object.
     * @param deltaTime Time elapsed since the last update (in seconds).
     */
    virtual void update(float deltaTime) override;

    /**
     * @brief Sorts the child game objects by their Y position.
     */
    void sortChildrenByYPosition();

  protected:
    /**
     * @brief Indicates whether the isometric layer is static (does not change).
     */
    bool m_staticLayer;
  };
}
