cmake_minimum_required(VERSION 2.8)

# CHECK: shouldn't this set CMAKE_BUILD_TYPE=RelWithDebInfo?
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type, one of: Debug, Release")
message(STATUS "Build type is ${CMAKE_BUILD_TYPE}")

project(boost.SIMD-testing)

# Set a variable for the CMake Eclipse generator.
set(
  CMAKE_ECLIPSE_VERSION
  4.5.0
  CACHE
  STRING
  "Eclipse version - only used with the CMake generator 'Eclipse CDT4 - Unix Makefiles'"
  )

set(CMAKE_SHARED_MODULE_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

set(
  CMAKE_CXX_FLAGS_DEBUG
  "-Wall -Werror -O0 -pipe -fstack-protector-all -pthread -fvisibility=hidden std=gnu++14 -Wno-deprecated -g"
  )

set(
  CMAKE_CXX_FLAGS_RELEASE
  "-Wall -Werror -O2 -pipe -pthread -fvisibility=hidden -std=gnu++14 -Wno-deprecated -g"
  )

# Find the Google Benchmark library.
find_library(
  BENCHMARK_LIBRARY
  benchmark
  /home/joachim//benchmark-build/src
  DOC "The Google Benchmark library."
  )
if(NOT BENCHMARK_LIBRARY)
  message(FATAL_ERROR "Cannot find Google Benchmark library.")
endif()
message(STATUS "Found the Google Benchmark library:")
message(STATUS "  ${BENCHMARK_LIBRARY}")

include_directories(
  /home/joachim/boost.simd/include
  /home/joachim/benchmark/include
)

add_subdirectory(src)
