#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "rkPrerequisites.h"
#include "rkGameObject.h"

using sf::Vector2f;

namespace rk
{
  class GameObjectBlueprint;

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

    void registerGameObject(UniquePtr<GameObject> gameObject);

    void registerGameObject(UniquePtr<GameObject> gameObject, GameObject& parent);

    /**
     * @brief Instantiates a new GameObject from the given blueprint and adds it
     * as a child to the root GameObject.
     */
    GameObject* instantiateGameObject(
      const GameObjectBlueprint& blueprint,
      const Vector2f& position
    );

    /**
     * @brief Instantiates a new GameObject from the given blueprint and adds it
     * as a child to the root GameObject.
     */
    GameObject* instantiateGameObject(
      const GameObjectBlueprint& blueprint,
      const String& name,
      const Vector2f& position
    );

    /**
     * @brief Instantiates a new GameObject from the given blueprint and adds it
     * as a child to the specified parent GameObject.
     */
    GameObject* instantiateGameObject(
      const GameObjectBlueprint& blueprint,
      const Vector2f& position,
      GameObject& parent
    );

    /**
     * @brief Instantiates a new GameObject from the given blueprint and adds it
     * as a child to the specified parent GameObject.
     */
    GameObject* instantiateGameObject(
      const GameObjectBlueprint& blueprint,
      const String& name,
      const Vector2f& position,
      GameObject& parent
    );

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

    void destroy();

  private:
    UniquePtr<GameObject> m_root;
  };
}