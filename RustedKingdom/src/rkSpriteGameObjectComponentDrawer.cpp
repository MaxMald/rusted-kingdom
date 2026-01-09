#include "rkSpriteGameObjectComponentDrawer.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkSpriteComponent.h"

namespace rk
{
  SpriteGameObjectComponentDrawer::SpriteGameObjectComponentDrawer()
    : AGameObjectComponentDrawer("Sprite")
  {
  }

  void SpriteGameObjectComponentDrawer::onDraw(
    Component& component,
    sf::RenderWindow&
  )
  {
    SpriteComponent& spriteComponent =
      static_cast<SpriteComponent&>(component);

    sf::Sprite& sprite = spriteComponent.getSprite();

    ImGui::Image(
      sprite,
      calculateImageSize(sprite)
    );

    sf::IntRect spriteRect = sprite.getTextureRect();
    ImGui::Text("Texture Rect Position: (%d, %d)", 
      spriteRect.position.x,
      spriteRect.position.y
    );
    ImGui::Text("Texture Rect Size: (%d, %d)",
      spriteRect.size.x,
      spriteRect.size.y
    );
    ImGui::Text("Origin: (%.2f, %.2f)",
      sprite.getOrigin().x,
      sprite.getOrigin().y
    );
  }

  sf::Vector2f SpriteGameObjectComponentDrawer::calculateImageSize(
    const sf::Sprite& sprite
  )
  {
    const float maxWidth = 100.f;
    const float maxHeight = 100.f;

    sf::FloatRect localBounds = sprite.getLocalBounds();

    float width = localBounds.size.x * sprite.getScale().x;
    float height = localBounds.size.y * sprite.getScale().y;

    if (width <= 0.f || height <= 0.f)
      return sf::Vector2f(0.f, 0.f);

    float scale = std::min(maxWidth / width, maxHeight / height);

    scale = std::min(scale, 1.0f);

    return sf::Vector2f(width * scale, height * scale);
  }
}