cmake_minimum_required(VERSION 3.15)
project(NumLA LANGUAGES CXX)

# Enforce C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define header-only library target
add_library(NumLA INTERFACE)
target_include_directories(NumLA INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Add Unit Test Executable
add_executable(run_tests tests/test_matrix.cpp)
target_link_libraries(run_tests PRIVATE NumLA)