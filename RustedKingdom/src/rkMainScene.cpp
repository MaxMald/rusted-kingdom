#include "rkMainScene.h"
#include "rkServiceLocator.h"
#include "rkAssetManager.h"
#include "rkWindowManager.h"

#include "rkPathfinderFactory.h"
#include "rkPathfinderCollisionMaskUpdater.h"
#include "rkTiledMap.h"
#include "rkGameObjectBuilder.h"
#include "rkAnimationFactory.h"
#include "rkSpriteComponentFactory.h"
#include "rkRigidBodyComponentFactory.h"
#include "rkColliderComponentFactory.h"
#include "rkTexture.h"
#include "rkEightDirAnimationDesc.h"
#include "rkTiledMapAssetsLoader.h"
#include "rkTiledSceneCreator.h"
#include "rkIsometricPositionTransformerFactory.h"

#include "rkLuciusBlueprint.h"

namespace rk
{
  MainScene::MainScene() :
    ILevelScene(),
    m_assetManager(nullptr),
    m_windowManager(nullptr),
    m_pathfinderCollisionMaskUpdater(nullptr)
  {
  }

  MainScene::~MainScene()
  {
  }

  void MainScene::init(ServiceLocator& serviceLocator)
  {
    m_assetManager = serviceLocator.getService<AssetManager>();
    m_windowManager = serviceLocator.getService<WindowManager>();
  }

  void MainScene::onLoad()
  {
    ILevelScene::onLoad();

    loadAssets();
    createScene();
  }

  void MainScene::onUnload()
  {
    ILevelScene::onUnload();
    m_pathfinderCollisionMaskUpdater = nullptr;
  }

  void MainScene::loadAssets()
  {
    m_assetManager->getAssetGroup<TiledMap>().loadFromFile(
      "level-0",
      m_assetManager->combineAssetDirectoryWithPath("maps/level-5.tmx")
    );
    tiledMapAssetLoader::loadTiledMapAssets(*m_assetManager, "level-0");

    m_assetManager->getAssetGroup<Texture>().loadFromFile(
      "lucius-walking",
      m_assetManager->combineAssetDirectoryWithPath("textures/characters/lucius/lucius-walking.png")
    );
    m_assetManager->getAssetGroup<Texture>().loadFromFile(
      "lucius-running",
      m_assetManager->combineAssetDirectoryWithPath("textures/characters/lucius/lucius-running.png")
    );
    m_assetManager->getAssetGroup<EightDirAnimationDesc>().loadFromFile(
      "lucius-idle-anim",
      m_assetManager->combineAssetDirectoryWithPath("animations/lucius-idle-anim.json")
    );
    m_assetManager->getAssetGroup<EightDirAnimationDesc>().loadFromFile(
      "lucius-walking-anim",
      m_assetManager->combineAssetDirectoryWithPath("animations/lucius-walking-anim.json")
    );
    m_assetManager->getAssetGroup<EightDirAnimationDesc>().loadFromFile(
      "lucius-running-anim",
      m_assetManager->combineAssetDirectoryWithPath("animations/lucius-running-anim.json")
    );
  }

  void MainScene::createScene()
  {
    GameObjectBuilder gameObjectBuilder;
    SpriteComponentFactory spriteComponentFactory(*m_assetManager);
    RigidBodyComponentFactory rigidBodyComponentFactory(m_physicsWorld);
    ColliderComponentFactory colliderComponentFactory(m_physicsWorld);

    m_physicsWorld.createCollidersGroup("characters");
    m_physicsWorld.createCollidersGroup("plantas");
    SharedPtr<TiledMap> tiledMap = m_assetManager->getAssetGroup<TiledMap>()
      .get("level-0");

    tiledSceneCreator::create(
      "level-0",
      *m_assetManager,
      spriteComponentFactory,
      m_sceneGraph
    );

    createPathfinders();

    // Create Lucius
    AnimationFactory animationFactory(*m_assetManager);
    LuciusBlueprint luciusBlueprint(
      gameObjectBuilder,
      spriteComponentFactory,
      animationFactory,
      rigidBodyComponentFactory,
      colliderComponentFactory,
      m_pathfinderManager.getPathfinder("characters"),
      isometricPositionTransformerFactory::create(*tiledMap),
      m_windowManager->getRenderWindow()
    );

    m_sceneGraph.instantiateGameObject(
      luciusBlueprint,
      sf::Vector2f(200.0f, 200.0f)
    );
  }

  void MainScene::createPathfinders()
  {
    SharedPtr<TiledMap> tiledMap = m_assetManager->getAssetGroup<TiledMap>()
      .get("level-0");
    SharedPtr<Pathfinder> pathfinder = pathfinderFactory::createFromIsometricTiledMap(
      *tiledMap
    );

    m_pathfinderManager.addPathfinder("characters", pathfinder);

    m_pathfinderCollisionMaskUpdater = MakeUnique<PathfinderCollisionMaskUpdater>(
      pathfinder,
      m_physicsWorld,
      "plantas",
      isometricPositionTransformerFactory::create(*tiledMap)
    );
  }
}