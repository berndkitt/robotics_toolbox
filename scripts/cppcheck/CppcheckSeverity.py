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

"""Class to represent the Cppcheck severities."""
from enum import Enum

from . import CppcheckSeverity


class CppcheckSeverity(Enum):
    """Class to represent the Cppcheck severities."""

    ERROR       = 1
    WARNING     = 2
    STYLE       = 3
    PERFORMANCE = 4
    PORTABILITY = 5
    INFORMATION = 6

    @staticmethod
    def get_severity_as_string(cppcheck_severity: CppcheckSeverity) -> str:
        """
        Getter for the Cppcheck severity as string.

        Args:
            cppcheck_severity (CppcheckSeverity): Cppcheck severity.

        Returns:
            str: Cppcheck severity as string.
        """
        severity_as_string = ""

        if cppcheck_severity == CppcheckSeverity.ERROR:
            severity_as_string = "Error"
        elif cppcheck_severity == CppcheckSeverity.WARNING:
            severity_as_string = "Warning"
        elif cppcheck_severity == CppcheckSeverity.STYLE:
            severity_as_string = "Style"
        elif cppcheck_severity == CppcheckSeverity.PERFORMANCE:
            severity_as_string = "Performance"
        elif cppcheck_severity == CppcheckSeverity.PORTABILITY:
            severity_as_string = "Portability"
        elif cppcheck_severity == CppcheckSeverity.INFORMATION:
            severity_as_string = "Information"
        else:
            return "Severity unknown."

        return severity_as_string

    def get_severity_from_string(cppcheck_severity: str) -> CppcheckSeverity:
        """
        Getter for the Cppcheck severity.

        Args:
            cppcheck_severity (str): Cppcheck severity as string.

        Returns:
            CppcheckSeverity: Cppcheck severity.
        """
        severity = None

        if cppcheck_severity == "error":
            severity = CppcheckSeverity.ERROR
        elif cppcheck_severity == "warning":
            severity = CppcheckSeverity.WARNING
        elif cppcheck_severity == "style":
            severity = CppcheckSeverity.STYLE
        elif cppcheck_severity == "performance":
            severity = CppcheckSeverity.PERFORMANCE
        elif cppcheck_severity == "portability":
            severity = CppcheckSeverity.PORTABILITY
        elif cppcheck_severity == "information":
            severity = CppcheckSeverity.INFORMATION
        else:
            pass

        return severity
