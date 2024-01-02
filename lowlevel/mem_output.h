// Define different logging levels
#ifndef MEM_OUTPUT_H
#define MEM_OUTPUT_H
#define LOG_ERROR 0
#define LOG_WARNING 1
#define LOG_INFO 2

// Set the default log level based on your needs
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_INFO
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
#define MEM_ALLOC_LOG(level,fmt, ...) do { } while (0)
#endif
#endif