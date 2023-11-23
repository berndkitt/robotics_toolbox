"""
Script to generate the Doxygen documentation.

The script generated the Doxygen documentation for an entity and creates a ZIP file containing the
HTML and LaTeX version of the documentation.

The warning file from Doxygen is also checked for warnings. The number of warnings found is
returned.

Args:
    base_path (str):   Base path.
    entity (str):      Name of the entity.
    output_path (str): Absolute output path for the resulting ZIP file.
"""

import argparse
import os
import shutil

# run script
if __name__ == "__main__":
    # create parser for the command line arguments
    argument_parser = argparse.ArgumentParser(description="Script to create the Doxygen documentation.")

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
                                 help="Absolute output path for the resulting ZIP file.",
                                 required=True)

    args = argument_parser.parse_args()

    # get documentation directory of the entity to report
    documentation_directory = os.path.join(args.base_path, args.entity, "documentation")

    # go to documentation directory
    os.chdir(documentation_directory)

    # run Doxygen
    doxygen_configuration_file = args.entity + "_Doxyfile"
    os.system("doxygen " + doxygen_configuration_file)

    # open warning log file of Doxygen
    doxygen_warning_log_file = "DoxygenWarnings.log"
    doxygen_log_file = open(doxygen_warning_log_file, "r")

    # parse warning log file of Doxygen and collect information
    number_of_warnings_in_log = 0

    for current_line in doxygen_log_file:
        if not current_line.find("warning:") == -1:
            number_of_warnings_in_log = number_of_warnings_in_log + 1

    # close warning log file of Doxygen
    doxygen_log_file.close()

    # copy zipped version of the documentation into output directory
    filename_with_path_zip = args.output_path + "doxygen_" + args.entity

    shutil.make_archive(filename_with_path_zip, "zip", "./")

    # print number of found warnings
    print("Doxygen used " + doxygen_configuration_file + " in " + documentation_directory + ".")
    print("Analyzed Doxygen log file: " + doxygen_warning_log_file)
    print("Number of warnings found in Doxygen log file: " + str(number_of_warnings_in_log))

    # return number of found warnings as exit code
    exit(number_of_warnings_in_log)
