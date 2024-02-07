# define project name
project(FB)

# prepare library
execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/PrepareLibraryTemplates.py --directory_template_files ${CMAKE_SOURCE_DIR}/templates/ --directory_library ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFB/ --library_name FeatureBucketing --library_abbreviation FB)
execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/GenerateVersionNumber.py -b ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFB/ -ci ${CMAKE_CXX_COMPILER_ID} -cv ${CMAKE_CXX_COMPILER_VERSION} -o ${CMAKE_SOURCE_DIR}/modules/mapping_and_localization/libraries/libFB/versioning/ -if list_files.xml -iv list_versions.xml -of libFB_Fingerprints.txt -od libFB_DoxyfileVersion -oh libFB_Version.h)

# build libFB
add_library(${PROJECT_NAME} STATIC
    source_code/src/FeatureBucketerBase.cpp
    source_code/src/FeatureBucketerByChance.cpp
    source_code/src/FeatureBucketerByOrder.cpp
    source_code/src/LIBFBVersion.cpp)

# define include directories for libFB
target_include_directories(${PROJECT_NAME} PRIVATE
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
