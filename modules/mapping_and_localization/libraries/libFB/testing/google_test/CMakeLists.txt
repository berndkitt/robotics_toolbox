# define project name
project(unit_tests_libFB)

# build unit tests
add_executable(${PROJECT_NAME}
    source_code/main.cpp
    source_code/Test_LIBFBVersion.cpp)

# define include directories for the unit tests
target_include_directories(${PROJECT_NAME} PRIVATE
    ../../../../../../common/)

# link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Eigen3::Eigen
    gtest
    pthread
    FB)

# link libraries (for code coverage only)
if(OPTION_BUILD_UNIT_TESTS)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        --coverage
        gcov)
endif(OPTION_BUILD_UNIT_TESTS)
