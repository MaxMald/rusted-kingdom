#include <SFML/Graphics.hpp>
#include "rkAssetManager.h"
#include "rkSceneGraph.h"
#include "rkSpriteSheet.h"
#include "rkSpriteGameObject.h"

int main()
{
  sf::RenderWindow window(sf::VideoMode({ 500, 500 }), "SFML works!");

  rk::AssetManager assetManager("F:/Repositories/MaxMald/rusted-kingdom/assets");
  assetManager.loadTexture(
    "land_textures",
    "textures/terrain/128x64 Ground Tiles - Update 1.png"
  );

  rk::SpriteSheet spriteSheet(
    assetManager.getTexture("land_textures"),
    128,
    64
  );

  // Create a SpriteGameObject for a land tile
  auto landTile = std::make_unique<rk::SpriteGameObject>(
    assetManager.getTexture("land_textures"),
    spriteSheet.getSpriteRect(0)
  );
  landTile->setPosition(sf::Vector2f(32.0f, 32.0f));

  // Create the scene graph and add the land tile
  rk::SceneGraph sceneGraph;
  sceneGraph.getRoot()->addChild(std::move(landTile));

  while (window.isOpen())
  {
    // Process events
    while (const std::optional event = window.pollEvent())
    {
      // Close window: exit
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear();

    window.draw(sceneGraph);

    window.display();
  }

  assetManager.clear();
}