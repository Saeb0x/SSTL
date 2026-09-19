#if !defined(SSTL_UTILITY_H)
#define SSTL_UTILITY_H

#define SSTL_ARRAYCOUNT(array) (sizeof(array) / sizeof((array)[0]))

#define SSTL_KIB(count) (((count) * 1024ULL))
#define SSTL_MIB(count) (((count) * 1024ULL * 1024ULL))
#define SSTL_GIB(count) (((count) * 1024ULL * 1024ULL * 1024ULL))

#endif
