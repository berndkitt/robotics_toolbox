# This file is part of the Robotics Toolbox.

# Copyright (C) 2026

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

    def get_number_of_errors_by_severity(self,
                                         cppcheck_severity: CppcheckSeverity.CppcheckSeverity) -> int:
        """
        Getter for the number of errors for a given Cppcheck severity.

        Args:
            cppcheck_severity (CppcheckSeverity.CppcheckSeverity): Cppcheck severity.

        Returns:
            int: Number of errors for the given Cppcheck severity.
        """
        number_of_errors = 0

        for current_error in self.__error_list:
            current_severity = current_error.get_severity()

            if current_severity == cppcheck_severity:
                number_of_errors += 1

        return number_of_errors

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
