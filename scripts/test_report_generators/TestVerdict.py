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
