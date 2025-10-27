#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include "rkPrerequisites.h"

namespace rk
{
  /**
 * @brief Represents a game object in the scene graph.
 *
 * GameObject provides transformation, parent-child hierarchy, and extensibility
 * for game logic. Inherits from sf::Transformable for position, rotation, and
 * scale management.
 */
  class GameObject : public sf::Transformable
  {
  public:

    /**
     * @brief Constructs a GameObject with a default name.
     */
    GameObject();

    /**
     * @brief Constructs a GameObject with the specified name.
     *
     * @param name Name of the GameObject.
     */
    GameObject(const char* name);

    /**
     * @brief Virtual destructor for GameObject.
     */
    virtual ~GameObject();

    /**
     * @brief Gets the name of this GameObject.
     *
     * @return Name of the GameObject.
     */
    const char* getName() const;

    /**
     * @brief Updates this GameObject and its children.
     * 
     * @param deltaTime Time elapsed since last update (in seconds).
     */
    void update(float deltaTime);

    /**
     * @brief Adds a child GameObject to this object.
     *
     * @param child Unique pointer to the child GameObject.
     */
    void addChild(UniquePtr<GameObject> child);

    /**
     * @brief Removes all child GameObjects.
     */
    void clearChildren();

    /**
     * @brief Gets the parent GameObject.
     * 
     * @return Pointer to the parent, or nullptr if root.
     */
    GameObject* getParent() const;

    /**
     * @brief Gets the list of child GameObjects.
     * 
     * @return Reference to the vector of unique pointers to children.
     */
    const Vector<UniquePtr<GameObject>>& getChildren() const;

  protected:

    /**
     * @brief Custom update logic for this GameObject.
     * 
     * Override this method in derived classes to implement specific behavior.
     */
    virtual void OnUpdate();

    /**
     * @brief Destroys this GameObject and its children.
     */
    virtual void destroy();

  private:

    const char* m_name;
    GameObject* m_parent;
    Vector<UniquePtr<GameObject>> m_children;
  };
}
