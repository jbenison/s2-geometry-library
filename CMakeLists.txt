# Old enough to support Ubuntu Trusty.
cmake_minimum_required(VERSION 2.8.12)
project(s2-geometry-library)

# Won't build with c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()

# Add cmake options
option(BUILD_EXAMPLES "build examples" OFF)
option(BUILD_SHARED_LIBS "build shared libraries" OFF)
option(BUILD_TESTING "build testing" OFF)
option(BUILD_BENCHMARKS "build benchmarks" OFF)

# For resolving headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/geometry)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(gflags REQUIRED)
if (gflags_FOUND)
  include_directories(${gflags_INCLUDE_DIR})
  set(LIBS ${LIBS} ${gflags_LIBRARIES})
endif()

find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIR})
  set(LIBS ${LIBS} ${OPENSSL_LIBRARIES})
endif()

find_package(Threads REQUIRED)
if (THREADS_FOUND)
  set(LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT})
endif()

if(BUILD_TESTING OR BUILD_BENCHMARKS)
  enable_testing()
  if(BUILD_TESTING)
    find_package(GTest REQUIRED)
  endif(BUILD_TESTING)
  if(BUILD_BENCHMARKS)
    find_package(Benchmark REQUIRED)
  endif(BUILD_BENCHMARKS)
endif(BUILD_TESTING OR BUILD_BENCHMARKS)

# The actual s2-geometry-library
add_subdirectory(geometry)

# Add examples in here
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# Add uninstall target
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
    )

add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
    )