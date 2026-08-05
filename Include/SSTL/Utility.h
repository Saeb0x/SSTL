#if !defined(SSTL_UTILITY_H)
#define SSTL_UTILITY_H

#include "Types.h"

namespace sstl
{
    template <typename T, uint64 N>
    constexpr uint64 ArrayCount(const T (&)[N]) noexcept
    {
        return N;
    }
}

#endif
