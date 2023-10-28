#pragma once

#include <memory>

#ifdef BLZ_DEBUG
#   ifndef BLZ_ENABLE_ASSERTS
#       define BLZ_ENABLE_ASSERTS
#   endif
#endif

#define GLSTR_TO_CSTR(x) reinterpret_cast<const char*>(x)

#define BIT(x) (1 << (x))

#define BLZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)