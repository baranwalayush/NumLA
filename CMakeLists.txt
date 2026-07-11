cmake_minimum_required(VERSION 3.15)
project(NumLA VERSION 1.0.0 LANGUAGES CXX)

# Enforce C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define header-only library target
add_library(NumLA INTERFACE)
add_library(NumLA::NumLA ALIAS NumLA) 
target_include_directories(NumLA INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # Add Unit Test Executable
    add_executable(run_tests 
            tests/main.cpp
            tests/test_matrix.cpp
            tests/test_algorithms.cpp)
    target_link_libraries(run_tests PRIVATE NumLA)

    # Add Example Executable
    file(GLOB EXAMPLE_SOURCES "examples/*.cpp")
    foreach(source_file ${EXAMPLE_SOURCES})

        get_filename_component(example_name ${source_file} NAME_WE)
        
        add_executable(${example_name} ${source_file})

        target_link_libraries(${example_name} PRIVATE NumLA)

    endforeach()

endif()

# Install the library
include(GNUInstallDirs)
install(TARGETS NumLA
    EXPORT NumLATargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Generate and install the package configuration files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "NumLAVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

export(
    EXPORT NumLATargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/NumLATargets.cmake"
    NAMESPACE NumLA::
)

install(
    EXPORT NumLATargets
    FILE NumLATargets.cmake
    NAMESPACE NumLA::
    DESTINATION lib/cmake/NumLA
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/NumLAVersion.cmake"
    DESTINATION
        lib/cmake/NumLA
)