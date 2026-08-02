#if !defined(SSTL_CONFIG_H)
#define SSTL_CONFIG_H

#include "Types.h"

#include <cstdio>
#include <cstdlib>

// SECTION(saeb): Compiler detection.
#define SSTL_COMPILER_MSVC 0
#define SSTL_COMPILER_CLANG 0
#define SSTL_COMPILER_GNU 0

#if defined(_MSC_VER)
    #undef SSTL_COMPILER_MSVC
    #define SSTL_COMPILER_MSVC 1
#elif defined(__clang__)
    #undef SSTL_COMPILER_CLANG
    #define SSTL_COMPILER_CLANG 1
#elif defined(__GNUC__)
    #undef SSTL_COMPILER_GNU
    #define SSTL_COMPILER_GNU 1
#endif

// SECTION(saeb): Platform detection.
#define SSTL_PLATFORM_WINDOWS 0
#define SSTL_PLATFORM_LINUX 0
#define SSTL_PLATFORM_APPLE 0

#if defined(_WIN32) || defined(_WIN64)
    #undef SSTL_PLATFORM_WINDOWS
    #define SSTL_PLATFORM_WINDOWS 1
#elif defined(__linux__)
    #undef SSTL_PLATFORM_LINUX
    #define SSTL_PLATFORM_LINUX 1
#elif defined(__APPLE__)
    #undef SSTL_PLATFORM_APPLE
    #define SSTL_PLATFORM_APPLE 1
#endif

// SECTION(saeb): Debug/Release detection.
#if !defined(SSTL_DEBUG) && !defined(SSTL_RELEASE)
    #if defined(_DEBUG) || defined(DEBUG)
        #define SSTL_DEBUG 1
        #define SSTL_RELEASE 0
    #else
        #define SSTL_RELEASE 1
        #define SSTL_DEBUG 0
    #endif
#endif

// SECTION(saeb): Assertion.
#if SSTL_PLATFORM_WINDOWS
    extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent(void);
    extern "C" __declspec(dllimport) void __stdcall DebugBreak(void);
#endif

namespace SSTL
{
    using AssertHandler = void(*)(const char* expression, const char* file, int32 line, const char* message);

    inline void DefaultAssertHandler(const char* expression, const char* file, int32 line, const char* message)
    {
        std::fprintf(stderr, "SSTL assertion failed:\n    Expression: %s\n    At: %s:%d\n", expression, file, line);

        if(message != nullptr)
        {
            std::fprintf(stderr, "    Message: %s\n", message);
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
}

#if SSTL_DEBUG
#define SSTL_ASSERT_MSG(expression, message) \
    do \
    { \
        if (!(expression)) \
        { \
            SSTL::g_AssertHandler(#expression, __FILE__, __LINE__, (message)); \
        } \
    } while (0)
#else
    #define SSTL_ASSERT_MSG(expression, message) ((void)0)
#endif

#define SSTL_FAIL_MSG(message) (SSTL::g_AssertHandler("SSTL_FAIL", __FILE__, __LINE__, (message)))

#define SSTL_ASSERT(expression) SSTL_ASSERT_MSG(expression, nullptr)

// SECTION(saeb): Exception handling.
#if !defined(SSTL_EXCEPTIONS_ENABLED)
    #if defined(_CPPUNWIND) || defined(__EXCEPTIONS) || defined(__cpp_exceptions)
        #define SSTL_EXCEPTIONS_ENABLED 1
    #else
        #define SSTL_EXCEPTIONS_ENABLED 0
    #endif
#endif

#if SSTL_EXCEPTIONS_ENABLED
    #define SSTL_THROW(exception) throw exception
#else
    #define SSTL_THROW(exception) (SSTL_FAIL_MSG(#exception), std::abort())
#endif

// SECTION(saeb): Non-copyable / non-movable helpers.
#define SSTL_NON_COPYABLE(Type) \
    Type(const Type&) = delete; \
    Type& operator=(const Type&) = delete

#define SSTL_NON_MOVABLE(Type) \
    Type(Type&&) = delete; \
    Type& operator=(Type&&) = delete

// NOTE(saeb): Force-inline and likely/unlikely hints will be added later.

#endif
