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

"""Class to represent a Cppcheck error."""
from . import CppcheckSeverity


class CppcheckError:
    """Class to represent a Cppcheck error."""

    def __init__(self,
                 error_id:    str,
                 severity:    str,
                 message:     str,
                 verbose:     str,
                 cwe:         int,
                 error_file0: str,
                 error_file:  str,
                 line:        int,
                 column:      str) -> None:
        """
        Initialize a Cppcheck error.

        Args:
            error_id (str):    Error ID.
            severity (str):    Severity.
            message (str):     Message.
            verbose (str):     Verbose text.
            cwe (int):         CWE ID.
            error_file0 (str): Filename.
            error_file (str):  Filename.
            line (int):        Line number.
            column (str):      Column number.
        """
        self.__error_id    = error_id
        self.__severity    = CppcheckSeverity.CppcheckSeverity.get_severity_from_string(severity)
        self.__message     = message
        self.__verbose     = verbose
        self.__cwe         = cwe
        self.__error_file0 = error_file0
        self.__error_file  = error_file
        self.__line        = line
        self.__column      = column

    def get_severity(self) -> CppcheckSeverity.CppcheckSeverity:
        """
        Getter for the Cppcheck severity.

        Returns:
            CppcheckSeverity.CppcheckSeverity: Cppcheck severity.
        """
        return self.__severity

    def print_error(self) -> None:
        """Print error information for a Cppcheck error."""
        message_to_print = ""

        if self.__error_file:
            # map severity level for Visual Studio Code problem matcher (all severity levels but ERROR and WARNING will be mapped to "info")
            if self.__severity == CppcheckSeverity.CppcheckSeverity.ERROR:
                problem_matcher_severity = "error"
            elif self.__severity == CppcheckSeverity.CppcheckSeverity.WARNING:
                problem_matcher_severity = "warning"
            else:
                problem_matcher_severity = "info"

            message_to_print = f"{self.__error_file}:{self.__line}:{self.__column}:{problem_matcher_severity} Cppcheck: {self.__message} ({CppcheckSeverity.CppcheckSeverity.get_severity_as_string(self.__severity)})"
        else:
            message_to_print = f"Cppcheck: {self.__message}"

        print(message_to_print)
