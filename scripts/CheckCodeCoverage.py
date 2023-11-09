"""
Script to compare the code coverage values against thresholds.

The script takes as input a file containing the summary from Gcovr and compares the branch
coverage, the file coverage as well as the line coverage against provided thresholds.

In case that any of the coverage values does not meet the expected threshold the script
returns a value not equal to 0.

The return value will be the sum of the following values (only values for failed checks
will be summed up)
- Branch coverage:   1
- Function coverage: 2
- Line coverage:     4

Args:
    filename_gcovr_summary (str):        Name of the file including its path which contains the Gcovr summary.
    threshold_branch_coverage (float):   Minimum percentage for the branch coverage.
    threshold_function_coverage (float): Minimum percentage for the function coverage.
    threshold_line_coverage (float):     Minimum percentage for the line coverage.
"""
import argparse
import json

# run script
if __name__ == "__main__":
    # parse command line arguments
    argument_parser = argparse.ArgumentParser(description="Script to check the code coverage.")

    argument_parser.add_argument("-is",
                                 "--filename_gcovr_summary",
                                 type=str,
                                 help="Name of the file including its path which contains the Gcovr summary.",
                                 required=True)
    argument_parser.add_argument("-tb",
                                 "--threshold_branch_coverage",
                                 type=float,
                                 help="Minimum percentage for the branch coverage.",
                                 default=100.0)
    argument_parser.add_argument("-tf",
                                 "--threshold_function_coverage",
                                 type=float,
                                 help="Minimum percentage for the function coverage.",
                                 default=100.0)
    argument_parser.add_argument("-tl",
                                 "--threshold_line_coverage",
                                 type=float,
                                 help="Minimum percentage for the line coverage.",
                                 default=100.0)

    args = argument_parser.parse_args()

    # check coverage
    return_value = 0

    with open(args.filename_gcovr_summary) as gcovr_summary_file:
        gcovr_summary_data = json.load(gcovr_summary_file)

        # extract coverage data
        branch_coverage   = gcovr_summary_data["branch_percent"]
        function_coverage = gcovr_summary_data["function_percent"]
        line_coverage     = gcovr_summary_data["line_percent"]

        # compare coverage against thresholds
        if branch_coverage < args.threshold_branch_coverage:
            return_value += 1
        if function_coverage < args.threshold_function_coverage:
            return_value += 2
        if line_coverage < args.threshold_line_coverage:
            return_value += 4

        print("Branch coverage: "   + str(branch_coverage) + " %")
        print("Function coverage: " + str(function_coverage) + " %")
        print("Line coverage: "     + str(line_coverage) + " %")

    exit(return_value)
