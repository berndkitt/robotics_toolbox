# This file is part of the Robotics Toolbox.

# Copyright (C) 2023

# Authors: Bernd Kitt (b.kitt@berndkitt.de)

# The Robotics Toolbox is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 3 of the License,
# or any later version.

# The Robotics Toolbox is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
# Public License for more details.

# You should have received a copy of the GNU General Public License along with
# the Robotics Toolbox. If not, see https://www.gnu.org/licenses/.

"""
Script to run a license header check.

The script runs a license header check on a list of files. The files are checked for a valid license
header.

Args:
    base_directory (str):     Base directory.
    configuration_json (str): Filename of the configuration including its path.
    log_level (str):          Level for logging data.
"""
import argparse
import logging
import pathlib

from file_collector import FileCollector

LOG_LEVELS = {"debug": logging.DEBUG,
              "info": logging.INFO,
              "warning": logging.WARNING,
              "error": logging.ERROR,
              "critical": logging.CRITICAL}


def parse_arguments() -> argparse.Namespace:
    """
    Parse the command line arguments.

    Returns:
        argparse.Namespace: Namespace containing the command line arguments.
    """
    parser = argparse.ArgumentParser(description="Script to run the license header check.")

    parser.add_argument("--base_directory",
                        required=False,
                        default="./",
                        help="Base directory.")
    parser.add_argument("--configuration_json",
                        required=False,
                        default="./configuration.json",
                        help="Filename of the configuration including its path.")
    parser.add_argument("--log_level",
                        type=str,
                        help="Logging level.",
                        choices=LOG_LEVELS.keys(),
                        default="info",
                        required=False)

    args = parser.parse_args()

    return args


def check_file_for_license_header(filename: pathlib.Path,
                                  string_to_check: str = "GNU General Public License") -> bool:
    """
    Check whether the license header is present in a file.

    Args:
        filename (pathlib.Path):         Filename including its path.
        string_to_check (str, optional): String to search for. Defaults to "GNU General Public License".

    Returns:
        bool: _description_
    """
    is_license_header_present = False

    with open(filename, "r", encoding="utf-8") as file:
        lines = file.readlines()

        for current_line in lines:
            if current_line.find(string_to_check) != -1:
                is_license_header_present = True
                break

    return is_license_header_present


if __name__ == "__main__":
    args = parse_arguments()
    logging.basicConfig(level=LOG_LEVELS[args.log_level])

    collector = FileCollector.FileCollector(args.configuration_json, args.base_directory)

    list_of_files = collector.get_list_of_files()

    number_of_files_without_license_header = 0
    list_of_files_without_license_header = []

    for current_file in list_of_files:
        logging.debug(f"Checking {current_file} for presence of a license header.")

        is_license_header_present = check_file_for_license_header(current_file)

        if not is_license_header_present:
            logging.info(f"No license header found in {current_file}.")
            number_of_files_without_license_header += 1

    logging.info(f"Found {number_of_files_without_license_header} files without a license header.")

    exit(number_of_files_without_license_header)
