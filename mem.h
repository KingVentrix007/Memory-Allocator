// memory_manager.h
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H
#include "stdbool.h"
#include "stddef.h"
// #define MEMORY_ALLOCATION_VERBOSE_OUTPUT
typedef struct Node {
    void* addr;           // Starting address of the memory region represented by the node
    size_t size;           // Size of the memory region represented by the node
    struct Node* next;     // Pointer to the next node in the linked list
    bool allocated;        // Boolean flag indicating whether this region is currently allocated
    bool first_block;      // Boolean flag indicating if this is the first block in the memory region
    size_t num_block_used; // Number of blocks used (will be 0 if first_block is false)
    size_t total_requested_memory; // Total requested memory for this block of list, not rounded to the nearest 1024
} Node;

typedef struct
{
    int size; //Size of the allocation in bytes, The exact Number of bytes
    int allocated_size; //Size of the allocated memory region in bytes, devisable by 1024(or size specfied by Node->size)
    void *ptr; // Pointer to the allocated memory region
}MemoryAllocationInfo;
void init_memory_allocation(void * start_addr, int size);
void print_node_info(Node *node);

/**
 * Function Name: sys_allocate_memory
 * Description: Allocates a consecutive bunch of memory blocks and updates the linked list.
 *
 * Parameters:
 *   size (int) - The size of memory to allocate in bytes.
 *
 * Return:
 *   void
 */
void *sys_allocate_memory(int size);

/**
 * Function Name: sys_free_memory
 * Description: Frees memory blocks starting from the specified address and updates the linked list.
 *
 * Parameters:
 *   addr (void*) - The address of the memory to free.
 *
 * Return:
 *   void
 */
void sys_free_memory(const void *addr);
/**
 * Function Name: sys_reallocate_memory
 * Description: Reallocates memory for a previously allocated block and updates the linked list.
 *
 * Parameters:
 *   addr (void*) - The address of the memory block to reallocate.
 *   old_size (int) - The current size of the memory block in bytes.
 *   new_size (int) - The new size to which the memory block should be reallocated.
 *
 * Return:
 *   void* - The new address of the reallocated memory block.
 */
void *sys_reallocate_memory(void *addr, int old_size, int new_size);
void print_memory_info();
void extend_allocation_space(void *extra_region,size_t size);
void *init_memory_region(void *start_addr,size_t size);


/** 
 * Function Name: get_memory_size 
 * Description: Retrieves the size of the allocated memory block pointed to by ptr. 
 * 
 * !! WARNING !! 
 * None. 
 * 
 * Parameters: 
 *   ptr (void*) - Pointer to the memory block. 
 * 
 * Return: 
 *   size_t - The size of the allocated memory block. 
 */
size_t get_memory_size(void *ptr);
#ifdef MEMORY_ALLOCATION_VERBOSE_OUTPUT
#define MEM_ALLOC_LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define MEM_ALLOC_LOG(fmt, ...) do { } while (0)
#endif

#endif // MEMORY_MANAGER_H