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

namespace Blaze
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}