# define project name
project(mapping_and_localization)

# build libraries of the module
add_subdirectory(libraries/libFB)

# build unit tests of the module (if selected)
if(OPTION_BUILD_UNIT_TESTS)
    add_subdirectory(libraries/libFB/testing/google_test)
endif(OPTION_BUILD_UNIT_TESTS)
