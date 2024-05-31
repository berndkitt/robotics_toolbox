# define project name
project(FBVis)

# prepare library
execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/PrepareLibraryTemplates.py --directory_template_files ${CMAKE_SOURCE_DIR}/templates/ --directory_library ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFBVis/ --library_name FeatureBucketingVisualization --library_abbreviation FBVis)
execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/GenerateVersionNumber.py -b ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFBVis/ -ci ${CMAKE_CXX_COMPILER_ID} -cv ${CMAKE_CXX_COMPILER_VERSION} -bt ${CMAKE_BUILD_TYPE} -o ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFBVis/versioning/ -if list_files.xml -iv list_versions.xml -of libFBVis_Fingerprints.txt -oh libFBVis_Version.h -od ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFBVis/documentation/libFBVis_Doxyfile)

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
