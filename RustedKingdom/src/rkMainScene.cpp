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
#include "rkTiledMapUtilities.h"
#include "rkTiledSceneCreator.h"
#include "rkTiledColliderComponentFactory.h"
#include "rkLuciusBlueprint.h"

#include "rkTiledClassApplierMapper.h"
#include "rkBaseTiledClassApplier.h"
#include "rkMinimapTiledClassApplier.h"

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
    ILevelScene::init(serviceLocator);
    m_assetManager = serviceLocator.getService<AssetManager>();
    m_windowManager = serviceLocator.getService<WindowManager>();
  }

  void MainScene::onLoad()
  {
    ILevelScene::onLoad();

    loadAssets();
    createScene();

    prepareMinimap(
      m_assetManager->getAssetGroup<TiledMap>().get("level-0")->getTmrTiledMap()
    );
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

    m_assetManager->getAssetGroup<TiledMap>().loadFromFile(
      "ui",
      m_assetManager->combineAssetDirectoryWithPath("maps/level-ui.tmx")
    );
    tiledMapAssetLoader::loadTiledMapAssets(*m_assetManager, "ui");

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

    TiledColliderComponentFactory tiledColliderComponentFactory(colliderComponentFactory);
    TiledClassApplierMapper tiledClassApplierMapper;
    
    tiledClassApplierMapper.registerClassApplier(
      "",
      MakeShared<BaseTiledClassApplier>(
        spriteComponentFactory,
        tiledColliderComponentFactory
      )
    );

    tiledClassApplierMapper.registerClassApplier(
      "Minimap",
      MakeShared<MinimapTiledClassApplier>(
        spriteComponentFactory,
        tiledColliderComponentFactory
      )
    );

    tiledSceneCreator::create(
      "level-0",
      *m_assetManager,
      tiledClassApplierMapper,
      spriteComponentFactory,
      m_sceneGraph
    );

    tiledSceneCreator::create(
      "ui",
      *m_assetManager,
      tiledClassApplierMapper,
      spriteComponentFactory,
      m_uiSceneGraph
    );

    createPathfinders();

    // Create Lucius
    SharedPtr<IPositionTransformer> positionTransform =
      tiledMapUtilities::getPositionTransformer(*tiledMap);

    AnimationFactory animationFactory(*m_assetManager);
    LuciusBlueprint luciusBlueprint(
      gameObjectBuilder,
      spriteComponentFactory,
      animationFactory,
      rigidBodyComponentFactory,
      colliderComponentFactory,
      m_pathfinderManager.getPathfinder("characters"),
      positionTransform,
      m_windowManager->getRenderWindow()
    );

    GameObject* plantas = m_sceneGraph.getRoot()->findChildByName("plantas");

    m_sceneGraph.instantiateGameObject(
      luciusBlueprint,
      sf::Vector2f(200.0f, 200.0f),
      *plantas
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
      tiledMapUtilities::getPositionTransformer(*tiledMap)
    );
  }
}