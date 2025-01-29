# Minimum CMake version
cmake_minimum_required(VERSION 3.20)

# Project name and version
project(ThreadSafeHashTable VERSION 1.0 LANGUAGES CXX C) # Explicitly specify both C++ and C

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable FetchContent
include(FetchContent)

# Fetch BLAKE3
FetchContent_Declare(
    blake3
    GIT_REPOSITORY https://github.com/BLAKE3-team/BLAKE3.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(blake3)

# Fetch fmt (for format support)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        10.2.0
)
FetchContent_MakeAvailable(fmt)

# Manually add BLAKE3 source files (needed because it has no CMakeLists.txt)
set(BLAKE3_SOURCES
    ${blake3_SOURCE_DIR}/c/blake3.c
    ${blake3_SOURCE_DIR}/c/blake3_dispatch.c
    ${blake3_SOURCE_DIR}/c/blake3_portable.c
    ${blake3_SOURCE_DIR}/c/blake3_neon.c  # Ensure NEON is included
)

# Create a static library for BLAKE3 and specify it as a C library
add_library(blake3 STATIC ${BLAKE3_SOURCES})
set_target_properties(blake3 PROPERTIES LINKER_LANGUAGE C)  # Explicitly set language

# **Enable NEON for ARM64 macOS**
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
    target_compile_definitions(blake3 PRIVATE BLAKE3_USE_NEON=1)
    message(STATUS "Enabling NEON optimizations for ARM64 macOS")
endif()

# Include directories for headers
include_directories(src ${blake3_SOURCE_DIR}/c ${fmt_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/hash_function.cpp
    src/main.cpp
)

# Add the executable
add_executable(ThreadSafeHashTable ${SOURCES})

# Link BLAKE3 and fmt libraries
target_link_libraries(ThreadSafeHashTable PRIVATE blake3 fmt)

# Compiler warnings (recommended)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(ThreadSafeHashTable PRIVATE -Wall -Wextra -pedantic)
endif()

# Link required libraries (e.g., pthread)
find_package(Threads REQUIRED)
target_link_libraries(ThreadSafeHashTable PRIVATE Threads::Threads)
