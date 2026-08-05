#if !defined(SSTL_EXCEPTION_H)
#define SSTL_EXCEPTION_H

#include "Assert.h"

#if !SSTL_EXCEPTIONS_ENABLED
    #include <cstdlib>
#endif

#if SSTL_EXCEPTIONS_ENABLED
    #define SSTL_THROW(exception) throw exception
#else
    #define SSTL_THROW(exception) (SSTL_FAIL_MSG(#exception), std::abort())
#endif

#endif
