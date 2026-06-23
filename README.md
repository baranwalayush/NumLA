# NumLA

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/std/the-standard)

NumLA is a scientific computing library designed to be easy-to-use and highly optimized, with a focus on providing a clean and modern interface for students.

## Getting Started

### Prerequisites
* A C++17 compatible compiler (e.g., GCC, Clang, MSVC).
* CMake 3.15 or later.

### Using NumLA in your project
The recommended way to use NumLA is to add it as a dependency using CMake's `FetchContent` module. This will download and configure NumLA automatically.

1.  **Update your `CMakeLists.txt`:**

   Add the following to your `CMakeLists.txt` file:

   ```cmake
   cmake_minimum_required(VERSION 3.15)
   project(MyProject LANGUAGES CXX)

   set(CMAKE_CXX_STANDARD 17)
   set(CMAKE_CXX_STANDARD_REQUIRED ON)

   include(FetchContent)
   FetchContent_Declare(
       NumLA
       GIT_REPOSITORY https://github.com/baranwalayush/NumLA.git
       GIT_TAG        main 
   )
   FetchContent_MakeAvailable(NumLA)

   add_executable(my_program main.cpp)

   target_link_libraries(my_program PRIVATE NumLA::NumLA)
   ```

2.  **Write your code (`main.cpp`):**

   Here is a simple example of how to use NumLA:

   ```cpp
   #include <iostream>
   #include "NumLA/matrix.hpp"

   int main() {
      // Create a 2x2 Identity Matrix
      auto I = NumLA::Matrix<double, 2, 2>::Identity();
      std::cout << "Successfully loaded NumLA!\n" << I;
      return 0;
   }
   ```

3.  **Build and Run:**

   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ./my_program
   ```

