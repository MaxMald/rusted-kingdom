#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "rkPrerequisites.h"

using sf::RenderTarget;
using sf::RenderStates;

namespace rk
{
  class SceneGraph;
  class Component;
  class ScriptComponent;
  class ServiceLocator;

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
    GameObject(const String& name);

    /**
     * @brief Virtual destructor.
     *
     * Automatically deletes all child GameObjects.
     */
    virtual ~GameObject();

    /** @brief Returns the computed world transform for this object.*/
    const sf::Transform & getWorldTransform() const { return m_worldTransform; }

    /** @brief Returns the world position of this GameObject.*/
    sf::Vector2f getWorldPosition() const;

    void addComponent(UniquePtr<Component> component);

    template<typename T>
    bool hasComponent() const
    {
      static_assert(
        IsBaseOf<Component, T>::value,
        "Component must derive from rk::Component"
      );

      for (const auto& comp : m_components)
      {
        if (typeid(T) == typeid(*comp))
          return true;
      }

      return false;
    }

    /**
     * @brief Retrieves a component of the specified type.
     * @param type The type of component to retrieve.
     * @return Pointer to the component if found, nullptr otherwise.
     */
    template<typename T>
    T* getComponent()
    {
      static_assert(
        IsBaseOf<Component, T>::value,
        "Component must derive from rk::Component"
      );

      for (const auto& comp : m_components)
      {
        if (typeid(T) == typeid(*comp))
          return static_cast<T*>(comp.get());
      }

      throw RuntimeErrorException(
        String::Format("Component of type %s not found", typeid(T).name())
      );
    }

    /**
     * @brief Retrieves all components of the specified type.
     * @param type The type of components to retrieve.
     * @return Vector of pointers to the components found.
     */
    template<typename T>
    Vector<T*> getComponents() const
    {
      static_assert(
        IsBaseOf<Component, T>::value,
        "Component must derive from rk::Component"
      );

      Vector<T*> result;
      for (const auto& comp : m_components)
      {
        if (typeid(T) == typeid(*comp))
          result.push_back(static_cast<T*>(comp.get()));
      }

      return result;
    }

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
     * @return Name.
     */
    const String& getName() const;

    /**
     * @brief Finds a child GameObject by name (recursive search). It returns the
     * first match found.
     *
     * @param name Name of the child to find.
     *
     * @return Pointer to the child GameObject, or nullptr if not found.
     */
    GameObject* findChildByName(const String& name);

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
     * @brief The children of this GameObject.
     */
    Vector<UniquePtr<GameObject>> m_children;

    /**
     * @brief Updates this GameObject and recursively updates its children.
     *
     * @param deltaTime Time elapsed since last update (in seconds).
     */
    virtual void update(float deltaTime);

    /**
     * @brief Draws this GameObject. Override to implement custom rendering.
     *
     * @param target The SFML render target to draw onto (e.g., window or
     * texture).
     * @param states The current render states (transform, blend mode, etc.) to
     * use for drawing.
     */
    virtual void draw(RenderTarget& target, RenderStates states) const override;

    /**
     * @brief Called when the GameObject is being deleted.
     *
     * Override to implement custom cleanup logic.
     */
    virtual void onDelete();

  private:
    String m_name;
    GameObject* m_parent;
    Vector<UniquePtr<Component>> m_components;

    /**
     * @brief Called when the GameObject is created.
     */
    void onCreate();

    friend class SceneGraph;
  };
}
