"""
Script to run Clang-Tidy.

The script runs Clang-Tidy and writes the warnings into a file.

The warning file from Clang-Tidy is also checked for warnings. The number of warnings found is
returned.

Args:
    output_path (str): Absolute output path for the results file.
"""

import argparse
import re
import subprocess

from file_collector import FileCollector

# run script
if __name__ == "__main__":
    # parse command line arguments
    argument_parser = argparse.ArgumentParser(description="Script to run Clang-Tidy.")

    argument_parser.add_argument("--base_directory",
                                 required=False,
                                 default="./",
                                 help="Base directory.")
    argument_parser.add_argument("--configuration_json",
                                 required=False,
                                 default="./configuration.json",
                                 help="Filename of the configuration including its path.")

    args = argument_parser.parse_args()

    # get list of files to check
    files = FileCollector.FileCollector(args.configuration_json, args.base_directory)

    # run Clang-Tidy for all files
    list_of_files         = files.get_list_of_files_as_string()
    extra_arguments       = "--extra-arg=-std=c++17"
    include_directories   = "-I ./common -I /usr/local/include/eigen3 -I /usr/local/include/opencv4"

    clang_format_call = f"clang-tidy {list_of_files} {extra_arguments} -- {include_directories}"

    output = subprocess.run(clang_format_call, shell=True, capture_output=True, text=True)

    # parse results file and collect information
    number_of_warnings = 0

    for current_line in output.stdout.split("\n"):
        for current_file in files.get_list_of_files():
            current_file_until_slash = re.sub(r"^.*?/", "/", current_file)  # removes all characters until the first "/"

            if current_file_until_slash in current_line:
                print(current_line)  # needed for Visual Studio Code Problem Matcher

                if not current_line.find(": warning:") == -1:
                    number_of_warnings = number_of_warnings + 1

    print("Number of warnings found: " + str(number_of_warnings))

    # return number of found warnings as exit code
    exit(number_of_warnings)
