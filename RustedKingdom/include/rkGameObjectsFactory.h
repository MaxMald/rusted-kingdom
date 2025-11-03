#pragma once

#include "rkPrerequisites.h"
#include <SFML/Graphics/Rect.hpp>

namespace sf
{
  class Texture;
}

namespace rk
{
  class AssetManager;
  class SceneGraph;
  class SpriteGameObject;

  /**
   * @brief Factory responsible for creating game objects and registering them
   * into a SceneGraph.
   */
  class GameObjectsFactory
  {
  public:

    /**
     * @brief Construct a new GameObjectsFactory.
     *
     * @param sceneGraph Pointer to the SceneGraph that will receive created
     * objects. The factory will register newly created objects into this graph.
     * @param assetsManager Pointer to the AssetManager used to obtain textures
     * and other resources. The AssetManager must outlive the objects created by
     * this factory.
     */
    GameObjectsFactory(
      SceneGraph* sceneGraph,
      const AssetManager* assetsManager
    );

    /**
     * @brief Default destructor.
     */
    ~GameObjectsFactory() = default;

    /**
     * @brief Create a SpriteGameObject using the full texture identified by
     * `textureKey`.
     *
     * @param textureKey Key used to lookup the texture in the AssetManager.
     * @return Pointer to the created SpriteGameObject, or nullptr if creation
     * failed.
     */
    SpriteGameObject* createSpriteGameObject(
      const String& textureKey
    );

    /**
     * @brief Create a SpriteGameObject using a sub-rectangle of a texture.
     *
     * @param textureKey Key used to lookup the texture in the AssetManager.
     * @param textureRect Sub-rectangle of the texture to use for the sprite
     * (pixels).
     * @return Pointer to the created SpriteGameObject, or nullptr if creation
     * failed.
     */
    SpriteGameObject* createSpriteGameObject(
      const String& textureKey,
      const sf::IntRect& textureRect
    );

  private:

    SceneGraph* m_sceneGraph;              ///< SceneGraph where created objects are registered.
    const AssetManager* m_assetsManager;   ///< Asset manager used to resolve textures/resources.
  };
}