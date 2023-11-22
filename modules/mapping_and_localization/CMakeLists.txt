# define project name
project(mapping_and_localization)

# build libraries of the module
add_subdirectory(libraries/libFB)
add_subdirectory(libraries/libFBVis)

# build unit tests of the module (if selected)
if(OPTION_BUILD_UNIT_TESTS)
    add_subdirectory(libraries/libFB/testing/google_test)
    add_subdirectory(libraries/libFBVis/testing/google_test)
endif(OPTION_BUILD_UNIT_TESTS)
