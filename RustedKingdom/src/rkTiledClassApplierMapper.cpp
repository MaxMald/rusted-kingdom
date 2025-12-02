#include "rkTiledClassApplierMapper.h"

namespace rk
{
  TiledClassApplierMapper::TiledClassApplierMapper()
  {
  }

  TiledClassApplierMapper::~TiledClassApplierMapper()
  {
  }

  bool TiledClassApplierMapper::hasClassApplier(const String& className) const
  {
    return m_classAppliers.find(className) != m_classAppliers.end();
  }

  SharedPtr<ITiledClassApplier> TiledClassApplierMapper::getClassApplier(
    const String& className
  ) const
  {
    auto it = m_classAppliers.find(className);
    if (it != m_classAppliers.end())
      return it->second;

    return nullptr;
  }

  void TiledClassApplierMapper::registerClassApplier(
    const String& className,
    SharedPtr<ITiledClassApplier> classApplier
  )
  {
    m_classAppliers[className] = classApplier;
  }
}