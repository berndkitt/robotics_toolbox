# define project name
project(unit_tests_libWPG)

# build unit tests
add_executable(${PROJECT_NAME}
    source_code/main.cpp
    source_code/Test_LIBWPGVersion.cpp
    source_code/Test_WorldPointGeneratorCuboid.cpp)

# define include directories for the unit tests
target_include_directories(${PROJECT_NAME} PRIVATE
    ../../../../../../common/)

# link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Eigen3::Eigen
    gtest
    pthread
    WPG)
