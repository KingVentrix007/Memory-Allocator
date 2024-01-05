/**
 * @file mem_manager.c
 * @brief This file contains the implementation of memory management functions.
 * @author KingVentrix007
 * @date 05-01-2024
 * @copyright Tristan Kuhn
 */

#include "mem.h"
#include "mem_output.h"
#include "mem_config.h"

/**
 * @brief Finds a free zone of memory to allocate.
 * @param current_node The current node to start searching from.
 * @param size The size of memory to allocate.
 * @return A pointer to the start of the allocated memory.
 */
void *find_free_zone(Node *current_node, size_t size,int num_blocks_needed)
{
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
    return NULL;
}