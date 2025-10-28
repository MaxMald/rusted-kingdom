#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "rkPrerequisites.h"

using sf::RenderTarget;
using sf::RenderStates;

namespace rk
{
  class SceneGraph;

  /**
  * @brief Represents a basic game object in the scene graph.
  *
  * GameObject provides transformation, parent-child hierarchy, and extensibility
  * for game logic. Inherits from sf::Transformable for position, rotation, and
  * scale management.
  */
  class GameObject : public sf::Transformable, public sf::Drawable
  {
  public:

    /**
     * @brief Constructs a new GameObject.
     */
    GameObject();

    /**
     * @brief Constructs a new GameObject with a specified name.
     *
     * @param name Name of the GameObject.
     */
    GameObject(const char* name);

    /**
     * @brief Virtual destructor.
     *
     * Automatically deletes all child GameObjects.
     */
    virtual ~GameObject();

    /**
     * @brief Adds a child GameObject to this object.
     *
     * @param child Unique pointer to the child GameObject.
     */
    void addChild(UniquePtr<GameObject> child);

    /**
     * @brief Removes a specific child GameObject and transfers ownership to the
     * caller.
     *
     * If the child is found, it is removed from this parent and its parent
     * pointer is set to nullptr.
     *
     * @param child Pointer to the child GameObject to remove.
     *
     * @return Unique pointer to the removed child, or nullptr if not found.
     */
    UniquePtr<GameObject> removeChild(GameObject* child);

    /**
     * @brief Detaches this GameObject from its parent and transfers ownership to
     * the caller.
     *
     * If this object has a parent, it is removed from the parent's children and
     * its parent pointer is set to nullptr.
     *
     * @return Unique pointer to this GameObject, or nullptr if it has no parent.
     */
    UniquePtr<GameObject>  detachFromParent();

    /**
     * @brief Removes and deletes all child GameObjects.
     *
     * All children are destroyed and their memory is released.
     */
    void clearChildren();

    /**
     * @brief Gets the name of the GameObject.
     *
     * @return Name as a C-style string.
     */
    const char* getName() const;

    /**
     * @brief Finds a child GameObject by name (recursive search). It returns the
     * first match found.
     *
     * @param name Name of the child to find.
     *
     * @return Pointer to the child GameObject, or nullptr if not found.
     */
    GameObject* findChildByName(const char* name);

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

    /**
     * @brief Updates the transformation of this GameObject based on its parent's
     * transform.
     */
    void updateTransform();

  protected:

    /**
     * @brief The world transform of this GameObject, combining its local
     * transform with its parent's world transform.
     */
    sf::Transform m_worldTransform;

    /**
     * @brief Updates this GameObject and recursively updates its children.
     *
     * @param deltaTime Time elapsed since last update (in seconds).
     */
    void update(float deltaTime);

    /**
     * @brief Called during update to implement custom behavior.
     *
     * @param deltaTime Time elapsed since last update (in seconds).
     */
    virtual void onUpdate(float deltaTime);

    /**
     * @brief Called when the GameObject is being deleted.
     *
     * Override to implement custom cleanup logic.
     */
    virtual void onDelete();

  private:

    const char* m_name;
    GameObject* m_parent;
    Vector<UniquePtr<GameObject>> m_children;

    friend class SceneGraph;
  };
}
