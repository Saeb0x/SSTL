#if !defined(SSTL_STACKALLOCATOR_H)
#define SSTL_STACKALLOCATOR_H

#include "SSTL/Core/Config.h"
#include "SSTL/Core/Types.h"

#define SSTL_ALIGNUP(address, alignmentBytes) ((((usize)(address)) + (alignmentBytes) - 1) & (~((alignmentBytes) - 1)))

struct StackAllocator
{
    uint8* MemoryBlock;
    uint8* Base;
    uint8* Cap;
    uint8* LowerHeap;
    uint8* UpperHeap;
};

enum class Heap : uint8
{
    Lower = 0,
    Upper
};

struct Frame
{
    uint8* Mark;
    Heap Heap;
};

bool InitStackAllocator(StackAllocator* allocator, usize size);
void ShutdownStackAllocator(StackAllocator* allocator);

#if SSTL_PLATFORM_WINDOWS
    #include "Platform/Windows/Win32StackAllocator.h"
#else
    #error "SSTL: Unsupported platform for StackAllocator."
#endif

inline void* Allocate(StackAllocator* allocator, Heap heap, usize size, uint8 alignment)
{
    if(!allocator || size == 0 || alignment == 0)
    {
        return nullptr;
    }

    // Validate alignment is power of two.
    if((alignment & (alignment - 1)) != 0)
    {
        return nullptr;
    }

    void* startingAddress;
    if(heap == Heap::Upper)
    {
        // From upper heap (down).
        usize aligned = SSTL_ALIGNUP((usize)(allocator->UpperHeap - size), alignment);

        if(aligned < (usize)allocator->LowerHeap)
        {
            return nullptr; // Out of memory or collision
        }

        allocator->UpperHeap = (uint8*)aligned;
        startingAddress = (void*)aligned;
    }
    else
    {
        // From lower heap (up).
        usize aligned = SSTL_ALIGNUP((usize)allocator->LowerHeap, alignment);

        if(aligned + size > (usize)allocator->UpperHeap)
        {
            return nullptr; // Out of memory or collision
        }

        allocator->LowerHeap = (uint8*)(aligned + size);
        startingAddress = (void*)aligned;
    }

    return startingAddress;
}

inline usize GetAvailableMemory(StackAllocator* allocator)
{
    if(!allocator)
    {
        return 0;
    }

    return allocator->UpperHeap - allocator->LowerHeap;
}

inline usize GetUsedMemory(StackAllocator* allocator)
{
    if(!allocator)
    {
        return 0;
    }

    return (allocator->LowerHeap - allocator->Base) + (allocator->Cap - allocator->UpperHeap);
}

inline Frame GetFrame(StackAllocator* allocator, Heap heap)
{
    Frame frame;
    frame.Mark = (heap == Heap::Upper) ? allocator->UpperHeap : allocator->LowerHeap;
    frame.Heap = heap;

    return frame;
}

inline void ReleaseFrame(StackAllocator* allocator, Frame frame)
{
    if(frame.Heap == Heap::Upper)
    {
        allocator->UpperHeap = frame.Mark;
    }
    else
    {
        allocator->LowerHeap = frame.Mark;
    }
}

#endif
