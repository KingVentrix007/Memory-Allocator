// memory_manager.h
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H
#include "stdbool.h"
#include "stddef.h"
typedef struct Node {
    void* addr;           // Starting address of the memory region represented by the node
    size_t size;           // Size of the memory region represented by the node
    struct Node* next;     // Pointer to the next node in the linked list
    bool allocated;        // Boolean flag indicating whether this region is currently allocated
    bool first_block;      // Boolean flag indicating if this is the first block in the memory region
    size_t num_block_used; // Number of blocks used (will be 0 if first_block is false)
} Node;


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
void sys_free_memory(void *addr);

void print_memory_info();
void extend_allocation_space(void *extra_region,size_t size);
void *init_memory_region(void *start_addr,size_t size);
#endif // MEMORY_MANAGER_H