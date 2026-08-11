#if !defined(SSTL_HELPERS_H)
#define SSTL_HELPERS_H

// SECTION(saeb): Non-copyable / non-movable helpers.
#define SSTL_NON_COPYABLE(Type) \
    Type(const Type&) = delete; \
    Type& operator=(const Type&) = delete

#define SSTL_NON_MOVABLE(Type) \
    Type(Type&&) = delete; \
    Type& operator=(Type&&) = delete

#endif
