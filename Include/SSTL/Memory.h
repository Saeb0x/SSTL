#if !defined(SSTL_MEMORY_H)
#define SSTL_MEMORY_H

#include "Types.h"
#include "Assert.h"

namespace sstl
{
    constexpr uint64 Kilobytes = 1024;
    constexpr uint64 Megabytes = Kilobytes * 1024;
    constexpr uint64 Gigabytes = Megabytes * 1024;

    struct Arena
    {
        uint8* Base;
        uint64 Size;
        uint64 Used;
    };

    inline void InitializeArena(Arena* arena, void* base, uint64 size)
    {
        arena->Base = static_cast<uint8*>(base);
        arena->Size = size;
        arena->Used = 0;
    }

    inline void* PushSize(Arena* arena, uint64 size, uint64 alignment)
    {
        SSTL_ASSERT((alignment & (alignment - 1)) == 0); // Power of two

        uint64 currentAddress = reinterpret_cast<uint64>(arena->Base + arena->Used);
        uint64 alignmentMask = alignment - 1;
        uint64 alignmentOffset = 0;
        if(currentAddress & alignmentMask)
        {
            alignmentOffset = alignment - (currentAddress & alignmentMask);
        }

        SSTL_ASSERT(arena->Used + alignmentOffset + size <= arena->Size);

        void* result = arena->Base + arena->Used + alignmentOffset;
        arena->Used += alignmentOffset + size;

        return result;
    }

    template <typename T>
    inline T* PushStruct(Arena* arena)
    {
        return static_cast<T*>(PushSize(arena, sizeof(T), alignof(T)));
    }

    template <typename T>
    inline T* PushArray(Arena* arena, uint64 count)
    {
        return static_cast<T*>(PushSize(arena, sizeof(T) * count, alignof(T)));
    }

    struct ScratchMemory
    {
        Arena* Owner;
        uint64 Used;
    };

    inline ScratchMemory BeginScratchMemory(Arena* arena)
    {
        ScratchMemory result;
        result.Owner = arena;
        result.Used = arena->Used;
        return result;
    }

    inline void EndScratchMemory(ScratchMemory scratchMemory)
    {
        SSTL_ASSERT(scratchMemory.Owner->Used >= scratchMemory.Used);
        scratchMemory.Owner->Used = scratchMemory.Used;
    }
}

#endif
