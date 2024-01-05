<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=KingVentrix007_Memory-Allocator&metric=alert_status)](https://sonarcloud.io/dashboard?id=KingVentrix007_Memory-Allocator)
[![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=KingVentrix007_Memory-Allocator&metric=security_rating)](https://sonarcloud.io/dashboard?id=KingVentrix007_Memory-Allocator)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=KingVentrix007_Memory-Allocator&metric=bugs)](https://sonarcloud.io/dashboard?id=KingVentrix007_Memory-Allocator)
[![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=KingVentrix007_Memory-Allocator&metric=ncloc)](https://sonarcloud.io/dashboard?id=KingVentrix007_Memory-Allocator)


<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/KingVentrix007/Memory-Allocator">
    <img src="tek-logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Memory Allocator</h3>

  <p align="center">
    This repository contains a simple memory allocator designed for hobby operating systems. It provides basic functionality for managing memory regions using a linked list data structure.
    <br />
    <a href="https://github.com/KingVentrix007/Memory-Allocator"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/KingVentrix007/Memory-Allocator">View Demo</a>
    ·
    <a href="https://github.com/KingVentrix007/Memory-Allocator/issues">Report Bug</a>
    ·
    <a href="https://github.com/KingVentrix007/Memory-Allocator/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#features">Features</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project
The Memory Allocator is a versatile project designed for hobby operating systems. It provides essential functionality for managing memory regions using a linked list data structure. This project aims to facilitate memory allocation, deallocation, and extension of allocation space in a dynamic and efficient manner. The Memory Allocator is intended to be utilized both as a standalone library and as part of an operating system.



<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Features

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
- **Fast**:
Allocating memory takes an average of 0.000000 seconds. Freeing memory takes an average 0.000001 seconds

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

- An OS that can boot, and get information about memory from somewhere
- A text editor
- Git
- A C99 compatible c compiler

### Installation

1. Clone the repo

   ```sh
   git clone https://github.com/KingVentrix007/Memory-Allocator.git
   ```

2. Switch to one of the release branches

    ```bash
      git checkout release-V(X).(X)
    ```

3. **Include the Memory Allocator in Your Project:**

    Include the necessary files (`mem.h` and `mem.c` and optinally `internal.c` and `internal.h`) in your hobby OS project.
    **Important** mem.c and mem.h rely on memset,memcpy and other mem functions, These need to be provided or internal.c and internal.h must be included

See [Examples](/docs/examples/basic.md#basic-memory-allocation-and-deallocation) for more.
<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage

There are two ways you can use this project **Standalone** and **As part of an OS**.

### As part of an OS

1. **Initialize Memory Allocation:**

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

2. **Allocate and Free Memory:**

    ```c
    // Allocate memory
    void *ptr = sys_allocate_memory([size]);

    // Your code here

    // Free memory
    sys_free_memory(ptr);
    ```

3. **Extend Allocation Space:**
    **CURRENTLY NOT WORKING. IS IN PROGRESS**

    ```c
    void *new_region = (void *)start_of_open_memory_2;
    extend_allocation_space(new_region, [size of start_of_open_memory_2]);
    ```

### Standalone

1. Edit mem_config.h

    Set your desired parameters

2. Run Normal version

```bash
make build
make run
```

you can set `USE_VERBOSE_OUTPUT` to 1 in the config file to get printed output

3. Run tests

```bash
make build-test
make run-test
```

Check out the [docs](docs/html/index.html) for more specifics on each function
Check out the examples


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

- [X] Allocate and Free Memory
- [X] PMM(Physical Memory Manager)
- [X] Have `sys_allocate_memory` and `sys_free_memory` use regions from the pmm
- [ ] Error Checking
  - [X] Buffer Overflow
  - [X] Dangling Pointer
  - [ ] Memory Leaks
  - [ ] Bad Pointer
  - [ ] Bad Region

<!-- See the [open issues](https://github.com/KingVentrix007/Memory-Allocator/issues) for a full list of proposed features (and known issues). -->

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Tristan Kuhn - <tristanjkuhn007@gmail.com>

Project Link: [https://github.com/KingVentrix007/Memory-Allocator](https://github.com/KingVentrix007/Memory-Allocator)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

- [othneildrew](https://github.com/othneildrew/Best-README-Template/blob/master/BLANK_README.md)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/KingVentrix007/Memory-Allocator.svg?style=for-the-badge
[contributors-url]: https://github.com/KingVentrix007/Memory-Allocator/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/KingVentrix007/Memory-Allocator.svg?style=for-the-badge
[forks-url]: https://github.com/KingVentrix007/Memory-Allocator/network/members
[stars-shield]: https://img.shields.io/github/stars/KingVentrix007/Memory-Allocator.svg?style=for-the-badge
[stars-url]: https://github.com/KingVentrix007/Memory-Allocator/stargazers
[issues-shield]: https://img.shields.io/github/issues/KingVentrix007/Memory-Allocator.svg?style=for-the-badge
[issues-url]: https://github.com/KingVentrix007/Memory-Allocator/issues
[license-shield]: https://img.shields.io/github/license/KingVentrix007/Memory-Allocator.svg?style=for-the-badge
[license-url]: https://github.com/KingVentrix007/Memory-Allocator/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/tristan-kuhn-40386b2a1
[product-screenshot]: images/screenshot.png
