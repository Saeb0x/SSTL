#if !defined(SSTL_TYPES_H)
#define SSTL_TYPES_H

#include <climits>
#include <cstddef>
#include <cstdint>

static_assert(CHAR_BIT == 8, "SSTL requires 8-bit bytes.");

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

    using char8 = char;
    using char16 = char16_t;
    using char32 = char32_t;

    using cstring8 = const char8*;
    using cstring16 = const char16*;
    using cstring32 = const char32*;

    using byte = uint8;
    using handle = uint32;

    using usize = std::size_t;
    using isize = std::ptrdiff_t;
}

#endif
