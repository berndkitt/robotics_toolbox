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

"""Class to represent test verdicts."""
from enum import Enum

from . import TestVerdict


class TestVerdict(Enum):
    """Class to represent test verdicts."""

    PASSED = 1
    FAILED = 2
    NOT_EXECUTED = 3

    @staticmethod
    def calculate_test_verdict(actual_value:  int,
                               allowed_value: int) -> TestVerdict:
        """
        Calculate the test verdict.

        Args:
            actual_value (int):  Actual value.
            allowed_value (int): Maximum allowed value.

        Returns:
            TestVerdict: Test verdict.
        """
        if actual_value <= allowed_value:
            return TestVerdict.PASSED
        else:
            return TestVerdict.FAILED

    @staticmethod
    def get_test_verdict_as_string(test_verdict: TestVerdict) -> str:
        """
        Getter for the test verdict as string.

        Args:
            test_verdict (TestVerdict): Test verdict.

        Returns:
            str: Test verdict as string.
        """
        if test_verdict == TestVerdict.PASSED:
            return "Passed"
        elif test_verdict == TestVerdict.FAILED:
            return "Failed"
        elif test_verdict == TestVerdict.NOT_EXECUTED:
            return "Not executed"
        else:
            return "Unknown"
