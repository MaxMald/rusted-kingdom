#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrNonCopyable.h"
#include "TMR/tmrLayerType.h"

namespace tmr
{
  class Properties;

  class TMR_API Layer : public NonCopyable
  {
  public:
    Layer(
      const int32_t& id,
      const char* name,
      Properties* properties,
      layerType::Type type
    );
    virtual ~Layer();

    const int32_t& getId() const { return m_id; }
    const char* getName() const { return m_name; }
    const Properties* getProperties() const { return m_properties; }
    layerType::Type getType() const { return m_type; }

  private:
    int32_t m_id;
    layerType::Type m_type;
    char* m_name;
    Properties* m_properties;
  };
}