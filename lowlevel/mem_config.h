/*
 * File: mem_config.h
 * Language: C
 * 
 * Summary:
 * This header file defines the configuration settings for memory management.
 * It defines constants for the block size, maximum number of cached allocations,
 * default log level, and whether to use verbose output. If USE_VERBOSE_OUTPUT
 * is set to 1, the MEMORY_ALLOCATION_VERBOSE_OUTPUT macro is also defined.
 */

#ifndef __MEM_CONFIG__H
#define __MEM_CONFIG__H

#define BLOCK_SIZE 1024 // The Block Size that each node will have
#define MAX_CASHED_ALLOCATIONS 100 // THe max number of cashed allocations
#define DEFAULT_LOG_LEVEL 0 // Log level by default
#define USE_VERBOSE_OUTPUT 0 // Use verbose output for debugging
#define ALIGNMENT 16 // The memory alignment
#define RUN_CHECKS_ON_ALLOCATE 0 //Wether or not to run checks on memory allocation 0=false, 1=true
#define RUN_CHECKS_ON_FREE 0 //Wether or not to run checks on free memory 0=false, 1=true
#if USE_VERBOSE_OUTPUT == 1
#define MEMORY_ALLOCATION_VERBOSE_OUTPUT
#endif

#endif