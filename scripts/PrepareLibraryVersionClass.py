import argparse
import shutil


def replace_library_name(filename_with_path: str,
                         search_string:      str,
                         replace_str:        str) -> None:
    # read input file
    with open(filename_with_path, "r") as file_input:
        file_data = file_input.read()

        # update content
        file_data_updated = file_data.replace(search_string, replace_str)

    # write output file with updated content
    with open(filename_with_path, "w") as file_output:
        file_output.write(file_data_updated)


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
                        help="Base directory of the library")
    parser.add_argument("--library_abbreviation",
                        required=True,
                        help="Abbreviation of the library.")

    args = parser.parse_args()

    # define variables
    search_string_library_abbreviation           = "${LIB_ABBREVIATION}"
    search_string_library_abbreviation_uppercase = "${LIB_ABBREVIATION_UPPERCASE}"
    filename_source_header                       = "LIBVersion.h"
    filename_source_source                       = "LIBVersion.cpp"

    # create source filenames
    filename_with_path_source_header = f"{args.directory_template_files}/{filename_source_header}"
    filename_with_path_source_source = f"{args.directory_template_files}/{filename_source_source}"

    # create target filenames
    filename_target_header = f"LIB{args.library_abbreviation.upper()}Version.h"
    filename_target_source = f"LIB{args.library_abbreviation.upper()}Version.cpp"

    filename_with_path_target_header = f"{args.directory_library}/source_code/include/{filename_target_header}"
    filename_with_path_target_source = f"{args.directory_library}/source_code/src/{filename_target_source}"

    # copy template files to source library directory
    shutil.copy2(filename_with_path_source_header, filename_with_path_target_header)
    shutil.copy2(filename_with_path_source_source, filename_with_path_target_source)

    # replace information in target files
    replace_library_name(filename_with_path_target_header, search_string_library_abbreviation, args.library_abbreviation)
    replace_library_name(filename_with_path_target_header, search_string_library_abbreviation_uppercase, args.library_abbreviation.upper())
    replace_library_name(filename_with_path_target_source, search_string_library_abbreviation, args.library_abbreviation)
    replace_library_name(filename_with_path_target_source, search_string_library_abbreviation_uppercase, args.library_abbreviation.upper())
