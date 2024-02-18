import argparse

from metrixplusplus import MetrixPlusPlusAnalyzer
from metrixplusplus import MetrixPlusPlusResultsParser


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

    args = parser.parse_args()

    # create Metrix++ analyzer and Metrix++ results parser
    metrixplusplus_analyzer       = MetrixPlusPlusAnalyzer.MetrixPlusPlusAnalyzer(args.base_directory, args.configuration_json)
    metrixplusplus_results_parser = MetrixPlusPlusResultsParser.MetrixPlusPlusResultsParser(args.base_directory)

    # run Metrix++ analysis
    metrixplusplus_analyzer.analyze()

    # parse Metrix++ results
    metrixplusplus_results_parser.parse_results()
