#include "unity.h"
#include "../lowlevel/mem.h"
#include "string.h"  
/**   
 * Function Name: setUp
 * Description: Set up function called before each test function.
 */
void setUp(void) {
    // printf("setUp() called\n");
    main_automated_testing();
}

/**
 * Function Name: tearDown
 * Description: Tear down function called after each test function.
 */
void tearDown(void) {
    main_automated_testing_end();
}


/**
 * Function Name: test_allocate_memory
 * Description: Tests the allocation of memory using sys_allocate_memory function.
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
 * Function Name: test_store_values
 * Description: Tests storing values in the allocated memory.
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
 * Function Name: test_free_memory
 * Description: Tests freeing allocated memory.
 */
void test_free_memory() {
    
    void *ptr2 = sys_allocate_memory(2048);
    // printf("ptr2 = 0x%p",ptr2);
    ptr2 = sys_free_memory(ptr2);
    //  printf("\n%s:%d ptr2 = 0x%p\n",__FILE__,__LINE__,ptr2);
    TEST_ASSERT_NULL(ptr2);
   
}

/**
 * Function Name: test_reallocate_memory
 * Description: Tests reallocating memory using sys_reallocate_memory function.
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
 * Function Name: test_invalid_reallocation
 * Description: Tests error handling for invalid parameters in reallocating memory.
 */
void test_invalid_reallocation() {
  
    const void *invalid_ptr = sys_reallocate_memory(NULL, 0, 8192);
    TEST_ASSERT_NULL(invalid_ptr);
}

/**
 * Function Name: test_reallocate_smaller_size
 * Description: Tests error handling for reallocating to smaller or equal size.
 */
void test_reallocate_smaller_size() {
    
    void *ptr4 = sys_allocate_memory(8192);
    void *ptr5 = sys_reallocate_memory(ptr4, 8192, 4096);
    TEST_ASSERT_EQUAL_PTR(ptr4, ptr5);
}

/**
 * Function Name: test_get_memory_size
 * Description: Tests getting the size of allocated memory.
 */
void test_get_memory_size() {
   

    void *ptr7 = sys_allocate_memory(1028);
    TEST_ASSERT_NOT_NULL(ptr7);

    size_t size = get_memory_size(ptr7);
    TEST_ASSERT_EQUAL_INT(1028, size);
}

/**
 * Function Name: test_free_all_memory
 * Description: Tests freeing all remaining allocated memory.
 */
void test_free_all_memory() {
   
    //Simple test case for freeing all memory. Still to be implemented
    
}

/**
 * Function Name: Test_memory_leek_detector
 * Description: Tests memory leak detection
 */

void test_memory_leek_detector()
{
    
    void *ptr9  = sys_allocate_memory(1024);
    TEST_ASSERT_NOT_NULL(ptr9);
    // const int *value = 1;
    memset(ptr9,1,1100);
    int ret = memory_leak_detector();
    TEST_ASSERT_EQUAL_INT(-1,ret);
}


// Add more test functions as needed

/**
 * Function Name: main
 * Description: Main function that runs all the test functions.
 *
 * Parameters: None
 *
 * Return: None
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
    RUN_TEST(test_memory_leek_detector);
    UNITY_END();

    return 0;  // Return 0 for success
}