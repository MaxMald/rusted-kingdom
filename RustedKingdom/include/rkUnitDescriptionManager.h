#pragma once

#include "rkIService.h"
#include "rkUnitDescription.h"

namespace rk
{
  class AssetManager;

  class UnitDescriptionManager : public IService
  {
  public:
    UnitDescriptionManager();
    virtual ~UnitDescriptionManager();

    const UnitDescription& getUnitDescription(const String& unitName) const;
    void addUnitDescription(const UnitDescription& unitDescription);

  protected:
    void init(ServiceLocator& serviceLocator) override;
    void destroy() override;

  private:
    UnorderedMap<String, UnitDescription> m_unitDescriptions;

    void loadUnitDescriptions(SharedPtr<AssetManager> assetManager);
  };
}