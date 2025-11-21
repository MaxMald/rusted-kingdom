#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  namespace pathUtilities
  {
    /**
     * @brief Combines two file paths into one.
     *
     * @param path1 The first file path.
     * @param path2 The second file path.
     *
     * @return A newly allocated string containing the combined file path.
     * Returned pointer must be freed when no longer needed.
     */
    char* combinePaths(const char* path1, const char* path2);
  }
}