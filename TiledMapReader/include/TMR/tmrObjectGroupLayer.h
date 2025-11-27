#pragma once

#include "TMR/tmrLayer.h"

namespace tmr
{
  class ObjectGroup;

  class TMR_API ObjectGroupLayer : public Layer
  {
  public:
    ObjectGroupLayer(
      const int32_t& id,
      const char* name,
      Properties* properties,
      ObjectGroup* objectGroup
    );
    virtual ~ObjectGroupLayer();

    /**
     * @brief Gets the ObjectGroup associated with this layer.
     * @return Pointer to the ObjectGroup.
     */
    const ObjectGroup* getObjectGroup() const { return m_objectGroup; }

  private:
    ObjectGroup* m_objectGroup;
  };
}