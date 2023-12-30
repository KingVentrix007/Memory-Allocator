#include "mem.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "string.h"
// #define TEST_CASE_MEMORY_ALLOC
// #define MEMORY_ALLOCATION_LOGGING

void *memory_region = NULL;
void *end_of_node_region = NULL;
void *memory_region_end = NULL;


int main()
{
    // Allocate initial memory
    memory_region = malloc(1024 * 1024 * 1024);
    init_memory_allocation(memory_region, 1024 * 1024 * 1024);

    // Run the memory allocator test suite
    #ifdef TEST_CASE_MEMORY_ALLOC
       int ret =  run_memory_allocator_test_suite();
       if(ret != 0)
       {
            printf("Test Cases Failed: Test Case %d\n", (ret*-1));
       }
       else
       {
        printf("Test Cases Successful");
       }
       #endif
    // #endif
    // Free the initial allocated memory
    free(memory_region);

    return 0;
}

void print_node_info(Node *node)
{
    MEM_ALLOC_LOG("  Address: %p\n", node->addr);
    MEM_ALLOC_LOG("  Size: %zu\n", node->size);
    MEM_ALLOC_LOG("  Allocated: %s\n", node->allocated ? "true" : "false");
    MEM_ALLOC_LOG("  First Block: %s\n", node->first_block ? "true" : "false");
    MEM_ALLOC_LOG("  Num Blocks Used: %zu\n", node->num_block_used);
    MEM_ALLOC_LOG("\n");
}

void init_memory_allocation(void *start_addr, int size)
{
    init_memory_region(start_addr, size);
    // memory_allocations = (MemoryAllocationInfo *)sys_allocate_memory(sizeof(MemoryAllocationInfo) * 10);
    // Now nodes are initialized, and the available memory is divided accordingly
}
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
void *sys_allocate_memory(int size)
{
    // Calculate the number of blocks needed
    if(size > (memory_region_end - memory_region))
    {
        MEM_ALLOC_LOG("error");
        return NULL;
    }
    int num_blocks_needed = (size + 1023) / 1024; // Round up to the nearest whole block
    // MemoryAllocationInfo info;
    // info.size = size;
    // info.allocated_size = num_blocks_needed*1024;
    MEM_ALLOC_LOG("Allocating %d blocks of memory\n", num_blocks_needed);

    // Find a consecutive bunch of free nodes
    Node *current_node = (Node *)memory_region;
    current_node = current_node->next;

    while (current_node != NULL)
    {
        if (!current_node->allocated)
        {
            int consecutive_free_blocks = 0;
            Node *start_node = current_node;
            start_node->total_requested_memory = size;
            // Check for consecutive free blocks
            while (current_node != NULL && !current_node->allocated && consecutive_free_blocks < num_blocks_needed)
            {
                ++consecutive_free_blocks;
                current_node = current_node->next;
            }

            // If enough consecutive free blocks are found, allocate them
            if (consecutive_free_blocks >= num_blocks_needed)
            {
                // Mark the nodes as allocated
                current_node = start_node;
                for (int i = 0; i < num_blocks_needed; ++i)
                {
                    current_node->allocated = true;
                    current_node->first_block = (i == 0);
                    current_node->num_block_used = num_blocks_needed;
                    current_node = current_node->next;
                }

                MEM_ALLOC_LOG("Allocated %d bytes of memory\n", size);
                // info.ptr = start_node->addr;
                
            //    memory_allocations[num_memory_allocations] = info;
            // num_memory_allocations++;
                return start_node->addr;
            }
        }

        // Move to the next node
        current_node = current_node->next;
    }

    MEM_ALLOC_LOG("Failed to allocate %d bytes of memory\n", size);
    return NULL;
}

/**
 * Function Name: sys_free_memory
 * Description: Frees memory blocks starting from the specified address and updates the linked list.
 *              Also removes the corresponding block from the memory_allocations list and sorts it.
 *
 * Parameters:
 *   addr (void*) - The address of the memory to free.
 *
 * Return:
 *   void
 */
