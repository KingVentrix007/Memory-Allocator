#include "internal.h"
#include <stddef.h>
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
int internal_memcmp(const void* s1, const void* s2, size_t n) {
    const unsigned char* p1 = s1;
    const unsigned char* p2 = s2;

    while (n-- > 0) {
        if (*p1 != *p2) {
            return (*p1 - *p2);
        }
        p1++;
        p2++;
    }

    return 0; // Memory areas are equal
}
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
void* internal_memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = dest;
    const unsigned char* s = src;
    while (n-- > 0) {
        *d++ = *s++;
    }
    return dest;
}
/**
 * Function Name: internal_memset
 * Description: Custom implementation of memset.
 *
 * Parameters:
 *   s (void*) - Pointer to the memory to set.
 *   c (int) - Value to set. Should be an unsigned char cast to int.
 *   n (size_t) - Number of bytes to set.
 *
 * Return:
 *   (void*) - Pointer to the memory area s.
 */

void* internal_memset(void* s, int c, size_t n) {
    unsigned char* p = (unsigned char *)s;
    while (n-- > 0) {
        *p++ = (unsigned char)c;
    }
    return s;
}