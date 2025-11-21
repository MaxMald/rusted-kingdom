#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
  /**
   * @brief Prevents copy construction and copy assignment for derived classes.
   *
   * Inherit from NonCopyable to make a class non-copyable.
   */
  class TMR_API NonCopyable
  {
  protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

    NonCopyable(NonCopyable&&) = delete;
    NonCopyable& operator=(NonCopyable&&) = delete;
  };
}
