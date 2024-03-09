"""Class to represent a list of Cppcheck errors."""
from . import CppcheckError
from . import CppcheckSeverity


class CppcheckErrorList:
    """Class to represent a list of Cppcheck errors."""

    def __init__(self) -> None:
        """Initialize an empty error list."""
        self.__number_of_errors = 0
        self.__error_list       = []

    def add_error(self,
                  error: CppcheckError.CppcheckError) -> None:
        """Add a Cppcheck error to the list.

        Args:
            message (CppcheckError.CppcheckError): Cppcheck error.
        """
        self.__number_of_errors += 1
        self.__error_list.append(error)

    def print_all_errors(self) -> None:
        """Print all errors."""
        for current_error in self.__error_list:
            current_error.print_error()

    def print_errors(self,
                     cppcheck_severity: CppcheckSeverity.CppcheckSeverity) -> None:
        """
        Print all errors for a given Cppcheck severity.

        Args:
            cppcheck_severity (CppcheckSeverity.CppcheckSeverity): Cppcheck severity.
        """
        for current_error in self.__error_list:
            if current_error.get_severity() == cppcheck_severity:
                current_error.print_error()
