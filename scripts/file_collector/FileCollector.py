"""Module to to create a list of files."""

import json
import os
from typing import List


class FileCollector():
    """
    Class to collect a list of files.

    The class can be used to create a list of files including their paths based on a configuration
    file.
    """

    def __init__(self,
                 configuration_file: str,
                 base_directory: str) -> None:
        """
        Initialize the file collector.

        Args:
            configuration_file (str): Name of the configuration file including its path.
            base_directory (str):     Base directory.
        """
        self._base_directory = base_directory
        self._list_of_files = set()

        with open(configuration_file) as configuration_json:
            # read data from configuration file
            configuration = json.load(configuration_json)

            self._extensions = configuration["extensions"]
            self._directories = [os.path.join(self._base_directory, directory) for directory in configuration["directories"]]
            self._files_included = [os.path.join(self._base_directory, file) for file in configuration["files_included"]]
            self._files_excluded = [os.path.join(self._base_directory, file) for file in configuration["files_excluded"]]

            # check configuration
            self._check_configuration()

            # extract the list of files
            self._list_of_files = self._extract_files()

    def get_list_of_files_as_string(self) -> str:
        """
        Return the list of files as string (separated by blanks).

        Returns:
            str: List of files as string.
        """
        files_as_string = ""

        for current_file in self._list_of_files:
            files_as_string = files_as_string + current_file + " "

        files_as_string.strip()

        return files_as_string

    def _check_configuration(self) -> None:
        """
        Check the configuration.

        Raises:
            Exception: Raised in case that the include and exclude list contain the same files.
            Exception: Raised in case a directory does not exist.
            Exception: Raised in case that a file in the include list does not exist.
        """
        # check for files in include and exclude list
        files_include_exclude = set(self._files_included).intersection(self._files_excluded)

        if len(files_include_exclude) > 0:
            raise Exception("Included and excluded files are identical.")

        # check whether all directories exist
        for directory in self._directories:
            if not os.path.exists(directory):
                raise Exception(f"Directory {directory} does not exist.")

        # check whether all include files exist
        for current_file in self._files_included:
            if not os.path.exists(current_file):
                raise Exception(f"File {current_file} does not exist.")

    def _extract_files(self) -> List[str]:
        """
        Extract the list of files in the specified directories.

        Returns:
            List[str]: List of files including their paths.
        """
        files = self._search_files_in_directories(self._directories)
        files = set(files + self._files_included) - set(self._files_excluded)
        files = sorted(files)

        return files

    def _search_files_in_directories(self,
                                     directories: List[str]) -> List[str]:
        """
        Search for all relevant files in the specified directories.

        Args:
            directories (List[str]): List of directories to check.

        Returns:
            List[str]: List of files found including their paths.
        """
        list_of_files = []

        for current_directory in directories:
            for root, _, files in os.walk(current_directory):
                for current_file in files:
                    file_with_path = root + os.sep + current_file

                    has_extension = [extension for extension in self._extensions if file_with_path.endswith(extension)]

                    if len(has_extension) > 0:
                        list_of_files.append(os.path.join(root, current_file))

        return list_of_files
