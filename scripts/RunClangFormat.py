"""
Script to run Clang-Format.

The script runs Clang-Format on a list of files provided as configuration file. In case that the
command line argument "dry_run" is not set, the formatting is applied in the files. In case that
"dry_run" is set, the changes will not be applied. If changes should be made, the return code of
the script is not equal to 0.

Args:
    base_directory (str):     Base directory.
    configuration_json (str): Filename of the configuration including its path.
    dry_run (bool):           Do not apply the changes but print them on the console.
"""

import argparse
import subprocess

from file_collector import FileCollector

# run script
if __name__ == "__main__":
    # parse command line arguments
    parser = argparse.ArgumentParser(description="Script to run Clang-Format.")

    parser.add_argument("--base_directory",
                        required=False,
                        default="./",
                        help="Base directory.")
    parser.add_argument("--configuration_json",
                        required=False,
                        default="./configuration.json",
                        help="Filename of the configuration including its path.")
    parser.add_argument("--dry_run",
                        required=False,
                        default=False,
                        action="store_true",
                        help="Do not apply the changes but print them on the console.")

    args = parser.parse_args()

    # get list of files to check
    files = FileCollector.FileCollector(args.configuration_json, args.base_directory)

    # run Clang-Format for all files
    return_code = 0
    list_of_files = files.get_list_of_files_as_string()

    if args.dry_run:
        clang_format_call = f"clang-format -- dry-run -Werror {list_of_files}"
    else:
        clang_format_call = f"clang-format -i {list_of_files}"

    if len(list_of_files) > 0:
        output = subprocess.run(clang_format_call, shell=True)
        return_code = output.returncode

    exit(return_code)
