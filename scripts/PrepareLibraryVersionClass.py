"""
Script to prepare the version class for a library.

The script copies the templates for the version class as well as the corresponding unit test file
into the library's directory and replaces the placeholders by proper values.
"""

import argparse
import shutil

# define global variables
search_string_library_abbreviation           = "$LIB_ABBREVIATION$"
search_string_library_abbreviation_uppercase = "$LIB_ABBREVIATION_UPPERCASE$"
filename_source_header                       = "LIBVersion.h"
filename_source_source                       = "LIBVersion.cpp"
filename_source_unit_tests                   = "Test_LIBVersion.cpp"


def replace_library_name(filename_with_path: str,
                         search_string:      str,
                         replace_string:     str) -> None:
    """
    Replace a string by another string in a given file.

    Args:
        filename_with_path (str): Filename including its path.
        search_string (str):      String to search.
        replace_string (str):     New string.
    """
    # read input file
    with open(filename_with_path, "r") as file_input:
        file_data = file_input.read()

        # update content
        file_data_updated = file_data.replace(search_string, replace_string)

    # write output file with updated content
    with open(filename_with_path, "w") as file_output:
        file_output.write(file_data_updated)


def prepare_library_version_class(directory_template_files: str,
                                  directory_library:        str,
                                  library_abbreviation:     str) -> None:
    """
    Prepare the library version class.

    Args:
        directory_template_files (str): Path to the directory containing the template files.
        directory_library (str):        Base directory of the library.
        library_abbreviation (str):     Abbreviation of the library.
    """
    # create source filenames
    filename_with_path_source_header = f"{directory_template_files}/{filename_source_header}"
    filename_with_path_source_source = f"{directory_template_files}/{filename_source_source}"

    # create target filenames
    filename_target_header           = f"LIB{library_abbreviation.upper()}Version.h"
    filename_target_source           = f"LIB{library_abbreviation.upper()}Version.cpp"
    filename_with_path_target_header = f"{directory_library}/source_code/include/{filename_target_header}"
    filename_with_path_target_source = f"{directory_library}/source_code/src/{filename_target_source}"

    # copy templates
    shutil.copy2(filename_with_path_source_header, filename_with_path_target_header)
    shutil.copy2(filename_with_path_source_source, filename_with_path_target_source)

    # replace information in target files
    replace_library_name(filename_with_path_target_header, search_string_library_abbreviation, library_abbreviation)
    replace_library_name(filename_with_path_target_header, search_string_library_abbreviation_uppercase, library_abbreviation.upper())
    replace_library_name(filename_with_path_target_source, search_string_library_abbreviation, library_abbreviation)
    replace_library_name(filename_with_path_target_source, search_string_library_abbreviation_uppercase, library_abbreviation.upper())


def prepare_library_version_class_unit_tests(directory_template_files: str,
                                             directory_library:        str,
                                             library_abbreviation:     str) -> None:
    """
    Prepare the unit tests of the library version class.

    Args:
        directory_template_files (str): Path to the directory containing the template files.
        directory_library (str):        Base directory of the library.
        library_abbreviation (str):     Abbreviation of the library.
    """
    # create source filename
    filename_with_path_source_unit_tests = f"{directory_template_files}/{filename_source_unit_tests}"

    # create target filename
    filename_target_unit_tests           = f"Test_LIB{library_abbreviation.upper()}Version.cpp"
    filename_with_path_target_unit_tests = f"{directory_library}/testing/google_test/source_code/{filename_target_unit_tests}"

    # copy template
    shutil.copy2(filename_with_path_source_unit_tests, filename_with_path_target_unit_tests)

    # replace information in target file
    replace_library_name(filename_with_path_target_unit_tests, search_string_library_abbreviation, library_abbreviation)
    replace_library_name(filename_with_path_target_unit_tests, search_string_library_abbreviation_uppercase, library_abbreviation.upper())


# run script
if __name__ == "__main__":
    # parse command line arguments
    parser = argparse.ArgumentParser(description="Script to prepare the version class of a library.")

    parser.add_argument("--directory_template_files",
                        required=False,
                        default="./templates/",
                        help="Path to the directory containing the template files.")
    parser.add_argument("--directory_library",
                        required=True,
                        help="Base directory of the library.")
    parser.add_argument("--library_abbreviation",
                        required=True,
                        help="Abbreviation of the library.")

    args = parser.parse_args()

    # prepare library version class
    prepare_library_version_class(args.directory_template_files, args.directory_library, args.library_abbreviation)

    # prepare library version class unit tests
    prepare_library_version_class_unit_tests(args.directory_template_files, args.directory_library, args.library_abbreviation)
