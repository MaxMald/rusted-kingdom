#pragma once

#include <cstdint>
#include <cstddef>
#include <unordered_map>
#include <memory>
#include <vector>

namespace rk
{
  using Int8 = std::int8_t;
  using Int16 = std::int16_t;
  using Int32 = std::int32_t;
  using Int64 = std::int64_t;
  using UInt8 = std::uint8_t;
  using UInt16 = std::uint16_t;
  using UInt32 = std::uint32_t;
  using UInt64 = std::uint64_t;
  using Byte = UInt8;

  using Bool = bool;
  using SizeT = std::size_t;

  template<typename K, typename V>
  using UnorderedMap = std::unordered_map<K,V>;

  template<typename T>
  using UniquePtr = std::unique_ptr<T>;

  template<typename T>
  using Vector = std::vector<T>;
}