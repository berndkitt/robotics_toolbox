# define project name
project(FBVis)

# generate version number
execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/GenerateVersionNumber.py -b ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFBVis/ -o ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFBVis/versioning/ -if list_files.xml -iv list_versions.xml -of libFBVis_Fingerprints.txt -od libFBVis_DoxyfileVersion -oh libFBVis_Version.h)

# build libFBVis
add_library(${PROJECT_NAME} STATIC
    source_code/src/FeatureBucketerVisualizer.cpp
    source_code/src/LIBFBVISVersion.cpp)

# define include directories for libFBVis
target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ../../../../common/)

# link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Eigen3::Eigen)

# link libraries (for code coverage only)
if(OPTION_BUILD_UNIT_TESTS)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        --coverage
        gcov)
endif(OPTION_BUILD_UNIT_TESTS)
