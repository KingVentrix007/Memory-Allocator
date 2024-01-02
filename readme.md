# Memory Allocator for Hobby OS
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=KingVentrix007_Memory-Allocator&metric=alert_status)](https://sonarcloud.io/dashboard?id=KingVentrix007_Memory-Allocator)
[![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=KingVentrix007_Memory-Allocator&metric=security_rating)](https://sonarcloud.io/dashboard?id=KingVentrix007_Memory-Allocator)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=KingVentrix007_Memory-Allocator&metric=bugs)](https://sonarcloud.io/dashboard?id=KingVentrix007_Memory-Allocator)
[![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=KingVentrix007_Memory-Allocator&metric=ncloc)](https://sonarcloud.io/dashboard?id=KingVentrix007_Memory-Allocator)


## Overview

This repository contains a simple memory allocator designed for hobby operating systems. It provides basic functionality for managing memory regions using a linked list data structure.


## Features
- **Memory Allocation**: Allocate contiguous blocks of memory.
- **Memory Deallocation**: Free previously allocated memory.
- **Extend Allocation Space**: Dynamically extend the allocation space by connecting to a new memory region.
- **_msize functionality**:
Provides the ability to get the size of a memory region
- **And many others**
## Getting Started

### Prerequisites

- An OS that can boot, and get information about memory from somewhere

### Usage

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/KingVentrix007/Memory-Allocator.git
    ```

2. **Include the Memory Allocator in Your Project:**

    Include the necessary files (`mem.h` and `mem.c` and optinally `internal.c` and `internal.h`) in your hobby OS project.
    **Important** mem.c and mem.h rely on memset,memcpy and other mem functions, These need to be provided or internal.c and internal.h must be included
 **Warning** In these examples `malloc` is used to simulate having a region of memory in the RAM, typically malloc would be replaced with the address of the memory region

3. **Initialize Memory Allocation:**

    ```c
    #include "mem.h"
    
    void *memory_region = NULL;

    int main() {
        // Allocate initial memory
        memory_region = malloc([initial_memory_size]);
        init_memory_allocation(memory_region, [initial_memory_size]);

        // Your code here

        return 0;
    }
    ```

4. **Allocate and Free Memory:**

    ```c
    // Allocate memory
    void *ptr = sys_allocate_memory([size]);

    // Your code here

    // Free memory
    sys_free_memory(ptr);
    ```

5. **Extend Allocation Space:**
    **CURRENTLY NOT WORKING. IS IN PROGRESS**
    ```c
    void *new_region = malloc([extra_memory_size]);
    extend_allocation_space(new_region, [extra_memory_size]);
    ```

## Contributing

If you have suggestions or improvements, feel free to open an issue or create a pull request.

## License

This project is licensed under the [MIT] - see the [LICENSE](LICENSE) file for details.
