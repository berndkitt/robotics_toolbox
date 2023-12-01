"""
Script to run Clang-Tidy.

The script runs Clang-Tidy and writes the warnings into a file.

The warning file from Clang-Tidy is also checked for warnings. The number of warnings found is
returned.

Args:
    output_path (str): Absolute output path for the results file.
"""

import argparse
import os
from pathlib import Path

# run script
if __name__ == "__main__":
    # parse command line arguments
    argument_parser = argparse.ArgumentParser(description="Script to run Clang-Tidy.")

    argument_parser.add_argument("-o",
                                 "--output_path",
                                 type=str,
                                 help="Absolute output path for the results file.",
                                 required=True)

    args = argument_parser.parse_args()

    # get list of files
    directories_to_check = ["common", "modules"]
    list_of_files        = []
    string_list_of_files = ""

    for current_directory in directories_to_check:
        for path in Path(current_directory).rglob("*.cpp"):
            list_of_files.append(str(path))
            string_list_of_files = string_list_of_files + " " + str(path)

    # run Clang-Tidy
    output_file_with_path = args.output_path + "clang_tidy_results.txt"

    os.system("clang-tidy " + string_list_of_files + " --extra-arg=-std=c++17 -- -I ./common -I /usr/local/include/eigen3 -I /usr/local/include/opencv4 > " + output_file_with_path)

    # open output file
    clang_tidy_results_file = open(output_file_with_path, "r")

    # parse output file and collect information
    number_of_warnings = 0

    for current_line in clang_tidy_results_file:
        for current_file in list_of_files:
            if current_file in current_line and not current_line.find(": warning:") == -1:
                number_of_warnings = number_of_warnings + 1

    # close output file
    clang_tidy_results_file.close()

    # print number of found warnings
    print("Analyzed file: " + output_file_with_path)
    print("Number of warnings found: " + str(number_of_warnings))

    # return number of found warnings as exit code
    exit(number_of_warnings)
