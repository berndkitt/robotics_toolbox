# define project name
project(WPG)

# prepare library
execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/PrepareLibraryTemplates.py --directory_template_files ${CMAKE_SOURCE_DIR}/templates/ --directory_library ${CMAKE_SOURCE_DIR}/modules/environment_modeling/libraries/libWPG/ --library_name WorldPointGeneration --library_abbreviation WPG)
execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/GenerateVersionNumber.py -b ${CMAKE_SOURCE_DIR}/modules/environment_modeling/libraries/libWPG/ -ci ${CMAKE_CXX_COMPILER_ID} -cv ${CMAKE_CXX_COMPILER_VERSION} -bt ${CMAKE_BUILD_TYPE} -o ${CMAKE_SOURCE_DIR}/modules/environment_modeling/libraries/libWPG/versioning/ -if list_files.xml -iv list_versions.xml -of libWPG_Fingerprints.txt -oh libWPG_Version.h -od ${CMAKE_SOURCE_DIR}/modules/environment_modeling/libraries/libWPG/documentation/libWPG_Doxyfile)

# build libWPG
add_library(${PROJECT_NAME} STATIC
    source_code/src/LIBWPGVersion.cpp
    source_code/src/WorldPointGeneratorBase.cpp
    source_code/src/WorldPointGeneratorCuboid.cpp)

# define include directories for libWPG
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
