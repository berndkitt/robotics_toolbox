"""Test report generator for Cppcheck."""
from cppcheck import CppcheckErrorList
from cppcheck import CppcheckSeverity

from . import TestReportGeneratorBase


class TestReportGeneratorCppcheck(TestReportGeneratorBase.TestReportGeneratorBase):
    """Test report generator for Cppcheck."""

    def __init__(self,
                 cppcheck_configuration_json: str,
                 cppcheck_error_list:         CppcheckErrorList.CppcheckErrorList):
        """
        Initialize the Cppcheck test report generator.

        Args:
            cppcheck_configuration_json (str):                         Filename of the Cppcheck configuration including its path.
            cppcheck_error_list (CppcheckErrorList.CppcheckErrorList): Cppcheck error list.
        """
        # initialize test report generator base
        TestReportGeneratorBase.TestReportGeneratorBase.__init__(self, cppcheck_configuration_json)

        self.__cppcheck_error_list = cppcheck_error_list

    def __get_maximum_value_from_setting(self,
                                         cppcheck_severity: CppcheckSeverity.CppcheckSeverity) -> int:
        """
        Extract maximum allowed value for a severity from the configuration file.

        Args:
            cppcheck_severity (CppcheckSeverity.CppcheckSeverity): Cppcheck severity.

        Returns:
            int: Maximum allowed value for the severity.
        """
        return self._test_configuration["Test"][CppcheckSeverity.CppcheckSeverity.get_severity_as_string(cppcheck_severity)]["max_allowed_value"]

    def _print_test_report_core(self,
                                add_details: bool = False) -> None:
        """
        Print core test report on console.

        Args:
            add_details (bool, optional): Flag to add details. Defaults to False.
        """
        if add_details:
            self.__cppcheck_error_list.print_all_errors()

        self._run_tests()

    def _run_tests(self) -> None:
        """Run tests and print results on to console."""
        for current_severity in CppcheckSeverity.CppcheckSeverity:
            maximum_allowed_value = self.__get_maximum_value_from_setting(current_severity)
            current_value         = self.__cppcheck_error_list.get_number_of_errors_by_severity(current_severity)

            if current_value > maximum_allowed_value:
                self._number_of_failed_tests += 1

            self._print_results_line(CppcheckSeverity.CppcheckSeverity.get_severity_as_string(current_severity), current_value, maximum_allowed_value)
