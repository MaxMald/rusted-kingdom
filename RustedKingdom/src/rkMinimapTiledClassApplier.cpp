#include "rkMinimapTiledClassApplier.h"

#include <SFML/Graphics/Color.hpp>
#include <TMR/tmrObject.h>
#include <TMR/tmrProperties.h>

#include "rkGameObject.h"
#include "rkTiledPropertiesHandler.h"
#include "scripts/rkMinimapScript.h"

namespace rk
{
  MinimapTiledClassApplier::MinimapTiledClassApplier()
  {
  }

  MinimapTiledClassApplier::~MinimapTiledClassApplier()
  {
  }

  void MinimapTiledClassApplier::apply(
    GameObject& gameObject,
    const tmr::Object* tmrObject,
    const tmr::TiledMap* tmrTiledMap
  )
  {
    BaseTiledClassApplier::apply(gameObject, tmrObject, tmrTiledMap);

    TiledPropertiesHandler properties(tmrObject->getProperties());

    float viewBoxThickness = 1.f;
    properties.tryGetFloat("viewBoxThickness", viewBoxThickness);

    sf::Color viewBoxColor = sf::Color::Red;
    properties.tryGetColor("viewBoxColor", viewBoxColor);

    UniquePtr<MinimapScript> minimapScript = MakeUnique<MinimapScript>(gameObject);
    minimapScript->setViewBoxThickness(viewBoxThickness);
    minimapScript->setViewBoxColor(viewBoxColor);

    gameObject.addComponent(std::move(minimapScript));

  }
}