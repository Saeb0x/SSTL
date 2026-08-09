#if !defined(SSTL_TYPES_H)
#define SSTL_TYPES_H

#include <cstdint>
#include <cstddef>

namespace sstl
{
    using int8 = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;

    using uint8 = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;

    using real32 = float;
    using real64 = double;

    using bool8 = uint8;
    using bool32 = uint32;

    using byte = uint8;
    using handle = uint32;

    using usize = std::size_t;
    using isize = std::ptrdiff_t;
}

#endif
