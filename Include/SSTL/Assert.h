#if !defined(SSTL_ASSERT_H)
#define SSTL_ASSERT_H

#include "Config.h"
#include "Types.h"

#if !defined(SSTL_DEFAULT_ASSERT_HANDLER)
    #define SSTL_DEFAULT_ASSERT_HANDLER 1
#endif

#if SSTL_DEFAULT_ASSERT_HANDLER
    #include <cstdio>
    #include <cstdlib>
#endif

#if SSTL_PLATFORM_WINDOWS && SSTL_DEFAULT_ASSERT_HANDLER
    extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent(void);
    extern "C" __declspec(dllimport) void __stdcall DebugBreak(void);
#endif

namespace sstl
{
    using AssertHandler = void(*)(const char* expression, const char* file, int32 line, const char* message);

#if SSTL_DEFAULT_ASSERT_HANDLER
    inline void DefaultAssertHandler(const char* expression, const char* file, int32 line, const char* message)
    {
        std::fprintf(stderr, "SSTL: Assertion failed:\n    Expression: %s.\n    At: %s:%d.\n", expression, file, line);

        if(message != nullptr)
        {
            std::fprintf(stderr, "    Message: %s.\n", message);
        }

#if SSTL_PLATFORM_WINDOWS
        if(IsDebuggerPresent())
        {
            DebugBreak();
        }
#endif

        std::abort();
    }

    inline AssertHandler g_AssertHandler = &DefaultAssertHandler;
#else
    inline AssertHandler g_AssertHandler = nullptr;
#endif
}

#if SSTL_DEBUG
#define SSTL_ASSERT_MSG(expression, message) \
    do \
    { \
        if (!(expression)) \
        { \
            sstl::g_AssertHandler(#expression, __FILE__, __LINE__, (message)); \
        } \
    } while (0)
#else
    #define SSTL_ASSERT_MSG(expression, message) ((void)sizeof(!(expression)), (void)sizeof(message))
#endif

#define SSTL_ASSERT(expression) SSTL_ASSERT_MSG(expression, nullptr)
#define SSTL_ASSERT_STATIC_MSG(expression, message) static_assert(expression, message)
#define SSTL_ASSERT_STATIC(expression) static_assert(expression)

// NOTE(saeb): Unconditional failure.
#define SSTL_FAIL_MSG(message) (sstl::g_AssertHandler("SSTL_FAIL", __FILE__, __LINE__, (message)))

#endif
