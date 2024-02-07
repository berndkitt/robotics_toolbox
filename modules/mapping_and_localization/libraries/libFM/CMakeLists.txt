# define project name
project(FM)

# prepare library
execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/PrepareLibraryTemplates.py --directory_template_files ${CMAKE_SOURCE_DIR}/templates/ --directory_library ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFM/ --library_name FeatureMatching --library_abbreviation FM)
execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/GenerateVersionNumber.py -b ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFM/ -ci ${CMAKE_CXX_COMPILER_ID} -cv ${CMAKE_CXX_COMPILER_VERSION} -o ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFM/versioning/ -if list_files.xml -iv list_versions.xml -of libFM_Fingerprints.txt -od libFM_DoxyfileVersion -oh libFM_Version.h)

# build libFM
add_library(${PROJECT_NAME} STATIC
    source_code/src/FeatureMatcher.cpp
    source_code/src/LIBFMVersion.cpp)

# define include directories for libFM
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
