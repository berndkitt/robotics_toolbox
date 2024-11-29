"""Module containing the LibraryInformation class."""
import json
import pathlib


class LibraryInformation:
    """Class containing the library information."""

    def __init__(self,
                 path_to_library: pathlib.Path) -> None:
        """
        Initialize the library information.

        Args:
            path_to_library (pathlib.Path): Path to the library.
        """
        self.__path_to_library = path_to_library

        self.__read_library_information_from_file()

    def get_library_abbreviation(self) -> str:
        """
        Getter for the abbreviation of the library.

        Returns:
            str: Abbreviation of the library.
        """
        return self.__abbreviation

    def get_library_name(self) -> str:
        """
        Getter for the name of the library.

        Returns:
            str: Name of the library.
        """
        return self.__name

    def get_path_to_doxyfile(self) -> pathlib.Path:
        """
        Getter for the path to the Doxyfile.

        Returns:
            pathlib.Path: Path to the Doxyfile.
        """
        return pathlib.Path.joinpath(self.__path_to_library,
                                     "documentation",
                                     f"lib{self.get_library_abbreviation()}_Doxyfile")

    def get_path_to_file_list(self) -> pathlib.Path:
        """
        Getter for the path to the versioning file list.

        Returns:
            pathlib.Path: Path to the versioning file list.
        """
        return pathlib.Path.joinpath(self.__path_to_library,
                                     "versioning",
                                     "list_files.xml")

    def get_path_to_fingerprint_file(self) -> pathlib.Path:
        """
        Getter for the path to the versioning fingerprint file.

        Returns:
            pathlib.Path: Path to the versioning fingerprint file.
        """
        return pathlib.Path.joinpath(self.__path_to_library,
                                     "versioning",
                                     f"lib{self.get_library_abbreviation()}_Fingerprints.txt")

    def get_path_to_library(self) -> pathlib.Path:
        """
        Getter for the path of the library.

        Returns:
            pathlib.Path: Path of the library.
        """
        return self.__path_to_library

    def get_path_to_version_file_cpp(self) -> pathlib.Path:
        """
        Getter for the path to the version information source file.

        Returns:
            pathlib.Path: Path to the version information source file.
        """
        return pathlib.Path.joinpath(self.__path_to_library,
                                     "source_code",
                                     "src",
                                     f"LIB{self.get_library_abbreviation()}Version.cpp")

    def get_path_to_version_file_h(self) -> pathlib.Path:
        """
        Getter for the path to the version information header file.

        Returns:
            pathlib.Path: Path to the version information header file.
        """
        return pathlib.Path.joinpath(self.__path_to_library,
                                     "source_code",
                                     "include",
                                     f"LIB{self.get_library_abbreviation()}Version.h")

    def get_path_to_version_header_file(self) -> pathlib.Path:
        """
        Getter for the path to the versioning version header file.

        Returns:
            pathlib.Path: Path to the versioning version header file.
        """
        return pathlib.Path.joinpath(self.__path_to_library,
                                     "versioning",
                                     f"lib{self.get_library_abbreviation()}_Version.h")

    def get_path_to_version_list(self) -> pathlib.Path:
        """
        Getter for the path to the version list.

        Returns:
            pathlib.Path: Path to the version list.
        """
        return pathlib.Path.joinpath(self.__path_to_library,
                                     "versioning",
                                     "list_versions.xml")

    def get_path_to_version_unit_tests_file_cpp(self) -> pathlib.Path:
        """
        Getter for the path to the version information unit test source file.

        Returns:
            pathlib.Path: Path to the version information unit test source file.
        """
        return pathlib.Path.joinpath(self.__path_to_library,
                                     "testing",
                                     "google_test",
                                     "source_code",
                                     f"Test_LIB{self.get_library_abbreviation().upper()}Version.cpp")

    def __read_library_information_from_file(self) -> None:
        path_to_library_information = pathlib.Path.joinpath(self.__path_to_library,
                                                            "LibraryInformation.json")
        with open(path_to_library_information, "r") as json_file:
            library_information = json.load(json_file)

            self.__abbreviation = library_information["abbreviation"]
            self.__name         = library_information["name"]
