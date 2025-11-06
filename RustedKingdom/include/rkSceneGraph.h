#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include "rkPrerequisites.h"
#include "rkGameObject.h"

namespace rk
{
  /**
   * @brief Manages the hierarchy and lifecycle of GameObjects in the scene.
   *
   * SceneGraph owns all GameObjects, provides root node access, and supports
   * creation, destruction, and traversal of the scene hierarchy.
   */
  class SceneGraph : public sf::Drawable
  {
  public:
    SceneGraph();
    ~SceneGraph();

    /**
     * @brief Gets the root GameObject of the scene.
     *
     * @return Pointer to the root GameObject.
     */
    GameObject* getRoot() const;

    /**
     * @brief Updates the entire scene graph.
     *
     * @param deltaTime Time elapsed since last update (in seconds).
     */
    void update(float deltaTime);

    /**
     * @brief Draws all GameObjects in the scene graph, sorted by Y position for
     * correct isometric rendering.
     *
     * @param target The SFML render target to draw onto (e.g., window or
     * texture).
     * @param states The current render states (transform, blend mode, etc.) to
     * use for drawing.
     */
    void draw(RenderTarget& target, RenderStates states) const override;

  private:
    UniquePtr<GameObject> m_root;
  };
}