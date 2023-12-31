#include "mem.h"
#include "extra.h"


int memcpy_m(void *dst, const void *src, size_t size)
{
    int dst_size = get_memory_size(dst);
    if(dst_size < size)
    {
        MEM_ALLOC_LOG("Size of destination buffer is smaller than size");
        return -1;
    }
    else if(dst_size == -1)
    {
        MEM_ALLOC_LOG("Destination buffer is not allocated. Please use a C99 compliant memcpy() instead");
    }
    return 0;
}