#pragma once
#pragma once

/*#ifdef DOE_PLATFORM_WINDOWS
#ifdef DOE_BUILD_DLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif
#else
#error Hazel only supports windows!
#endif*/ 

#ifdef DOE_ENABLE_ASSERTS
#define DOE_ASSERT(x, ...) {if(!(x)) { HZ_ERROR("Asserttion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define DOE_ASSERT(x, ...) {if(!(x)) { HZ_CORE_ERROR("Asserttion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else
#define DOE_ASSERT(x, ...)
#define DOE_CORE_ASSERT(x, ...)

#endif 


#define DOE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)