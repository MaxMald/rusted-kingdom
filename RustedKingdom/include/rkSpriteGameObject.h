#pragma once

#include "rkGameObject.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace rk
{
  /**
   * @brief A GameObject that displays an SFML sprite.
   *
   * SpriteGameObject extends GameObject to provide sprite rendering. It manages
   * an sf::Sprite and its associated texture.
   */
  class SpriteGameObject : public GameObject
  {
  public:
    /**
     * @brief Constructs a SpriteGameObject with an optional texture.
     *
     * @param texture Pointer to an SFML texture (can be nullptr).
     */
    SpriteGameObject(const sf::Texture* texture = nullptr);

    /**
     * @brief Constructs a SpriteGameObject with a texture and texture rectangle.
     *
     * @param texture Pointer to an SFML texture.
     * @param textureRect Rectangle defining the portion of the texture to use.
     */
    SpriteGameObject(const sf::Texture* texture, const sf::IntRect& textureRect);

    /**
     * @brief Sets the texture for the sprite.
     * 
     * @param texture Pointer to an SFML texture.
     */
    void setTexture(const sf::Texture* texture);

    /**
     * @brief Gets the underlying SFML sprite.
     * 
     * @return Reference to the sprite.
     */
    sf::Sprite& getSprite();

  protected:

    /**
     * @brief Draws the sprite. Override of GameObject::draw.
     */
    virtual void draw(RenderTarget& renderTarget, RenderStates states) const override;

  private:

    sf::Sprite m_sprite;
    const sf::Texture* m_texture;
  };
}