void sys_free_memory(void *addr)
{
    Node *current_node = (Node *)memory_region;

    // Find the node corresponding to the given address
    while (current_node != NULL && current_node->addr != addr)
    {
        current_node = current_node->next;
    }

    // If the node is found, free the memory blocks
    if (current_node != NULL && current_node->allocated)
    {
        int num_blocks_to_free = current_node->num_block_used;

        // Mark the nodes as free
        for (int i = 0; i < num_blocks_to_free; ++i)
        {
            current_node->allocated = false;
            current_node->first_block = false;
            current_node->num_block_used = 0;
            current_node->total_requested_memory = 0;
            current_node = current_node->next;
            
        }

        // // Remove the corresponding MemoryAllocationInfo from the list
        // for (size_t i = 0; i < num_memory_allocations; ++i)
        // {
        //     if (memory_allocations[i].ptr == addr)
        //     {
        //         // Remove the MemoryAllocationInfo by shifting the remaining elements
        //         for (size_t j = i; j < num_memory_allocations - 1; ++j)
        //         {
        //             memory_allocations[j] = memory_allocations[j + 1];
        //         }

        //         // Decrement the count of memory allocations
        //         num_memory_allocations--;

        //         // Sort the memory_allocations based on allocated size in ascending order
        //         for (size_t k = 0; k < num_memory_allocations - 1; ++k)
        //         {
        //             for (size_t l = 0; l < num_memory_allocations - k - 1; ++l)
        //             {
        //                 if (memory_allocations[l].allocated_size > memory_allocations[l + 1].allocated_size)
        //                 {
        //                     // Swap the MemoryAllocationInfo structures
        //                     MemoryAllocationInfo temp = memory_allocations[l];
        //                     memory_allocations[l] = memory_allocations[l + 1];
        //                     memory_allocations[l + 1] = temp;
        //                 }
        //             }
        //         }

        //         // Print or log the deallocated memory information
        //         MEM_ALLOC_LOG("Freed memory starting from address %p\n", addr);
        //         MEM_ALLOC_LOG("Sorted Memory Allocation List:\n");
        //         for (size_t m = 0; m < num_memory_allocations; ++m)
        //         {
        //             MEM_ALLOC_LOG("  Size: %d, Allocated Size: %d, Pointer: %p\n", 
        //                     memory_allocations[m].size, 
        //                     memory_allocations[m].allocated_size, 
        //                     memory_allocations[m].ptr);
        //         }

        //         return;
        //     }
        // }
    }
    else
    {
        MEM_ALLOC_LOG("Invalid address or memory is not allocated\n");
    }
}


/**
 * Function Name: sys_reallocate_memory
 * Description: Reallocates memory for a previously allocated block and updates the linked list.
 * !! WARNING !!: This function deallocates the addr value.
 *
 * Parameters:
 *   addr (void*) - The address of the memory block to reallocate.
 *   old_size (int) - The current size of the memory block in bytes.
 *   new_size (int) - The new size to which the memory block should be reallocated.
 *
 * Return:
 *   void* - The new address of the reallocated memory block.
 */
void *sys_reallocate_memory(void *addr, int old_size, int new_size)
{
    // Check for invalid parameters
    if (old_size >= new_size)
    {
        MEM_ALLOC_LOG("Reallocation of memory unnecessary as the old size exceeds the new size\n");
        return addr;
    }
    else if (addr == NULL)
    {
        MEM_ALLOC_LOG("Address is NULL\n");
        return NULL;
    }
    else if (addr < memory_region || addr > memory_region_end)
    {
        MEM_ALLOC_LOG("Address out of range\n");
        return NULL;
    }

    // Allocate new memory
    void *new_addr = sys_allocate_memory(new_size);

    // Check if the allocation was successful
    if (new_addr != NULL)
    {
        // Copy data from the old memory to the new memory
        memcpy(new_addr, addr, old_size);

        // Free the old memory
        sys_free_memory(addr);

        return new_addr;
    }
    else
    {
        MEM_ALLOC_LOG("Failed to reallocate memory. Returning original address.\n");
        return addr;
    }
}
/** 
 * Function Name: print_memory_info 
 * Description: Prints information about the memory. 
 * 
 * !! WARNING !! 
 * None. 
 * 
 * Parameters: 
 *   print_option (int) - Determines the printing option. 
 * 
 * Return: 
 *   None. 
 */
void print_memory_info(int print_option)
{
    Node *current_node = (Node *)memory_region;

    MEM_ALLOC_LOG("Memory Information:\n");

    size_t free_space = 0;
    while (current_node != NULL)
    {
            MEM_ALLOC_LOG("  Address: %p\n", current_node->addr);
            MEM_ALLOC_LOG("  Size: %zu\n", current_node->size);
            MEM_ALLOC_LOG("  Allocated: %s\n", current_node->allocated ? "true" : "false");
            MEM_ALLOC_LOG("  First Block: %s\n", current_node->first_block ? "true" : "false");
            MEM_ALLOC_LOG("  Num Blocks Used: %zu\n", current_node->num_block_used);
            MEM_ALLOC_LOG("\n");
            
            if(current_node->allocated == true)
            {
                MEM_ALLOC_LOG("\n----------------------------------------------------------------\n");
                MEM_ALLOC_LOG("Free space : %d\n", free_space);
                free_space = free_space;
                
            }
            else
            {
                free_space = free_space +current_node->size;
            }
            current_node =  current_node->next;
    }
}

