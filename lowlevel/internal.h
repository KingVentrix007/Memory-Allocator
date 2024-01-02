#ifndef __INTERNAL__MEMORY_ALLOATION__H
#define __INTERNAL__MEMORY_ALLOATION__H
#include <stddef.h>
/**
 * Function Name: internal_memset
 * Description: Sets the first n bytes of the memory area pointed to by s to the specified value.
 *
 * Parameters:
 *   s (void*) - Pointer to the memory area.
 *   c (int)   - Value to be set.
 *   n (size_t) - Number of bytes to be set.
 *
 * Return:
 *   (void*) - Pointer to the memory area s.
 */
void* internal_memset(void* s, int c, size_t n);
/**
 * Function Name: internal_memcpy
 * Description: Copies n bytes from memory area src to memory area dest.
 *
 * Parameters:
 *   dest (void*) - Pointer to the destination memory area.
 *   src  (const void*) - Pointer to the source memory area.
 *   n    (size_t) - Number of bytes to be copied.
 *
 * Return:
 *   (void*) - Pointer to the destination memory area dest.
 */
void* internal_memcpy(void* dest, const void* src, size_t n);
/**
 * Function Name: internal_memcmp
 * Description: Compares the first n bytes of memory areas s1 and s2.
 *
 * Parameters:
 *   s1 (const void*) - Pointer to the first memory area.
 *   s2 (const void*) - Pointer to the second memory area.
 *   n  (size_t)      - Number of bytes to be compared.
 *
 * Return:
 *   (int) - 0 if the memory areas are equal, < 0 if s1 is less than s2, > 0 if s1 is greater than s2.
 */
int internal_memcmp(const void* s1, const void* s2, size_t n);

#endif