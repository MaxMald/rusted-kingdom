#include "rkTiledLayerGameObjectCreator.h"

#include <TMR/tmrTiledMap.h>
#include <TMR/tmrLayer.h>
#include <TMR/tmrProperties.h>

#include "rkGameObject.h"
#include "rkSceneGraph.h"
#include "rkIsometricLayerGameObject.h"
#include "rkTiledPropertiesHandler.h"

namespace rk
{
  namespace tiledLayerGameObjectCreator
  {
    GameObject* create(
      const tmr::TiledMap* tiledMap,
      const tmr::Layer* layer,
      SceneGraph& sceneGraph
    )
    {
      if (!tiledMap)
        throw RuntimeErrorException("TiledMap pointer is null.");

      tmr::orientation::Type mapOrientation = tiledMap->getOrientation();
      if (mapOrientation == tmr::orientation::Type::Isometric)
      {
        return createForIsometricMap(layer, sceneGraph);
      }
      else if (mapOrientation == tmr::orientation::Type::Orthogonal)
      {
        return createForOrthogonalMap(layer, sceneGraph);
      }

      throw RuntimeErrorException("Not implemented map orientation.");
    }

    GameObject* createForOrthogonalMap(
      const tmr::Layer* layer,
      SceneGraph& sceneGraph
    )
    {
      if (!layer)
        throw RuntimeErrorException("Layer pointer is null.");

      UniquePtr<GameObject> layerGameObject = MakeUnique<GameObject>(layer->getName());
      GameObject* rawLayerGameObject = layerGameObject.get();

      sceneGraph.registerGameObject(std::move(layerGameObject));

      return rawLayerGameObject;
    }

    GameObject* createForIsometricMap(
      const tmr::Layer* layer,
      SceneGraph& sceneGraph
    )
    {
      if (!layer)
        throw RuntimeErrorException("Layer pointer is null.");

      UniquePtr<IsometricLayerGameObject> layerGameObject
        = MakeUnique<IsometricLayerGameObject>(layer->getName());
      IsometricLayerGameObject* rawLayerGameObject = layerGameObject.get();

      TiledPropertiesHandler propertiesHandler(layer->getProperties());

      bool isStatic = false;
      propertiesHandler.tryGetBool("isStatic", isStatic);
      layerGameObject->setStaticLayer(isStatic);

      sceneGraph.registerGameObject(std::move(layerGameObject));

      return rawLayerGameObject;
    }
  }
}