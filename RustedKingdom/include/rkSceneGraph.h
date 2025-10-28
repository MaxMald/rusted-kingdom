#pragma once

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
  class SceneGraph
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
     * @brief Draws all GameObjects in the scene graph, sorted by Y position.
     */
    void draw();

  private:

    UniquePtr<GameObject> m_root;

    /**
     * @brief Recursively collects all GameObjects in the hierarchy starting from
     * the given parent.
     *
     * @param parent Pointer to the GameObject to start traversal from.
     * @param gameObjects Reference to a vector that will be filled with pointers
     * to all found GameObjects.
     */
    void getAllGameObjectsRecursively(
      GameObject* parent,
      Vector<GameObject*>& gameObjects
    );

    /**
     * @brief Sorts a vector of GameObject pointers by their Y position.
     *
     * @param gameObjects Reference to a vector of GameObject pointers to be
     * sorted.
     */
    void sortGameObjectsByYPosition(Vector<GameObject*>& gameObjects);
  };
}