"""Module containing the LibraryFinder class."""
import logging
import pathlib
import re

from . import LibraryInformation


class LibraryFinder:
    """
    LibraryFinder class.

    This class can be used to collect all libraries within the defined base path. The libraries are
    identified by their directory name. It is assumed that the libraries are in a directory
    following the pattern "libABC" where "ABC" consists of upper- and lowercase characters only. The
    number of characters in "ABC" is not relevant as long as it consists if one character or more.
    """

    def __init__(self,
                 base_path: str) -> None:
        """
        Initialize the library finder.

        Args:
            base_path (str): Base path to the libraries.
        """
        self.__base_path = pathlib.Path(base_path)
        self.__list_libraries = []

        self.__find_all_libraries()

    def get_library_information(self,
                                library_abbreviation: str) -> LibraryInformation.LibraryInformation:
        """
        Getter for the information of a library.

        This function returns the information of the library specified as input. In case the library
        is not found, the function returns none.

        Args:
            library_abbreviation (str): Abbreviation of the library.

        Returns:
            LibraryInformation.LibraryInformation: Information of the library.
        """
        library_information = None

        for current_library_information in self.__list_libraries:
            if current_library_information.get_library_abbreviation() == library_abbreviation:
                library_information = current_library_information
                break

        return library_information

    def __find_all_libraries(self) -> None:
        """
        Find all libraries within the defined base path.

        The libraries are identified by their directory name. It is assumed that the libraries are
        in a directory following the pattern "libABC" where "ABC" consists of upper- and lowercase
        characters only. The number of characters in "ABC" is not relevant as long as it consists if
        one character or more.
        Directories starting with any of the directories in the "ignore_directories" list will be
        ignored.
        """
        library_name_pattern = re.compile("lib[A-Z]+[a-z]*")
        ignore_directories   = [self.__base_path.joinpath("build")]

        for current_path in self.__base_path.rglob("**/lib*"):
            if library_name_pattern.fullmatch(current_path.name):
                for ignore_directory in ignore_directories:
                    if ignore_directory not in current_path.parents:
                        logging.info(f"Found library {current_path.name} in {current_path}.")
                        self.__list_libraries.append(LibraryInformation.LibraryInformation(current_path))
