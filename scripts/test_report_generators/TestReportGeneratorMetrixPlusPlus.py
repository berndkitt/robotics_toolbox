"""Test report generator for Metrix++."""
from metrixplusplus import MetrixPlusPlusMessageList
from metrixplusplus import MetrixPlusPlusMetric

from . import TestReportGeneratorBase


class TestReportGeneratorMetrixPlusPlus(TestReportGeneratorBase.TestReportGeneratorBase):
    """Test report generator for Metrix++."""

    def __init__(self,
                 metrixplusplus_configuration_json: str,
                 metrixplusplus_message_list:       MetrixPlusPlusMessageList.MetrixPlusPlusMessageList) -> None:
        """
        Initialize the Metrix++ test report generator.

        Args:
            metrixplusplus_configuration_json (str):                                           Filename of the Metrix++ configuration including its path.
            metrixplusplus_message_list (MetrixPlusPlusMessageList.MetrixPlusPlusMessageList): Metrix++ message list.
        """
        # initialize test report generator base
        TestReportGeneratorBase.TestReportGeneratorBase.__init__(self, metrixplusplus_configuration_json)

        self.__metrixplusplus_message_list = metrixplusplus_message_list

    def __get_maximum_value_from_settings(self,
                                          metrixplusplus_metrix: MetrixPlusPlusMetric.MetrixPlusPlusMetric) -> int:
        """
        Extract maximum allowed value for a metric from the configuration file.

        Args:
            metrixplusplus_metrix (MetrixPlusPlusMetric.MetrixPlusPlusMetric): Metrix++ metric.

        Returns:
            int: Maximum allowed value for the metric.
        """
        return self._test_configuration["Test"][MetrixPlusPlusMetric.MetrixPlusPlusMetric.get_metric_as_string(metrixplusplus_metrix)]["max_allowed_value"]

    def _print_test_report_core(self,
                                add_details: bool = False) -> None:
        """
        Print core test report on console.

        Args:
            add_details (bool, optional): Flag to add details. Defaults to False.
        """
        for current_metric in MetrixPlusPlusMetric.MetrixPlusPlusMetric:
            if add_details:
                maximum_allowed_value = self.__get_maximum_value_from_settings(current_metric)
                self.__metrixplusplus_message_list.print_messages(current_metric, maximum_allowed_value)

        self._run_tests()

    def _run_tests(self) -> None:
        """Run tests and print results on to console."""
        for current_metric in MetrixPlusPlusMetric.MetrixPlusPlusMetric:
            maximum_allowed_value = self.__get_maximum_value_from_settings(current_metric)
            maximum_value         = self.__metrixplusplus_message_list.get_maximum_value_for_metric(current_metric)

            if maximum_allowed_value <= maximum_value:
                self._number_of_failed_tests += 1

            self._print_results_line(MetrixPlusPlusMetric.MetrixPlusPlusMetric.get_metric_as_string(current_metric), maximum_value, maximum_allowed_value)
