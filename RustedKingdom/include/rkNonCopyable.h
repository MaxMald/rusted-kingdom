#pragma once

namespace rk
{
  class NonCopyable
  {
  protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) noexcept = delete;
    NonCopyable& operator=(NonCopyable&&) noexcept = delete;
  };
}