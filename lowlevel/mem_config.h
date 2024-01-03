/**
 * @file mem_config.h
 * @brief Configuration settings for memory management.
 */

#ifndef MEM_CONFIG_H
#define MEM_CONFIG_H

/**
 * @brief Block size for memory management.
 */
#define BLOCK_SIZE 1024

/**
 * @brief Maximum number of cached allocations.
 */
#define MAX_CACHED_ALLOCATIONS 100

/**
 * @brief Alignment of teh memory region in bytes
 * 
 */

#define ALIGNMENT 16
/**
 * @brief Default log level for memory management.
 */
#define DEFAULT_LOG_LEVEL 2

/**
 * @brief Use verbose output for memory management.
 *
 * If USE_VERBOSE_OUTPUT is set to 1, the MEMORY_ALLOCATION_VERBOSE_OUTPUT macro is also defined.
 */
#define USE_VERBOSE_OUTPUT 0

#if USE_VERBOSE_OUTPUT == 1
/**
 * @brief Macro for verbose output in memory management.
 */
#define MEMORY_ALLOCATION_VERBOSE_OUTPUT
#endif

#endif /* MEM_CONFIG_H */
