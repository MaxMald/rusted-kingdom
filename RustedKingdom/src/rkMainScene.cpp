#include "rkMainScene.h"
#include "rkServiceLocator.h"
#include "rkAssetManager.h"
#include "rkWindowManager.h"
#include "rkGameObjectBlueprintsManager.h"

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
#include "rkArmyManager.h"

#include "rkTiledClassApplierMapper.h"
#include "rkBaseTiledClassApplier.h"
#include "rkMinimapTiledClassApplier.h"
#include "rkCorpSoldierClassApplier.h"
#include "rkButtonClassApplier.h"
#include "rkBlueprintClassApplier.h"
#include "rkCorpoBasicSoldierBlueprint.h"

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
    createArmies();
    createScene();

    createBoxSelector();
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
    m_assetManager->loadBundle("bundles/mainLevel-bundle.json");
  }

  void MainScene::createArmies()
  {
    m_armyManager->createArmy(
      "User Army",
      factionType::Corps,
      armyControlType::User
    );

    m_armyManager->createArmy(
      "Hostile Army",
      factionType::Bios,
      armyControlType::AI
    );
  }

  void MainScene::createScene()
  {
    GameObjectBuilder gameObjectBuilder;

    m_physicsWorld.createCollidersGroup("characters");
    m_physicsWorld.createCollidersGroup("plantas");
    SharedPtr<TiledMap> tiledMap = m_assetManager->getAssetGroup<TiledMap>()
      .get("level-0");

    TiledClassApplierMapper tiledClassApplierMapper;
    
    tiledClassApplierMapper.registerClassApplier(
      "",
      MakeShared<BaseTiledClassApplier>()
    );

    tiledClassApplierMapper.registerClassApplier(
      "Minimap",
      MakeShared<MinimapTiledClassApplier>()
    );

    tiledClassApplierMapper.registerClassApplier(
      "Button",
      MakeShared<ButtonClassApplier>()
    );

    SharedPtr<GameObjectBlueprintsManager> blueprintsManager =
      ServiceLocator::Instance().getService<GameObjectBlueprintsManager>();

    tiledClassApplierMapper.registerClassApplier(
      "CorpSoldier",
      MakeShared<CorpoSoldierClassApplier>(
        blueprintsManager->get(gameObjectBlueprintKeys::CorpoBasicSoldier)
      )
    );

    tiledSceneCreator::create(
      "level-0",
      *m_assetManager,
      tiledClassApplierMapper,
      m_sceneGraph
    );

    tiledSceneCreator::create(
      "ui",
      *m_assetManager,
      tiledClassApplierMapper,
      m_uiSceneGraph
    );

    createPathfinders();
  }

  void MainScene::createPathfinders()
  {
    SharedPtr<TiledMap> tiledMap = m_assetManager->getAssetGroup<TiledMap>()
      .get("level-0");
    SharedPtr<Pathfinder> pathfinder = pathfinderFactory::createFromIsometricTiledMap(
      *tiledMap
    );

    m_pathfinderManager->addPathfinder("characters", pathfinder);

    m_pathfinderCollisionMaskUpdater = MakeUnique<PathfinderCollisionMaskUpdater>(
      pathfinder,
      m_physicsWorld,
      "plantas",
      tiledMapUtilities::getPositionTransformer(*tiledMap)
    );
  }
}