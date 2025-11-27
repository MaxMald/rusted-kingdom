#pragma once

#include "TMR/tmrProperty.h"

namespace tmr
{
  class TMR_API StringProperty : public Property 
  {
  public:
    StringProperty(const char* name, const char* value);
    virtual ~StringProperty();

    const char* getValue() const { return m_value; }

  private:
    char* m_value;
  };
}