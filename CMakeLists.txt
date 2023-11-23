# define project name
project(robotics_toolbox)

# define minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

# include CMake modules
INCLUDE(CheckTypeSize)

# define minimum required C++ standard
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# check type sizes
set(BYTES_8_BIT  "1")
set(BYTES_16_BIT "2")
set(BYTES_32_BIT "4")
set(BYTES_64_BIT "8")

check_type_size("float"          SIZE_FLOAT32)
check_type_size("double"         SIZE_FLOAT64)
check_type_size("signed char"    SIZE_SINT8)
check_type_size("unsigned char"  SIZE_UINT8)
check_type_size("signed short"   SIZE_SINT16)
check_type_size("unsigned short" SIZE_UINT16)
check_type_size("signed int"     SIZE_SINT32)
check_type_size("unsigned int"   SIZE_UINT32)
check_type_size("signed long"    SIZE_SINT64)
check_type_size("unsigned long"  SIZE_UINT64)

if(NOT ${SIZE_FLOAT32} STREQUAL ${BYTES_32_BIT})
    message(FATAL_ERROR "Type 'float' is not of size ${BYTES_32_BIT} byte but of size ${SIZE_FLOAT32} byte.")
endif()
if(NOT ${SIZE_FLOAT64} STREQUAL ${BYTES_64_BIT})
    message(FATAL_ERROR "Type 'double' is not of size ${BYTES_64_BIT} byte but of size ${SIZE_FLOAT64} byte.")
endif()
if(NOT ${SIZE_SINT8} STREQUAL ${BYTES_8_BIT})
    message(FATAL_ERROR "Type 'signed char' is not of size ${BYTES_8_BIT} byte but of size ${SIZE_SINT8} byte.")
endif()
if(NOT ${SIZE_UINT8} STREQUAL ${BYTES_8_BIT})
    message(FATAL_ERROR "Type 'unsigned char' is not of size ${BYTES_8_BIT} byte but of size ${SIZE_UINT8} byte.")
endif()
if(NOT ${SIZE_SINT16} STREQUAL ${BYTES_16_BIT})
    message(FATAL_ERROR "Type 'signed short' is not of size ${BYTES_16_BIT} byte but of size ${SIZE_SINT16} byte.")
endif()
if(NOT ${SIZE_UINT16} STREQUAL ${BYTES_16_BIT})
    message(FATAL_ERROR "Type 'unsigned short' is not of size ${BYTES_16_BIT} byte but of size ${SIZE_UINT16} byte.")
endif()
if(NOT ${SIZE_SINT32} STREQUAL ${BYTES_32_BIT})
    message(FATAL_ERROR "Type 'signed int' is not of size ${BYTES_32_BIT} byte but of size ${SIZE_SINT32} byte.")
endif()
if(NOT ${SIZE_UINT32} STREQUAL ${BYTES_32_BIT})
    message(FATAL_ERROR "Type 'unsigned int' is not of size ${BYTES_32_BIT} byte but of size ${SIZE_UINT32} byte.")
endif()
if(NOT ${SIZE_SINT64} STREQUAL ${BYTES_64_BIT})
    message(FATAL_ERROR "Type 'signed long' is not of size ${BYTES_64_BIT} byte but of size ${SIZE_SINT64} byte.")
endif()
if(NOT ${SIZE_UINT64} STREQUAL ${BYTES_64_BIT})
    message(FATAL_ERROR "Type 'unsigned long' is not of size ${BYTES_64_BIT} byte but of size ${SIZE_UINT64} byte.")
endif()


# define build options
set(OPTION_BUILD_UNIT_TESTS ON CACHE BOOL "Build the unit tests of the modules.")

# search for 3rd party packages
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

# set compile options
set(CMAKE_CXX_FLAGS         "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG   "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# add compile options (for code coverage only)
if(OPTION_BUILD_UNIT_TESTS)
    add_compile_options(-fprofile-arcs -ftest-coverage)
endif(OPTION_BUILD_UNIT_TESTS)

# define output directories for the libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)

# define output directory for the executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# add the subdirectories of the modules
add_subdirectory(modules)
