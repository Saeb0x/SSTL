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

// SECTION(saeb): Non-copyable / non-movable helpers.
#define SSTL_NON_COPYABLE(Type) \
    Type(const Type&) = delete; \
    Type& operator=(const Type&) = delete

#define SSTL_NON_MOVABLE(Type) \
    Type(Type&&) = delete; \
    Type& operator=(Type&&) = delete

#endif
