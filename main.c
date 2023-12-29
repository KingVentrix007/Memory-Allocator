#include "mem.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"
void *memory_region = NULL;
void *end_of_node_region = NULL;
int main(int argc, char const *argv[])
{
    // Allocate initial memory
    memory_region = malloc(1024 * 1024 * 1024);
    init_memory_region(memory_region, 1024 * 1024 * 1024);

    // Allocate some memory using your custom function
    void *ptr1 = sys_allocate_memory(4096);
    void *ptr2 = sys_allocate_memory(2048);
    void *ptr3 = sys_allocate_memory(8192);

    // Print information about each node
    // print_memory_info();

    // Free memory using your custom function
    sys_free_memory(ptr2);

    // Print information after freeing memory
    // print_memory_info();

    // Allocate extra memory
    void *new_region = malloc(1024 * 1024);
    // extend_allocation_space(new_region, 1024 * 1024);

    // Print information after extending memory
    print_memory_info();

    // Free the remaining allocated memory
    sys_free_memory(ptr1);
    sys_free_memory(ptr3);

    // Print final memory information
    // print_memory_info();

    return 0;
}

void print_node_info(Node *node)
{
    printf("  Address: %p\n", node->addr);
    printf("  Size: %zu\n", node->size);
    printf("  Allocated: %s\n", node->allocated ? "true" : "false");
    printf("  First Block: %s\n", node->first_block ? "true" : "false");
    printf("  Num Blocks Used: %zu\n", node->num_block_used);
    printf("\n");
}

void init_memory_allocation(void *start_addr, int size)
{
    // Calculate the number of nodes based on the size of each node
    int num_nodes = size / 1024;
    
    // Calculate the size needed for the nodes
    int bytes_used_by_nodes = num_nodes * sizeof(Node);

    // Calculate the size available for actual allocation
    int bytes_available_for_allocation = size - bytes_used_by_nodes;

    printf("%d nodes \n", num_nodes);
    printf("%d bytes are taken up by the nodes in memory\n", bytes_used_by_nodes);
    printf("%d bytes are available for actual allocation\n", bytes_available_for_allocation);

    // Cast the start address to Node pointer
    Node *node1 = (Node *)start_addr;

    // Calculate the end of the node region
    end_of_node_region = (void *)((char *)start_addr + bytes_used_by_nodes);

    // Calculate the start of the allocation region
    void *start_of_allocation_region = end_of_node_region;

    // Initialize the first node (buffer node)
    node1->addr = start_of_allocation_region;
    node1->size = 1024;
    node1->next = (Node *)((char *)start_addr + sizeof(Node));
    node1->allocated = true;
    node1->first_block = true;
    node1->num_block_used = num_nodes - 1;

    // Initialize the rest of the nodes
    Node *current_node = node1->next;

    for (int i = 1; i < num_nodes; ++i)
    {
        if(start_of_allocation_region + i * 1024 > start_addr+size)
        {
            node1->num_block_used = i;
            printf("Bytes avlible = %d\n", node1->num_block_used *1024);
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
    int num_blocks_needed = (size + 1023) / 1024; // Round up to the nearest whole block

    printf("Allocating %d blocks of memory\n", num_blocks_needed);

    // Find a consecutive bunch of free nodes
    Node *current_node = (Node *)memory_region;
    current_node = current_node->next;

    while (current_node != NULL)
    {
        if (!current_node->allocated)
        {
            int consecutive_free_blocks = 0;
            Node *start_node = current_node;

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

                printf("Allocated %d bytes of memory\n", size);
                return start_node->addr;
            }
        }

        // Move to the next node
        current_node = current_node->next;
    }

    printf("Failed to allocate %d bytes of memory\n", size);
    return NULL;
}


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
            current_node = current_node->next;
        }

        printf("Freed memory starting from address %p\n", addr);
    }
    else
    {
        printf("Invalid address or memory is not allocated\n");
    }
}

void print_memory_info()
{
    Node *current_node = (Node *)memory_region;

    printf("Memory Information:\n");
    while (current_node != NULL)
    {
        printf("  Address: %p\n", current_node->addr);
        printf("  Size: %zu\n", current_node->size);
        printf("  Allocated: %s\n", current_node->allocated ? "true" : "false");
        printf("  First Block: %s\n", current_node->first_block ? "true" : "false");
        printf("  Num Blocks Used: %zu\n", current_node->num_block_used);
        printf("\n");
        sleep(0.5);
        current_node = current_node->next;
    }
}

void *init_memory_region(void *start_addr,size_t size)
{
     // Calculate the number of nodes based on the size of each node
    int num_nodes = size / 1024;
    
    // Calculate the size needed for the nodes
    int bytes_used_by_nodes = num_nodes * sizeof(Node);
    
    // Calculate the size available for actual allocation
    int bytes_available_for_allocation = size - bytes_used_by_nodes;

    printf("%d nodes \n", num_nodes);
    printf("%d bytes are taken up by the nodes in memory\n", bytes_used_by_nodes);
    printf("%d bytes are available for actual allocation\n", bytes_available_for_allocation);

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
            printf("Bytes avlible = %d\n", node1->num_block_used *1024);
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
void extend_allocation_space(void *extra_region, size_t size)
{
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