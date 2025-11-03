#include <SFML/Graphics.hpp>
#include <TMR/tmrTiledMapReader.h>
#include <TMR/tmrTiledMap.h>
#include "rkAssetManager.h"
#include "rkSceneGraph.h"
#include "rkSpriteSheet.h"
#include "rkSpriteGameObject.h"
#include "rkTiledMapBuilder.h"
#include "rkGameObjectsFactory.h"

int main()
{
  String assetsPath = "C:/Users/nuup2/OneDrive/Documentos/Repositories/MaxMald/rusted-kingdom/assets";
  // std::string assetsPath = "F:/Repositories/MaxMald/rusted-kingdom/assets";

  sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");

  rk::AssetManager assetManager(assetsPath.c_str());
  rk::SceneGraph sceneGraph;

  rk::GameObjectsFactory gameObjectsFactory(
    &sceneGraph,
    &assetManager
  );

  bool result = false;
  result = assetManager.loadTiledMap("level-0", "maps/level-0.json");
  if (!result)
    return -1;

  result = assetManager.loadAssetsFromTiledMap("level-0");
  if (!result)
    return -1;

  rk::TiledSceneBuilder::buildFromTiledMap(
    gameObjectsFactory,
    *assetManager.getTiledMap("level-0")
  );

  assetManager.loadTexture("testText", "textures/terrain/128x64 Dirt A to Dirt B.png");
  rk::SpriteGameObject* testSprite = gameObjectsFactory.createSpriteGameObject("testText");
  testSprite->setPosition({ 400.f, 300.f });

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