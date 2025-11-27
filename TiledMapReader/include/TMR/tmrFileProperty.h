#pragma once

#include "TMR/tmrProperty.h"

namespace tmr
{
  class TMR_API FileProperty : public Property 
  {
  public:
    FileProperty(const char* name, const char* value);
    virtual ~FileProperty();

    const char* getValue() const { return m_value; }

  private:
    char* m_value;
  };
}