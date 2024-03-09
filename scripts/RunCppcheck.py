"""
Script to run Cppcheck.

The script runs Cppcheck on a list of files and parses the analysis results.

Args:
    base_directory (str):              Base directory.
    configuration_xml (str):           Filename of the configuration including its path.
    check_configuration (bool):        Flag to check the Cppcheck configuration.
    cppcheck_configuration_json (str): Filename of the Cppcheck configuration including its path.
    filename_report (str):             Filename of the Cppcheck test report including its path.
"""
import argparse

from cppcheck import CppcheckAnalyzer
from cppcheck import CppcheckResultsParser

from test_report_generators import TestReportGeneratorCppcheck


# run script
if __name__ == "__main__":
    # parse command line arguments
    parser = argparse.ArgumentParser(description="Script to run Cppcheck.")

    parser.add_argument("--base_directory",
                        required=False,
                        default="./modules/environment_modeling/libraries/libWPG/",
                        help="Base directory.")
    parser.add_argument("--configuration_xml",
                        required=False,
                        default="./modules/environment_modeling/libraries/libWPG/testing/cppcheck/libWPG.xml",
                        help="Filename of the configuration including its path.")
    parser.add_argument("--check_configuration",
                        required=False,
                        default=False,
                        action="store_true",
                        help="Flag to check the Cppcheck configuration.")
    parser.add_argument("--cppcheck_configuration_json",
                        required=False,
                        default="./cppcheck_configuration.json",
                        help="Filename of the Cppcheck configuration including its path.")
    parser.add_argument("--filename_report",
                        required=False,
                        default="",
                        help="Filename of the Cppcheck test report including its path.")

    args = parser.parse_args()

    # create Cppcheck analyzer and Cppcheck results parser
    cppcheck_analyzer       = CppcheckAnalyzer.CppcheckAnalyzer(args.base_directory, args.configuration_xml, args.check_configuration)
    cppcheck_results_parser = CppcheckResultsParser.CppcheckResultsParser(args.base_directory)

    # run Cppcheck analysis
    cppcheck_analyzer.analyze()

    # parse Cppcheck results
    cppcheck_results_parser.parse_results()

    # create Cppcheck test report generator
    test_report_generator_cppcheck = TestReportGeneratorCppcheck.TestReportGeneratorCppcheck(args.cppcheck_configuration_json, cppcheck_results_parser.get_error_list())

    # print test report on console
    test_report_generator_cppcheck.print_report_on_console(True)

    # write test report to file
    if args.filename_report:
        test_report_generator_cppcheck.write_report_to_file(args.filename_report, True)

    # return number of failed tests as exit code
    exit(test_report_generator_cppcheck.get_number_of_failed_tests())
