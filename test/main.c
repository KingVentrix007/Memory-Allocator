/**
 * @file main.c
 * @brief Unit tests for memory allocation and management functions.
 * @details This file contains unit tests for functions related to memory allocation,
 *          deallocation, reallocation, and memory size retrieval.
 * @author KingVentrix007
 * @date 02/01/2024
 * @version 1.0
 */

#include "unity.h"
#include "../lowlevel/mem.h"
#include "string.h"

/**   
 * @brief Set up function called before each test function.
 */
void setUp(void) {
    
    main_automated_testing();
}

/**
 * @brief Tear down function called after each test function.
 */
void tearDown(void) {
    main_automated_testing_end();
}

/**
 * @brief Tests the allocation of memory using sys_allocate_memory function.
 */
void test_allocate_memory() {
    void const *ptr1 = sys_allocate_memory(4096);
    void const *ptr2 = sys_allocate_memory(2048);
    void const *ptr3 = sys_allocate_memory(8192);
    TEST_ASSERT_NOT_NULL(ptr1);
    TEST_ASSERT_NOT_NULL(ptr2);
    TEST_ASSERT_NOT_NULL(ptr3);
    sys_free_memory(ptr1);
    sys_free_memory(ptr2);
    sys_free_memory(ptr3);
}

/**
 * @brief Tests storing values in the allocated memory.
 */
void test_store_values() { 
    void *ptr1 = sys_allocate_memory(4096);
    char *string = (char *)ptr1;
    const char *StartText = "Test Case 2: Store values in allocated memory";
    strcpy(string, StartText);
    char const *EndText = (char *)ptr1;
    TEST_ASSERT_EQUAL_STRING(EndText,StartText);
    sys_free_memory(ptr1);
}

/**
 * @brief Tests freeing allocated memory.
 */
void test_free_memory() {
    const void *ptr2 = sys_allocate_memory(2048);
    
    ptr2 = sys_free_memory(ptr2);
    
    TEST_ASSERT_NULL(ptr2);
}

/**
 * @brief Tests reallocating memory using sys_reallocate_memory function.
 */
void test_reallocate_memory() {
    void *ptr1 = sys_allocate_memory(4096);
    char const *text = "hello world";
    strcpy(ptr1, text);
    void const *ptr4 = sys_reallocate_memory(ptr1, 4096, 8192);
    TEST_ASSERT_EQUAL_STRING(text, ptr4);
    TEST_ASSERT_NOT_NULL(ptr4);
    sys_free_memory(ptr4);
    TEST_ASSERT_NOT_NULL(ptr4);
}

/**
 * @brief Tests error handling for invalid parameters in reallocating memory.
 */
void test_invalid_reallocation() {
    const void *invalid_ptr = sys_reallocate_memory(NULL, 0, 8192);
    TEST_ASSERT_NULL(invalid_ptr);
}

/**
 * @brief Tests error handling for reallocating to smaller or equal size.
 */
void test_reallocate_smaller_size() {
    void *ptr4 = sys_allocate_memory(8192);
    void *ptr5 = sys_reallocate_memory(ptr4, 8192, 4096);
    TEST_ASSERT_EQUAL_PTR(ptr4, ptr5);
}

/**
 * @brief Tests getting the size of allocated memory.
 */
void test_get_memory_size() {
    const void *ptr7 = sys_allocate_memory(1028);
    TEST_ASSERT_NOT_NULL(ptr7);
    size_t size = get_memory_size(ptr7);
    TEST_ASSERT_EQUAL_INT(1028, size);
}

/**
 * @brief Tests freeing all remaining allocated memory.
 */
void test_free_all_memory() {
    //Simple test case for freeing all memory. Still to be implemented
}

/**
 * @brief Tests buffer overflows detection.
 */
void test_buffer_overflow_detector() {
    void *ptr9  = sys_allocate_memory(1024);
    TEST_ASSERT_NOT_NULL(ptr9);
    
    memset(ptr9,1,1100);
    int ret = buffer_overflow_detector();
    TEST_ASSERT_EQUAL_INT(-1,ret);
}

// Add more test functions as needed
/**
 * Function Name: simulate_memory_operations
 * Description: Simulates running 1000 iterations of allocating and freeing memory.
 *
 * Parameters:
 *   None
 *
 * Return:
 *   void
 */
void simulate_memory_operations() {
    srand(time(NULL));  // Seed for random number generation

    for (int i = 0; i < 1000; ++i) {
        // Generate a random size above 1000 for memory allocation
        int allocation_size = rand() % 4001 + 1001;

        // // Call sys_allocate_memory with the generated size
        const void* allocated_memory = sys_allocate_memory(allocation_size);
        if(allocated_memory == NULL)
        {
            printf("NULL");
            return;
        }
        // // Call sys_free_memory with the pointer from the allocation
        sys_free_memory(allocated_memory);
    }
    printf("Allocating memory time average %llf seconds\n",get_average_allocation_time());
    printf("Freeing memory time average %llf seconds\n",get_average_free_time()); 
    
}
/**
 * @brief Main function that runs all the test functions.
 *
 * @return 0 for success
 */
int main(void) {
    // Run test cases
    UNITY_BEGIN();
    RUN_TEST(test_allocate_memory);
    RUN_TEST(test_store_values);
    RUN_TEST(test_free_memory);
    RUN_TEST(test_reallocate_memory);
    RUN_TEST(test_invalid_reallocation);
    RUN_TEST(test_reallocate_smaller_size);
    RUN_TEST(test_get_memory_size);
    RUN_TEST(test_free_all_memory);
    RUN_TEST(test_buffer_overflow_detector);
    RUN_TEST(simulate_memory_operations);
    UNITY_END();
    return 0;  // Return 0 for success
}