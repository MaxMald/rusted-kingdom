#include "TMR/tmrObjectGroupLayer.h"
#include "TMR/tmrObjectGroup.h"

namespace tmr
{
  ObjectGroupLayer::ObjectGroupLayer(
    const int32_t& id,
    const char* name,
    Properties* properties,
    ObjectGroup* objectGroup
  ) :
    Layer(id, name, properties, layerType::ObjectGroup),
    m_objectGroup(objectGroup)
  {
  }

  ObjectGroupLayer::~ObjectGroupLayer()
  {
    if (m_objectGroup)
    {
      delete m_objectGroup;
      m_objectGroup = nullptr;
    }
  }
}