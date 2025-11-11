#include <SFML/Graphics.hpp>
#include <TMR/tmrTiledMapReader.h>
#include <TMR/tmrTiledMap.h>
#include "rkAssetManager.h"
#include "rkSceneGraph.h"
#include "rkSpriteSheet.h"
#include "rkTiledMapBuilder.h"
#include "rkViewsManager.h"
#include "rkGameObjectBuilder.h"
#include "rkGameObject.h"

int main()
{
  //String assetsPath = "C:/Users/nuup2/OneDrive/Documentos/Repositories/MaxMald/rusted-kingdom/assets";
  String assetsPath = "F:/Repositories/MaxMald/rusted-kingdom/assets";

  sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");

  rk::AssetManager assetManager(assetsPath.c_str());
  rk::GameObjectBuilder gameObjectBuilder(assetManager);
  rk::SceneGraph sceneGraph;

  bool result = false;
  result = assetManager.loadTiledMap("level-0", "maps/level-2.json");
  if (!result)
    return -1;

  result = assetManager.loadAssetsFromTiledMap("level-0");
  if (!result)
    return -1;

  rk::TiledSceneBuilder::buildFromTiledMap(
    gameObjectBuilder,
    sceneGraph,
    *assetManager.getTiledMap("level-0")
  );

  sf::FloatRect initialRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1920.0f, 1080.0f));
  rk::ViewsManager viewsManager(initialRect);

  assetManager.loadTexture(
   "lucius-walking",
   "textures/characters/lucius/lucius-running.png"
  );

  assetManager.loadEightDirectionAnimationBundle(
    "animations/luciusAnimationBundle.json"
  );

  rk::UniquePtr<rk::GameObject> lucius = gameObjectBuilder.createGameObject("Lucius")
    .position(sf::Vector2f(400.0f, 300.0f))
    .withSpriteComponent("lucius-walking")
    .withAnimationComponent("lucius-walking-anim")
    .build();

  sf::Clock deltaClock;
  while (window.isOpen())
  {
    // Process events
    while (const std::optional event = window.pollEvent())
    {
      // Close window: exit
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    sf::Time deltaTime = deltaClock.restart();

    viewsManager.update(deltaTime.asSeconds());
    window.setView(viewsManager.getWorldView());

    sceneGraph.update(deltaTime.asSeconds());

    window.clear();
    window.draw(sceneGraph);
    window.display();
  }

  assetManager.clear();
}