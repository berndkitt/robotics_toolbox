"""
Script to compare the Doxygen coverage value against a threshold.

The script takes as input the Doxygen report in XML format and calculates the Doxygen coverage
using Coverxygen. Afterwards, the actual coverage is compared against a defined threshold.

In case the coverage value does not meet the expected threshold the script returns 1, otherwise it
returns 0.

Args:
    base_path (str):            Base path.
    entity (str):               Name of the entity.
    output_path (str):          Absolute output path for the Doxygen coverage report.
    threshold_coverage (float): Minimum percentage for the Doxygen coverage.
"""

import argparse
import json
import os

# run script
if __name__ == "__main__":
    # parse command line arguments
    argument_parser = argparse.ArgumentParser(description="Script to check the Doxygen coverage.")

    argument_parser.add_argument("-b",
                                 "--base_path",
                                 type=str,
                                 default="",
                                 help="Base path.",
                                 required=True)
    argument_parser.add_argument("-e",
                                 "--entity",
                                 type=str,
                                 default="",
                                 help="Name of the entity.",
                                 required=True)
    argument_parser.add_argument("-o",
                                 "--output_path",
                                 type=str,
                                 help="Absolute output path for the Doxygen coverage report.",
                                 required=True)
    argument_parser.add_argument("-t",
                                 "--threshold_coverage",
                                 type=float,
                                 help="Minimum percentage for the Doxygen coverage.",
                                 default=100.0)

    args = argument_parser.parse_args()

    # define directories and files
    source_code_directory   = os.path.join(args.base_path, args.entity)
    documentation_directory = os.path.join(args.base_path, args.entity, "documentation", "xml")
    report_file_with_path   = os.path.join(args.output_path, "coverxygen_" + args.entity + ".json")

    # call Coverxygen
    os.system("python3 -m coverxygen --xml-dir " + documentation_directory + " --src-dir " + source_code_directory + " --output " + report_file_with_path + " --format json-v3")

    # check coverage
    return_value = 0

    with open(report_file_with_path) as coverxygen_summary_file:
        report_content = json.load(coverxygen_summary_file)

        # extract coverage data
        doxygen_coverage = report_content["total"]["coverage_rate"] * 100.0

        # compare coverage against threshold
        if doxygen_coverage < args.threshold_coverage:
            return_value += 1

        print("Doxygen coverage: " + str(doxygen_coverage) + " %")

    exit(return_value)
