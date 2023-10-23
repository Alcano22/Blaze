#pragma once

#include <memory>

#ifdef BLZ_DEBUG
#   ifndef BLZ_ENABLE_ASSERTS
#       define BLZ_ENABLE_ASSERTS
#   endif
#endif

#ifdef BLZ_ENABLE_ASSERTS
#   define BLZ_CORE_ASSERT(x, ...) { if (!(x)) { BLZ_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#   define BLZ_ASSERT(x, ...) { if (!(x)) { BLZ_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#   define BLZ_CORE_ASSERT(x, ...)
#   define BLZ_ASSERT(x, ...)
#endif

#define GLSTR_TO_CSTR(x) reinterpret_cast<const char*>(x)

#define BIT(x) (1 << (x))

#define BLZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)