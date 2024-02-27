"""
Script to run Clang-Tidy.

The script runs Clang-Tidy and writes the warnings into the console. The return code of the script
is th number of warnings found.

Either a single file can be analyzed using the --file argument or a list of files defined by a
configuration file provided by the --configuration_json argument can be analyzed.

Args:
    base_directory (str):     Base directory.
    file (str):               Filename of a single file including its path.
    configuration_json (str): Filename of the configuration including its path.
"""

import argparse
import re
import subprocess

from file_collector import FileCollector

# run script
if __name__ == "__main__":
    # parse command line arguments
    argument_parser = argparse.ArgumentParser(description="Script to run Clang-Tidy.")
    group = argument_parser.add_mutually_exclusive_group()

    argument_parser.add_argument("--base_directory",
                                 required=False,
                                 default="./",
                                 help="Base directory.")
    group.add_argument("--file",
                       required=False,
                       default="",
                       help="Filename of a single file including its path.")
    group.add_argument("--configuration_json",
                       required=False,
                       default="./configuration.json",
                       help="Filename of the configuration including its path.")

    args = argument_parser.parse_args()

    # get list of files to check
    if args.file:
        list_of_files           = [args.file]
        list_of_files_as_string = args.file
    else:
        files = FileCollector.FileCollector(args.configuration_json, args.base_directory)

        list_of_files           = files.get_list_of_files()
        list_of_files_as_string = files.get_list_of_files_as_string()

    print(list_of_files_as_string)

    # run Clang-Tidy for all files
    extra_arguments     = "--extra-arg=-std=c++17"
    include_directories = "-I ./common -I /usr/local/include/eigen3 -I /usr/local/include/opencv4"

    clang_format_call = f"clang-tidy {list_of_files_as_string} {extra_arguments} -- {include_directories}"

    output = subprocess.run(clang_format_call, shell=True, capture_output=True, text=True)

    # parse results and collect information
    number_of_warnings = 0

    for current_line in output.stdout.split("\n"):
        for current_file in list_of_files:
            current_file_until_slash = re.sub(r"^.*?/", "/", current_file)  # removes all characters until the first "/"

            if current_file_until_slash in current_line:
                print(current_line)  # needed for Visual Studio Code Problem Matcher

                if not current_line.find(": warning:") == -1:  # only count warnings
                    number_of_warnings = number_of_warnings + 1

    print("Number of warnings found: " + str(number_of_warnings))

    # return number of found warnings as exit code
    exit(number_of_warnings)
