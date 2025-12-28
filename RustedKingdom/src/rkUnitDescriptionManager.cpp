#include "rkUnitDescriptionManager.h"
#include "rkServiceLocator.h"
#include "rkAssetManager.h"
#include "rkJson.h"

namespace rk
{
  UnitDescriptionManager::UnitDescriptionManager()
  {
  }

  UnitDescriptionManager::~UnitDescriptionManager()
  {
  }

  const UnitDescription& UnitDescriptionManager::getUnitDescription(
    const String& unitName
  ) const
  {
    auto it = m_unitDescriptions.find(unitName);
    if (it != m_unitDescriptions.end()) {
      return it->second;
    }

    throw RuntimeErrorException("Unit description not found: " + unitName);
  }

  void UnitDescriptionManager::addUnitDescription(
    const UnitDescription& unitDescription
  )
  {
    m_unitDescriptions[unitDescription.getName()] = unitDescription;
  }

  void UnitDescriptionManager::init(ServiceLocator& serviceLocator)
  {
    loadUnitDescriptions(serviceLocator.getService<AssetManager>());
  }

  void UnitDescriptionManager::destroy()
  {
    m_unitDescriptions.clear();
  }

  void UnitDescriptionManager::loadUnitDescriptions(
    SharedPtr<AssetManager> assetManager
  )
  {
    Json json = Json::loadFromFile(
      assetManager->combineAssetDirectoryWithPath(
        Path("configs/unit-descriptions.json")
      )
    );

    Json units = json["units"];
    if (units.isNull() || !units.isArray()) {
      throw LogicErrorException(
        "Invalid unit descriptions format: 'units' key missing or not an array."
      );
    }

    SizeT unitCount = units.getSize();
    for (Int32 i = 0; i < unitCount; ++i) {
      Json unitJson = units[i];

      UnitDescription unitDescription;
      unitDescription.setName(unitJson["name"].getString());
      unitDescription.setDisplayName(unitJson["displayName"].getString());
      unitDescription.setVelocity(unitJson["velocity"].getFloat());
      unitDescription.setHealth(static_cast<UInt16>(unitJson["health"].getInt32()));
      unitDescription.setArmor(static_cast<UInt16>(unitJson["armor"].getInt32()));

      addUnitDescription(unitDescription);
    }
  }
}