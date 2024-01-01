#ifndef __HIGHLEVEL_ALLOCATION_CODE__H
#define __HIGHLEVEL_ALLOCATION_CODE__H
/**
 * Function Name: kmalloc
 * Description: Allocates memory using sys_allocate_memory function.
 *
 * Parameters:
 *   size (size_t) - The size of memory to allocate in bytes.
 *
 * Return:
 *   void* - A pointer to the allocated memory.
 */
void *kmalloc(size_t size)
{
    return sys_allocate_memory(size);
}

/**
 * Function Name: kfree
 * Description: Frees memory using sys_free_memory function.
 *
 * Parameters:
 *   ptr (void*) - A pointer to the memory to free.
 *
 * Return:
 *   void
 */
void kfree(void *ptr)
{
    sys_free_memory(ptr);
}

/**
 * Function Name: krealloc
 * Description: Reallocates memory using sys_reallocate_memory function.
 *
 * Parameters:
 *   ptr (void*) - A pointer to the memory block to reallocate.
 *   old_size (size_t) - The current size of the memory block in bytes.
 *   new_size (size_t) - The new size to which the memory block should be reallocated.
 *
 * Return:
 *   void* - A pointer to the reallocated memory block.
 */
void *krealloc(void *ptr, size_t old_size, size_t new_size)
{
    return sys_reallocate_memory(ptr, old_size, new_size);
}
#endif