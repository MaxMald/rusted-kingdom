#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  namespace assertions
  {
    /**
     * @brief Asserts that the provided pointer is not null.
     * 
     * @param ptr Pointer to check.
     * @param message Message to include in the assertion failure.
     */
    template <typename T>
    void assertNotNull(const T* ptr, const String& valueName)
    {
      if (!ptr)
      {
        throw RuntimeErrorException(
          String::Format(
            "Assertion failed: %s pointer is null.",
            valueName.c_str()
          )
        );
      }
    }

    /**
     * @brief Asserts that index is within bounds [0, size).
     *
     * Uses the phrase "out of bounds" which is the common and clear terminology.
     *
     * @param index Index to check.
     * @param size Size (upper bound, exclusive).
     * @param valueName Name of the value for the message.
     */
    template <typename T>
    void assertIndexInRange(const T& index, const T& size, const String& valueName)
    {
      if (index < 0 || index >= size)
      {
        if (size == 0)
        {
          throw RuntimeErrorException(
            String::Format(
              "Assertion failed: %s index %zu is out of bounds (no valid indices: size == 0).",
              valueName.c_str(),
              static_cast<size_t>(index)
            )
          );
        }

        throw RuntimeErrorException(
          String::Format(
            "Assertion failed: %s index %zu is out of bounds (valid range: 0..%zu).",
            valueName.c_str(),
            static_cast<size_t>(index),
            static_cast<size_t>(size - 1)
          )
        );
      }
    }
  } // namespace assertions
}