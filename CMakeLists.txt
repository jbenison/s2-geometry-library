cmake_minimum_required(VERSION 3.3)
project(s2_geometry_library)

# Won't build with c++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Set the install prefix
# Install target not yet implemented
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()

# Add cmake options
option(BUILD_EXAMPLES "Enable or disable building examples" OFF)

# For resolving headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/geometry)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/geometry/strings)

# The actual s2-geometry-library
add_subdirectory(geometry)

# Add examples in here
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()