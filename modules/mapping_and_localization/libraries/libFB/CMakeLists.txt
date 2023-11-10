# define project name
project(FB)

# generate version number
execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/GenerateVersionNumber.py -b ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFB/ -o ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFB/versioning/ -if list_files.xml -iv list_versions.xml -of libFB_Fingerprints.txt -od libFB_DoxyfileVersion -oh libFB_Version.h)

# build libFB
add_library(${PROJECT_NAME} STATIC
    source_code/src/FeatureBucketer.cpp)

# define include directories for libFB
target_include_directories(${PROJECT_NAME} PRIVATE
    ../../../../common/)

# link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Eigen3::Eigen)
