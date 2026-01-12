#include "rkUnitsSelectionControllerGameObjectComponentDrawer.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "rkGameObject.h"

#include "scripts/rkUnitsSelectionController.h"

namespace rk
{
  UnitsSelectionControllerGameObjectComponentDrawer::
    UnitsSelectionControllerGameObjectComponentDrawer() :
    AGameObjectComponentDrawer("Units Selection Controller")
  {
  }

  UnitsSelectionControllerGameObjectComponentDrawer::
    ~UnitsSelectionControllerGameObjectComponentDrawer()
  {
  }

  void UnitsSelectionControllerGameObjectComponentDrawer::onDraw(
    Component& component,
    sf::RenderWindow& window
  )
  {
    UnitsSelectionController& unitsSelectionController =
      static_cast<UnitsSelectionController&>(component);
    
    const Vector<GameObject*>& selectedUnits =
      unitsSelectionController.getCurrentlySelectedUnits();

    ImGui::Text("Currently Selected Units: %d", static_cast<int>(selectedUnits.size()));
    for (size_t i = 0; i < selectedUnits.size(); ++i)
    {
      String gameObjectName = selectedUnits[i]->getName();
      if (gameObjectName.empty())
        gameObjectName = "<unnamed>";

      gameObjectName = String::Format(
        "%s (%p)",
        gameObjectName.c_str(),
        &selectedUnits[i]
      );

      ImGui::BulletText("Unit %d: %s",
        static_cast<Int32>(i),
        gameObjectName.c_str()
      );
    }
  }
}