/**
 * Function Name: init_memory_region
 * Description: Initializes the memory region for allocation.
 *
 * !! WARNING !!
 * None.
 *
 * Parameters:
 *   start_addr (void*) - Starting address of the memory region.
 *   size (size_t) - Size of the memory region.
 *
 * Return:
 *   void* - End address of the node region.
 */
void *init_memory_region(void *start_addr,size_t size)
{
     // Calculate the number of nodes based on the size of each node
    int num_nodes = size / 1024;
    memory_region_end = memory_region+size;
    // Calculate the size needed for the nodes
    int bytes_used_by_nodes = num_nodes * sizeof(Node);
    
    // Calculate the size available for actual allocation
    int bytes_available_for_allocation = size - bytes_used_by_nodes;

    MEM_ALLOC_LOG("%d nodes \n", num_nodes);
    MEM_ALLOC_LOG("%d bytes are taken up by the nodes in memory\n", bytes_used_by_nodes);
    MEM_ALLOC_LOG("%d bytes are available for actual allocation\n", bytes_available_for_allocation);

    // Cast the start address to Node pointer
    Node *node1 = (Node *)memory_region;

    // Calculate the end of the node region
     end_of_node_region = (void *)((char *)start_addr + bytes_used_by_nodes);;

    // Calculate the start of the allocation region
    void *start_of_allocation_region = end_of_node_region;

    // Initialize the first node (buffer node)
    // node1->addr = start_of_allocation_region;
    // node1->size = 1024;
    // node1->next = (Node *)((char *)start_addr + sizeof(Node));
    // node1->allocated = true;
    // node1->first_block = true;
    node1->num_block_used = node1->num_block_used + num_nodes;

    // Initialize the rest of the nodes
    Node *current_node = (Node *)start_addr;

    for (int i = 1; i < num_nodes; ++i)
    {
        if(start_of_allocation_region + i * 1024 > start_addr+size)
        {
            node1->num_block_used = i;
            MEM_ALLOC_LOG("Bytes avlible = %ld\n", node1->num_block_used *1024);
            // sleep(5);
            break;
        }
        current_node->addr = start_of_allocation_region + i * 1024;
        current_node->size = 1024;
        current_node->next = (i < num_nodes - 1) ? (Node *)((char *)current_node + sizeof(Node)) : NULL;
        current_node->allocated = false;
        current_node->first_block = false;
        current_node->num_block_used = 0;

        ++current_node;
    }
    
    return end_of_node_region;
}

/**
 * Function Name: extend_allocation_space
 * Description: Extends the allocation space by initializing new nodes in the extra region.
 * !! WARNING !!
 * The function is currently broken and needs fixing.
 *
 * Parameters:
 *   extra_region (void*) - Pointer to the extra region for extending the allocation space.
 *   size (size_t) - Size of the extra region.
 *
 * Return:
 *   None.
 */
void extend_allocation_space(void *extra_region, size_t size)
{
    //! CURRENTLY BROKEN
    Node *last_node = (Node *)memory_region;

    // Find the last node in the existing list
    while (last_node->next != NULL)
    {
        last_node = last_node->next;
    }

    // Initialize the new nodes in the extended allocation space
    void *end_of_extended_node_region = init_memory_region(extra_region, size);

    // Update the next pointer of the last node to point to the first new node
    last_node->next = (Node *)extra_region;

    // Update the end_of_node_region to the end of the extended node region
    end_of_node_region = end_of_extended_node_region;
}

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
size_t get_memory_size(void *ptr)
{
    Node *current_node = (Node *)memory_region;
    int run_size = current_node->num_block_used;
    for (size_t i = 0; i < run_size; i++)

    
    {
        if(current_node->addr == ptr && current_node->allocated == true)
        {
            return current_node->total_requested_memory;
        }
        current_node = current_node->next;
    }
    MEM_ALLOC_LOG("Failed to find Allocated memory region at %p",ptr);
    return -1;
}