/**
 * @file mem_output.h
 * @brief ouput for memory Allocation functions
 */
#ifndef MEM_OUTPUT_H
#define MEM_OUTPUT_H
#include "mem_config.h"
#define LOG_ERROR 0 // Log error
#define LOG_WARNING 1 // Log warning
#define LOG_INFO 2 // Log info

// Set the default log level based on your needs
#ifndef LOG_LEVEL
#define LOG_LEVEL DEFAULT_LOG_LEVEL // Sets the default log level
#endif

#ifdef MEMORY_ALLOCATION_VERBOSE_OUTPUT

// Function to print memory allocation log with additional information
#define MEM_ALLOC_LOG(level,fmt, ...) \
    do { \
        if (level == LOG_ERROR && LOG_LEVEL == LOG_ERROR) \
            printf("[ERROR] "); \
        else if (level == LOG_WARNING && LOG_LEVEL == LOG_WARNING) \
            printf("[WARNING] "); \
        else if (level == LOG_INFO && LOG_LEVEL == LOG_INFO) \
            printf("[INFO] "); \
        \
        printf("File: %s, Function: %s, Line: %d - " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#else
#define MEM_ALLOC_LOG(level,fmt, ...) do { } while (0) //Place holder for MEM_ALLOC_LOG
#endif
#endif