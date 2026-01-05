#include "rkButtonClassApplier.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <TMR/tmrObject.h>

#include "rkGameObject.h"
#include "rkTiledPropertiesHandler.h"

#include "scripts/rkButtonScript.h"

using sf::IntRect;
using sf::Vector2i;

namespace rk
{
  ButtonClassApplier::ButtonClassApplier()
  {
  }

  ButtonClassApplier::~ButtonClassApplier()
  {
  }

  void ButtonClassApplier::apply(
    GameObject& gameObject,
    const tmr::Object* object,
    const tmr::TiledMap* tiledMap
  )
  {
    BaseTiledClassApplier::apply(gameObject, object, tiledMap);
    TiledPropertiesHandler propertiesHandler(object->getProperties());

    Int32 normalIndex = 0;
    Int32 hoveredIndex = 0;
    Int32 pressedIndex = 0;
    Int32 buttonHeight = 0;
    Int32 buttonWidth = 0;
    Int32 spriteSheetColumns = 0;

    if (
      !propertiesHandler.tryGetInt("buttonWidth", buttonWidth) ||
      !propertiesHandler.tryGetInt("buttonHeight", buttonHeight) ||
      !propertiesHandler.tryGetInt("spriteSheetColumns", spriteSheetColumns) ||
      !propertiesHandler.tryGetInt("normalIndex", normalIndex) ||
      !propertiesHandler.tryGetInt("hoveredIndex", hoveredIndex) ||
      !propertiesHandler.tryGetInt("pressedIndex", pressedIndex)
      )
    {
      // TODO Warning message
      return;
    }

    Vector2i buttonSize = Vector2i(buttonWidth, buttonHeight);
    UniquePtr<ButtonScript> buttonScript = MakeUnique<ButtonScript>(gameObject);

    buttonScript->prepare(
      IntRect(
        Vector2i(
          (normalIndex % spriteSheetColumns) * buttonWidth,
          (normalIndex / spriteSheetColumns) * buttonHeight
        ),
        buttonSize
      ),
      IntRect(
        Vector2i(
          (hoveredIndex % spriteSheetColumns) * buttonWidth,
          (hoveredIndex / spriteSheetColumns) * buttonHeight
        ),
        buttonSize
      ),
      IntRect(
        Vector2i(
          (pressedIndex % spriteSheetColumns) * buttonWidth,
          (pressedIndex / spriteSheetColumns) * buttonHeight
        ),
        buttonSize
      )
    );

    gameObject.addComponent(std::move(buttonScript));
  }
}