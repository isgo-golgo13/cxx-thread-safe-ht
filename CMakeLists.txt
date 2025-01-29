# Minimum CMake version
cmake_minimum_required(VERSION 3.20)

# Project name and version
project(ThreadSafeHashTable VERSION 1.0 LANGUAGES CXX)

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

# Manually add BLAKE3 source files (necessary for compilation)
set(BLAKE3_SOURCES
    ${blake3_SOURCE_DIR}/c/blake3.c
    ${blake3_SOURCE_DIR}/c/blake3_dispatch.c
    ${blake3_SOURCE_DIR}/c/blake3_portable.c
)

# Add source files
set(SOURCES
    src/hash_function.cpp
    src/main.cpp
    ${BLAKE3_SOURCES}  # Add Blake3 sources to the project
)

# Include directories for headers
include_directories(src ${blake3_SOURCE_DIR}/c)  # Include BLAKE3 headers

# Add the executable
add_executable(ThreadSafeHashTable ${SOURCES})

# Compiler warnings (optional but recommended)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(ThreadSafeHashTable PRIVATE -Wall -Wextra -pedantic)
endif()

# Link required libraries (e.g., pthread)
find_package(Threads REQUIRED)
target_link_libraries(ThreadSafeHashTable PRIVATE Threads::Threads)
