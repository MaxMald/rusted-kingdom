#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrOrientation.h"

namespace tmr
{
  namespace orientationParser
  {
    /**
     * @brief Parse orientation type from string.
     * @param orientationStr C-style string representing the orientation.
     * @return Parsed orientation type.
     */
    orientation::Type parseFromString(const char* orientationStr);
  } 
}