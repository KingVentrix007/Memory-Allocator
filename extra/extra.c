#include "mem.h"
#include "extra.h"


int memcpy_m(void *dst, const void *src, size_t size)
{
    size_t dst_size = get_memory_size(dst);
    if(dst_size < size && dst_size != -1)
    {
        MEM_ALLOC_LOG("Size of destination buffer is smaller than size, Resizing buffer");
        dst = sys_reallocate_memory(dst, dst_size,size);
        
    }
    // else if(dst_size == -1)
    // {
    //     MEM_ALLOC_LOG("Destination buffer is not allocated. Please use a C99 compliant memcpy() instead");
    //     return -2;
    // }
    char* dest_ptr = (char*)dst;
        const char* src_ptr = (const char*)src;

        // Copy each byte from source to destination
        for (size_t i = 0; i < n; ++i) {
            dest_ptr[i] = src_ptr[i];
    }
    return 0;
}