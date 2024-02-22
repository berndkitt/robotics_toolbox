"""
Script to run Metrix++.

The script runs Metrix++ on a list of files and parses the analysis results.

Args:
    base_directory (str):                    Base directory.
    configuration_json (str):                Filename of the configuration including its path.
    metrixplusplus_configuration_json (str): Filename of the Metrix++ configuration including its path.
    filename_report (str):                   Filename of the Metrix++ test report including its path.
"""
import argparse

from metrixplusplus import MetrixPlusPlusAnalyzer
from metrixplusplus import MetrixPlusPlusResultsParser

from test_report_generators import TestReportGeneratorMetrixPlusPlus


# run script
if __name__ == "__main__":
    # parse command line arguments
    parser = argparse.ArgumentParser(description="Script to run Metrix++.")

    parser.add_argument("--base_directory",
                        required=False,
                        default="./",
                        help="Base directory.")
    parser.add_argument("--configuration_json",
                        required=False,
                        default="./configuration.json",
                        help="Filename of the configuration including its path.")
    parser.add_argument("--metrixplusplus_configuration_json",
                        required=False,
                        default="./metrixplusplus_configuration.json",
                        help="Filename of the Metrix++ configuration including its path.")
    parser.add_argument("--filename_report",
                        required=False,
                        default="",
                        help="Filename of the Metrix++ test report including its path.")

    args = parser.parse_args()

    # create Metrix++ analyzer and Metrix++ results parser
    metrixplusplus_analyzer       = MetrixPlusPlusAnalyzer.MetrixPlusPlusAnalyzer(args.base_directory, args.configuration_json)
    metrixplusplus_results_parser = MetrixPlusPlusResultsParser.MetrixPlusPlusResultsParser(args.base_directory)

    # run Metrix++ analysis
    metrixplusplus_analyzer.analyze()

    # parse Metrix++ results
    metrixplusplus_results_parser.parse_results()

    # create Metrix++ test report generator
    test_report_generator_metrixplusplus = TestReportGeneratorMetrixPlusPlus.TestReportGeneratorMetrixPlusPlus(args.metrixplusplus_configuration_json, metrixplusplus_results_parser.get_message_list())

    # print test report on console
    test_report_generator_metrixplusplus.print_report_on_console(True)

    # write test report to file
    if args.filename_report:
        test_report_generator_metrixplusplus.write_report_to_file(args.filename_report, True)

    # return number of failed tests as exit code
    exit(test_report_generator_metrixplusplus.get_number_of_failed_tests())
