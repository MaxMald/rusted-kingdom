#include <SFML/Graphics.hpp>
#include <TMR/tmrTiledMapReader.h>
#include <TMR/tmrTiledMap.h>

#include "rkAssetManager.h"
#include "rkSceneGraph.h"
#include "rkSpriteSheet.h"
#include "rkTiledSceneFactory.h"
#include "rkTiledMap.h"
#include "rkViewsManager.h"
#include "rkGameObjectBuilder.h"
#include "rkGameObject.h"
#include "rkSpriteComponentFactory.h"
#include "rkLuciusBlueprint.h"
#include "rkAnimationFactory.h"
#include "rkPhysicWorld.h"
#include "rkRigidBodyComponentFactory.h"
#include "rkColliderComponentFactory.h"
#include "rkPathfinder.h"
#include "rkPathfinderFactory.h"
#include "rkPathfinderCollisionMaskUpdater.h"

#include "scripts/rkLucius.h"

int main()
{
  //String assetsPath = "C:/Users/nuup2/OneDrive/Documentos/Repositories/MaxMald/rusted-kingdom/assets";
  String assetsPath = "F:/Repositories/MaxMald/rusted-kingdom/assets";

  sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");

  rk::AssetManager assetManager(assetsPath.c_str());
  rk::GameObjectBuilder gameObjectBuilder;
  rk::SceneGraph sceneGraph;
  rk::SpriteComponentFactory spriteComponentFactory(assetManager);
  rk::PhysicWorld physicWorld;
  rk::RigidBodyComponentFactory rigidBodyComponentFactory(physicWorld);
  rk::ColliderComponentFactory colliderComponentFactory(physicWorld);
  rk::TiledSceneFactory tiledSceneFactory(
    gameObjectBuilder,
    spriteComponentFactory,
    rigidBodyComponentFactory,
    colliderComponentFactory,
    sceneGraph,
    physicWorld
  );

  physicWorld.createCollidersGroup("characters");

  bool result = false;
  result = assetManager.loadTiledMap("level-0", "maps/level-3.json");
  if (!result)
    return -1;

  result = assetManager.loadAssetsFromTiledMap("level-0");
  if (!result)
    return -1;

  tiledSceneFactory.create(assetManager.getTiledMap("level-0"));

  sf::FloatRect initialRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1920.0f, 1080.0f));
  rk::ViewsManager viewsManager(initialRect);

  assetManager.loadTexture(
   "lucius-walking",
   "textures/characters/lucius/lucius-walking.png"
  );

  assetManager.loadTexture(
    "lucius-running",
    "textures/characters/lucius/lucius-running.png"
  );

  assetManager.loadEightDirectionAnimationBundle(
    "animations/luciusAnimationBundle.json"
  );

  rk::TiledMap& tiledMap = assetManager.getTiledMap("level-0");
  rk::SharedPtr<rk::Pathfinder> pathfinder = rk::pathfinderFactory::createFromIsometricTiledMap(
    tiledMap
  );

  rk::PathfinderCollisionMaskUpdater pathfinderCollisionMaskUpdater(
    pathfinder,
    physicWorld,
    "plantas",
    tiledMap.getIsometricPositionTransformer()
  );

  rk::AnimationFactory animationFactory(assetManager);
  rk::LuciusBlueprint luciusBlueprint(
    gameObjectBuilder,
    spriteComponentFactory,
    animationFactory,
    rigidBodyComponentFactory,
    colliderComponentFactory,
    pathfinder,
    tiledMap.getIsometricPositionTransformer(),
    window
  );

  sceneGraph.instantiateGameObject(
    luciusBlueprint,
    sf::Vector2f(200.0f, 200.0f)
  );
  
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

    physicWorld.update(deltaTime.asSeconds());
    sceneGraph.update(deltaTime.asSeconds());

    window.clear();
    window.draw(sceneGraph);
    window.display();
  }

  sceneGraph.destroy();
  assetManager.clear();
}