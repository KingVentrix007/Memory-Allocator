#include "pmm.h"
#include "mem.h"
#include "internal.h"
void *pmm_node_region_end = NULL;
void *pmm_memory_region_end = NULL;
void *pmm_memory_region = NULL;

// int start()
// {
//     pmm_memory_region = malloc(1234);
// }
int init_pmm(void * start_adder,size_t size)
{
    // Calculate the number of nodes based on the size of each node
    pmm_memory_region = start_adder;
    size_t num_nodes = size / PMM_BLOCK_SIZE_BYTES;
    pmm_memory_region_end = pmm_memory_region + size;

    // Calculate the size needed for the nodes
    size_t bytes_used_by_nodes = num_nodes * sizeof(Node);

    // Ensure proper alignment for the start of the allocation region
    size_t alignment_padding = (ALIGNMENT - ((size_t)start_adder % ALIGNMENT)) % ALIGNMENT;
    void *aligned_start_addr = (char *)start_adder + alignment_padding;

    // Calculate the size available for actual allocation
    size_t bytes_available_for_allocation = size - bytes_used_by_nodes - alignment_padding;

    MEM_ALLOC_LOG(2, "%d nodes \n", num_nodes);
    MEM_ALLOC_LOG(2, "%d bytes are taken up by the nodes in memory\n", bytes_used_by_nodes);
    MEM_ALLOC_LOG(2, "%d bytes are available for actual allocation\n", bytes_available_for_allocation);

    // Cast the start address to Node pointer
    Node *node1 = (Node *)pmm_memory_region;

    // Calculate the end of the node region
    pmm_node_region_end = (void *)((char *)aligned_start_addr + bytes_used_by_nodes);

    // Calculate the start of the allocation region
    void *start_of_allocation_region = pmm_node_region_end;

    node1->num_block_used = node1->num_block_used + num_nodes;

    // Initialize the rest of the nodes
    Node *current_node = (Node *)aligned_start_addr;
    for (int i = 1; i < num_nodes; ++i) {
        if (start_of_allocation_region + i * PMM_BLOCK_SIZE_BYTES > aligned_start_addr + bytes_available_for_allocation) {
            node1->num_block_used = i;
            MEM_ALLOC_LOG(2, "Bytes available = %ld\n", node1->num_block_used * PMM_BLOCK_SIZE_BYTES);
            break;
        }
        current_node->addr = start_of_allocation_region + i * PMM_BLOCK_SIZE_BYTES;
        current_node->size = PMM_BLOCK_SIZE_BYTES;
        current_node->next = (i < num_nodes - 1) ? (Node *)((char *)current_node + sizeof(Node)) : NULL;
        current_node->allocated = false;
        current_node->first_block = false;
        current_node->num_block_used = 0;
        ++current_node;
    }

  



}

// size must alway be a multiple of PMM_BLOCK_SIZE_BYTES
void *allocate_pmm_block(int size)
{
    if(size < PMM_BLOCK_SIZE_BYTES*2)
    {
         MEM_ALLOC_LOG(0, "Allocated Region Too Small");
            
        return NULL;
    }
      if (size > (pmm_memory_region_end - pmm_memory_region))
    {
        MEM_ALLOC_LOG(0, "Size is too large");
        return NULL;
    }
    int num_blocks_needed = (size + 1023) / PMM_BLOCK_SIZE_BYTES; // Round up to the nearest whole block

    MEM_ALLOC_LOG(2, "Allocating %d blocks of memory\n", num_blocks_needed);

    // Find a consecutive bunch of free nodes
    Node *current_node = (Node *)pmm_memory_region;
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

                MEM_ALLOC_LOG(2, "Allocated %d bytes of memory\n", size);
                return start_node->addr;
            }
        }

        // Move to the next node
        if (current_node != NULL && current_node->next != NULL)
        {
            current_node = current_node->next;
        }
    }

    MEM_ALLOC_LOG(0, "Failed to allocate %d bytes of memory\n", size);
    return NULL;
    
}

void *pmm_free_block(const void *addr)
{
   
    Node *current_node = (Node *)pmm_memory_region;

    // Find the node corresponding to the given address
    while (current_node != NULL && current_node->addr != addr)
    {
        current_node = current_node->next;
    }

    // FreeZone freezone;
    // if (current_node != NULL && current_node->addr != NULL)
    // {
    //     freezone.start_ptr = current_node->addr;
    // }
    // freezone.size = get_memory_size(addr);

    // If the node is found, free the memory blocks
    if (current_node != NULL && current_node->allocated)
    {
        size_t num_blocks_to_free = current_node->num_block_used;

        // Mark the nodes as free
        for (int i = 0; i < num_blocks_to_free; ++i)
        {
            current_node->allocated = false;
            current_node->first_block = false;
            current_node->num_block_used = 0;
            current_node->total_requested_memory = 0;
            current_node = current_node->next;
        }

        // Return NULL after freeing
        memset(addr, 0, get_memory_size(addr));
        // freezone.end_ptr = current_node->addr;
        // free_zones[free_zone_count] = freezone;
        // free_zone_count++;

        return NULL;
    }
    else
    {
        MEM_ALLOC_LOG(0, "Invalid address or memory is not allocated 0x%p\n", addr);

        // Return the original address if not found or not allocated
        return (void *)addr;
    }
}

