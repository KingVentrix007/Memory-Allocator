#include "test.h"
#include "mem.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "string.h"
int run_memory_allocator_test_suite()
{
    // Test Case 1: Allocate memory
    printf("\nATTENTION: These Test Cases can run automatically. However, it is advised to check the printed ouput for additional information\n");
    printf("Test Case 1: Allocate memory\n");
    void *ptr1 = sys_allocate_memory(4096);
    void *ptr2 = sys_allocate_memory(2048);
    void *ptr3 = sys_allocate_memory(8192);
    if(ptr1 == NULL)
    {
        printf("Test 1 failed\n");
        return -1;
    }
    if(ptr2 == NULL)
    {
        printf("Test 1 failed\n");
        return -1;
    }
    if(ptr3 == NULL)
    {
        printf("Test 1 failed\n");
        return -1;
    }
    // print_memory_info();
    printf("\n");

    // Test Case 2: Store values in allocated memory
    printf("Test Case 2: Store values in allocated memory\n");

    int *int_ptr = (int *)ptr1;
    for (int i = 0; i < 1024; ++i) {
        int_ptr[i] = i * 2;
    }
    int *values = (int *)ptr1;
    for (int i = 0; i < 1024; ++i) {
        printf("%d",values[i]);
    }

    // print_memory_info();
    printf("\n");

    // Test Case 3: Free memory
    printf("Test Case 3: Free memory\n");
    sys_free_memory(ptr2);
    // print_memory_info();
    printf("\n");

    // Test Case 4: Reallocate memory
    printf("Test Case 4: Reallocate memory\n");
    char *text = "hello world";
    strcpy(ptr1,text);
    void *ptr4 = sys_reallocate_memory(ptr1, 4096, 8192);
    if(strcmp(ptr4, text) != 0 || ptr4 == NULL)
    {
        printf("Test Case 4: Reallocate memory failed");
        return -4;

    }
    printf("%s\n",ptr4);
    
    // print_memory_info();
    printf("\n");

    // Test Case 5: Error handling - Invalid parameters for reallocation
    printf("Test Case 5: Error handling - Invalid parameters for reallocation\n");
    void *invalid_ptr = sys_reallocate_memory(NULL, 0, 8192);
    if (invalid_ptr == NULL) {
        printf("Invalid parameters handled successfully\n");
        
    }
    else
    {
        printf("Test Case 5: Error Handling - Invalid parameters for reallocation failed\n");
        return - 5;
    }
    printf("\n");

    // Test Case 6: Error handling - Reallocate to smaller or equal size
    printf("Test Case 6: Error handling - Reallocate to smaller or equal size\n");
    void *ptr5 = sys_reallocate_memory(ptr4, 8192, 4096);
    if (ptr5 == ptr4) {
        printf("No reallocation performed, as the new size is smaller or equal to the old size\n");
    }
    else
    {
        printf("Test Case 6: Error handling - Reallocate to smaller or equal size\n");
        return -6;
    }
    // print_memory_info();
    printf("\n");

    // Test Case 7: Get size of memory  allocated memory
    printf("Test Case 7: Get size of allocated memory\n");
    void * ptr7 = sys_allocate_memory(1028);
    if(ptr7 == NULL)
    {
        printf("Failed to allocate memory for test case 7\n");
        return -7;
    }else
    {
        size_t size = get_memory_size(ptr7);
        if(size != 1028)
        {
            printf("\nTest case 7 failed to get correct memory size\n");
            return -7;
        }
        else if (size == 1028)
        {
            printf("Test case 7 completed successfully\n");
        }
        
    }

    // Test Case 8: Free all remaining allocated memory
    printf("Test Case 8: Free all remaining allocated memory\n");
    sys_free_memory(ptr1);
    sys_free_memory(ptr3);
    sys_free_memory(ptr4);
    return 0;
    // print_memory_info();

}

