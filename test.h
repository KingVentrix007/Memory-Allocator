#ifdef TEST_CASES_VISUAL

#define PRINT_TEST_CASE_HEADER(test_case_name) \
    printf("%s: %s\n", "Test Case", test_case_name)

#define PRINT_TEST_FAILURE(test_case_number) \
    printf("Test Case %d failed\n", test_case_number)

#define PRINT_SUCCESS_MESSAGE(message) \
    printf("%s\n", message)

#else

#define PRINT_TEST_CASE_HEADER(test_case_name)
#define PRINT_TEST_FAILURE(test_case_number)
#define PRINT_SUCCESS_MESSAGE(message)

#endif