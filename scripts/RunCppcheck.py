"""
Script to run Cppcheck.

The script runs Cppcheck on a list of files and parses the analysis results.

Args:
    base_directory (str):       Base directory.
    configuration_xml (str):    Filename of the configuration including its path.
    check_configuration (bool): Flag to check the Cppcheck configuration.
"""
import argparse

from cppcheck import CppcheckAnalyzer
from cppcheck import CppcheckResultsParser


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

    args = parser.parse_args()

    # create Cppcheck analyzer and Cppcheck results parser
    cppcheck_analyzer       = CppcheckAnalyzer.CppcheckAnalyzer(args.base_directory, args.configuration_xml, args.check_configuration)
    cppcheck_results_parser = CppcheckResultsParser.CppcheckResultsParser(args.base_directory)

    # run Cppcheck analysis
    cppcheck_analyzer.analyze()

    # parse Cppcheck results
    cppcheck_results_parser.parse_results()
