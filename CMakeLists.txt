# define project name
project(robotics_toolbox)

# define minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

# define minimum required C++ standard
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# define build options
set(OPTION_BUILD_UNIT_TESTS ON CACHE BOOL "Build the unit tests of the modules.")

# search for 3rd party packages
find_package(Eigen3 REQUIRED)

# set compile options
set(CMAKE_CXX_FLAGS         "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG   "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# define output directories for the libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)

# define output directory for the executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# add the subdirectories of the modules
add_subdirectory(modules)
