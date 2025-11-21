#pragma once

#define _CRT_SECURE_NO_WARNINGS

#if defined(_WIN32) || defined(_WIN64)
#if defined(TMR_STATIC)
#define TMR_API
#else
#if defined(TMR_EXPORTS)
#define TMR_API __declspec(dllexport)
#else
#define TMR_API __declspec(dllimport)
#endif
#endif
#endif

#include <cstddef>
#include <cstdint>

using std::size_t;
using std::uint32_t;
using std::int32_t;