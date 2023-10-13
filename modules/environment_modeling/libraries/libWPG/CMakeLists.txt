# define project name
project(WPG)

# build libWPG
add_library(${PROJECT_NAME} STATIC
    source_code/src/WorldPointGeneratorBase.cpp)

# define include directories for libWPG
target_include_directories(${PROJECT_NAME} PRIVATE
    ../../../../common/)

# link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Eigen3::Eigen)
