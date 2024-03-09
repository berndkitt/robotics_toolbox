"""Class to run parse the Cppcheck results."""
import os
import xml.etree.ElementTree as ET

from . import CppcheckError
from . import CppcheckErrorList


class CppcheckResultsParser:
    """Class to run parse the Cppcheck results."""

    def __init__(self,
                 base_directory: str) -> None:
        """
        Initialize Cppcheck results parser.

        Args:
            base_directory (str):  Base directory.
        """
        # set attributes
        self._base_directory             = base_directory
        self._entity_name                = os.path.basename(os.path.normpath(self._base_directory))
        self._directory_cppcheck_results = f"{self._base_directory}testing/cppcheck/results/"
        self._filename_results_with_path = f"{self._directory_cppcheck_results}{self._entity_name}_results.xml"
        self._error_list                 = CppcheckErrorList.CppcheckErrorList()

    def get_error_list(self) -> CppcheckErrorList.CppcheckErrorList:
        """
        Getter for the Cppcheck error list.

        Returns:
            CppcheckErrorList.CppcheckErrorList: Cppcheck error list.
        """
        return self._error_list

    def parse_results(self) -> None:
        """Parse Cppcheck results."""
        # parse XML file
        xml_tree = ET.parse(self._filename_results_with_path)
        xml_root = xml_tree.getroot()

        # extract error information
        for current_error in xml_root.findall("errors/error"):
            error_id       = current_error.get("id")
            error_severity = current_error.get("severity")
            error_message  = current_error.get("msg")
            error_verbose  = current_error.get("verbose")
            error_cwe      = current_error.get("cwe")

            error_file0  = None
            error_file   = None
            error_line   = None
            error_column = None

            error_location = current_error.find("location")

            if error_location is not None:  # error location is not present for all errors
                error_file   = error_location.get("file")
                error_line   = error_location.get("line")
                error_column = error_location.get("column")

                try:  # file0 is not present for all errors
                    error_file0 = error_location.get("file0")
                except KeyError:
                    pass

            current_cppcheck_error = CppcheckError.CppcheckError(error_id,
                                                                 error_severity,
                                                                 error_message,
                                                                 error_verbose,
                                                                 self.__convert_string_to_int(error_cwe),
                                                                 error_file0,
                                                                 error_file,
                                                                 self.__convert_string_to_int(error_line),
                                                                 self.__convert_string_to_int(error_column))

            self._error_list.add_error(current_cppcheck_error)

    @staticmethod
    def __convert_string_to_int(string: str) -> int:
        """Convert string to integer."""
        return_value = None

        if string:
            return_value = int(string)

        return return_value
