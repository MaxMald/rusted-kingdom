#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class ITiledClassApplier;

  class TiledClassApplierMapper : public NonCopyable
  {
  public:
    TiledClassApplierMapper();
    ~TiledClassApplierMapper();

    bool hasClassApplier(const String& className) const;
    SharedPtr<ITiledClassApplier> getClassApplier(const String& className) const;

    void registerClassApplier(
      const String& className,
      SharedPtr<ITiledClassApplier> classApplier
    );

  private:
    UnorderedMap<String, SharedPtr<ITiledClassApplier>> m_classAppliers;
  };
}