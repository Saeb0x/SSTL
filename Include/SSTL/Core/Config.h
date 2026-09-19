#if !defined(SSTL_CONFIG_H)
#define SSTL_CONFIG_H

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

#if defined(SSTL_DEBUG) && !defined(SSTL_RELEASE)
    #define SSTL_RELEASE (!(SSTL_DEBUG))
#elif defined(SSTL_RELEASE) && !defined(SSTL_DEBUG)
    #define SSTL_DEBUG (!(SSTL_RELEASE))
#elif !defined(SSTL_DEBUG) && !defined(SSTL_RELEASE)
    #if defined(_DEBUG) || defined(DEBUG)
        #define SSTL_DEBUG 1
        #define SSTL_RELEASE 0
    #else
        #define SSTL_DEBUG 0
        #define SSTL_RELEASE 1
    #endif
#endif

#if (SSTL_DEBUG + SSTL_RELEASE) != 1
    #error "SSTL: Exactly one of SSTL_DEBUG / SSTL_RELEASE must be 1."
#endif

#if !defined(SSTL_EXCEPTIONS_ENABLED)
    #if defined(_CPPUNWIND) || defined(__EXCEPTIONS) || defined(__cpp_exceptions)
        #define SSTL_EXCEPTIONS_ENABLED 1
    #else
        #define SSTL_EXCEPTIONS_ENABLED 0
    #endif
#endif

#endif
