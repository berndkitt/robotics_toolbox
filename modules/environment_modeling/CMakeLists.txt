# define project name
project(environment_modeling)

# build libraries of the module
add_subdirectory(libraries/libWPG)

# build unit tests of the module (if selected)
if(OPTION_BUILD_UNIT_TESTS)
    add_subdirectory(libraries/libWPG/testing/google_test)
endif(OPTION_BUILD_UNIT_TESTS)
