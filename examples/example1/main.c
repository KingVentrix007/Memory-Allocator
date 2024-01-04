#include <stdio.h>
#include <stdlib.h>
#include "../../lowlevel/mem.h"
void process_user_input() {
    // Prompt user for input
    printf("Enter the size of the array: ");
    int size;
    scanf("%d", &size);

    // Dynamically allocate memory for an integer array
    int* dynamicArray = (int*)sys_allocate_memory(size * sizeof(int));
    printf("Memory allocated at address: %p\n", (void*)dynamicArray);
    // Check if memory allocation was successful
    if (dynamicArray == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        return;
    }

    // Initialize array elements
    for (int i = 0; i < size; ++i) {
        dynamicArray[i] = i * 2;  // Perform some operation (you can modify this)
    }

    // Display the results
    printf("Dynamic Array elements: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", dynamicArray[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    dynamicArray = sys_free_memory((void *)dynamicArray);
    if(dynamicArray != NULL)
    {
        printf("ERROR: Failed to free dynamic\n");
    }
}

// Example usage in a main function
int main() {
    void *region = malloc(1024*1024*1024);
    mem_main(region,1024*1024*1024);
    process_user_input();
    free(region);
    return 0;
}
