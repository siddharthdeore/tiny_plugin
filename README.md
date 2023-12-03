# Tiny Plugin: A minimal Plugin Library for my Digital Signal Processing Experiments

## Overview

Tiny Plugin is a header only cross platform lightweight C++ library designed to facilitate the development of plugins for digital signal processing experiments and audio projects. This library is particularly useful for making generic plugin based software architecture.


## Features

- **Lightweight:** Tiny Plugin is designed with a minimalistic approach to keep the overhead low while allowing seamless integration into existing projects.

- **Modular Architecture:** The library follows a modular architecture, making it easy to add, remove, or replace plugins without disrupting the core functionality.

- **Extensibility:** Developers can easily extend the library by creating custom plugins that adhere to the defined interface, enabling the integration of domain-specific functionality.

## Getting Started

### Installation

To use Tiny Plugin in your project, follow these simple steps:

1. Clone the Tiny Plugin repository: `https://github.com/siddharthdeore/tiny_plugin.git`

2. Build the library:
     ```console
    cd tiny_plugin
    mkdir build && cd build
    cmake ..
    make
    make install
     ```


### Usage
Library can be imported in to cmake project using `find_package` CMake command as following example:
```cmake
cmake_minimum_required(VERSION 3.0)
project(myproject)
find_package(tiny_pluin REQUIRED)
add_executable(example example.cpp)
target_link_libraries(example tiny_pluin::tiny_pluin)
``` 

`example.cpp` to load shared library
```cpp
#include <memory>

#include <tiny_plugin/SharedLibrary.h>

int main()
{
    SharedLibrary simple("SimplePlugin");

    if (simple.is_loaded())
    {
        auto instance = simple.create_instance_sptr<void *>();
    }

    return 0;
}

```

# Maintainer

Siddharth Deore