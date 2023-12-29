# Memory Allocator for Hobby OS

## Overview

This repository contains a simple memory allocator designed for hobby operating systems. It provides basic functionality for managing memory regions using a linked list data structure.

## Features

- **Memory Allocation**: Allocate contiguous blocks of memory.
- **Memory Deallocation**: Free previously allocated memory.
- **Extend Allocation Space**: Dynamically extend the allocation space by connecting to a new memory region.

## Getting Started

### Prerequisites

- An OS that can boot, and get information about memory from somewhere

### Usage

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/KingVentrix007/Memory-Allocator.git
    ```

2. **Include the Memory Allocator in Your Project:**

    Include the necessary files (`mem.h` and `mem.c`) in your hobby OS project.

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
    !CURRENTLY NOT WORKING. IS IN PROGRESS
    ```c
    void *new_region = malloc([extra_memory_size]);
    extend_allocation_space(new_region, [extra_memory_size]);
    ```

## Contributing

If you have suggestions or improvements, feel free to open an issue or create a pull request.

## License

This project is licensed under the [MIT] - see the [LICENSE](LICENSE) file for details.
