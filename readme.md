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
- **Platform independent**:
It can run on a hosted environment, or it can run as a part of an OS,
- **Architecture Independent**:
It uses NO architecture specific code, is fully portable
- **And many others**
- **Library Option**:
It can be compiled as a static library.
- **Examples**:
There are examples to help get you started

- **Fast**: 
Allocating memory takes an average of 0.000000 seconds. Freeing memory takes an average 0.000001 seconds



## Getting Started

### Prerequisites

- An OS that can boot, and get information about memory from somewhere

### Usage(In OS)

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/KingVentrix007/Memory-Allocator.git
    ```

2. Switch to one of the release branches

```bash
    git checkout release-V(X).(X)
```

3. **Include the Memory Allocator in Your Project:**

    Include the necessary files (`mem.h` and `mem.c` and optinally `internal.c` and `internal.h`) in your hobby OS project.
    **Important** mem.c and mem.h rely on memset,memcpy and other mem functions, These need to be provided or internal.c and internal.h must be included

4. **Initialize Memory Allocation:**

    ```c
    #include "mem.h"
    
    void *memory_region = NULL;

    int main() {
        // Allocate initial memory
        memory_region = (void*)start_of_open_memory;
        init_memory_allocation(memory_region, [size of start_of_open_memory]);

        // Your code here

        return 0;
    }
    ```

5. **Allocate and Free Memory:**

    ```c
    // Allocate memory
    void *ptr = sys_allocate_memory([size]);

    // Your code here

    // Free memory
    sys_free_memory(ptr);
    ```

6. **Extend Allocation Space:**
    **CURRENTLY NOT WORKING. IS IN PROGRESS**

    ```c
    void *new_region = (void *)start_of_open_memory_2;
    extend_allocation_space(new_region, [size of start_of_open_memory_2]);
    ```

See [Examples](/docs/examples/basic.md#basic-memory-allocation-and-deallocation) for more.

### Usage(Stand Alone)

1. Clone repository

```bash
git clone https://github.com/KingVentrix007/Memory-Allocator.git
```

2. Switch to one of the release branches

```bash
    git checkout release-V(X).(X)
```

3. Edit mem_config.h

    Set your desired parameters

4. Run Normal version

```bash
make build
make run
```

you can set `USE_VERBOSE_OUTPUT` to 1 in the config file to get printed output

5. Run tests

```bash
make build-test
make run-test
```
Check out the [docs](docs/html/index.html) for more specifics on each function
Check out the examples
See The AI Generated [FileStructure.md](docs/FilesStructure.md) for more info on each file

## Contributing

If you have suggestions or improvements, feel free to open an issue or create a pull request.

## License

This project is licensed under the [MIT](https://opensource.org/license/mit/) - see the [LICENSE](LICENSE) file for details.
