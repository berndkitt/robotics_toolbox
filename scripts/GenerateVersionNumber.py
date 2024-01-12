"""
Script to generate a version number.

The script takes as input a file containing a list of all relevant files calculates a fingerprint
for each file in that list. Additionally, an overall fingerprint for all files is calculated.

The overall fingerprint is used as unique identifier of the version. Based on that fingerprint, the
version number is generated based on another list associating the fingerprint to a version number.
In case the fingerprint is unknown, the version will be 99.99.99.

The script outputs the following information:
- Fingerprint file containing the overall fingerprint as well as the individual fingerprints for
  all files in the provided list.
- C++ version header file containing the version number as well as additional build information
  (i.e. build user, build time, Git commit hash, compiler identifier, and compiler version), which
  can be compiled into a binary.
- Doxygen version file which serves as input file for the documentation generation, adding the
  version number and the Git commit hash to the documentation.

Args:
    base_path (str):                 Base path used as reference for the files in file_list_with_path.
    compiler_identifier (str):       Identifier of the compiler.
    compiler_version (str):          Version of the compiler.
    output_path (str):               Output path for the generated files.
    filename_file_list (str):        Name of the file which contains the list of files.
    filename_version_list (str):     Name of the file which contains the fingerprints and their associated version numbers.
    filename_fingerprint_list (str): Filename of the generated fingerprint list.
    filename_version_doxyfile (str): Filename of the generated Doxygen version file.
    filename_version_header (str):   Filename of the generated C++ version header file.
"""

import argparse
from pathlib import Path

from versioning import FingerprintGenerator
from versioning import VersionNumberGenerator

# run script
if __name__ == "__main__":
    # parse command line arguments
    argument_parser = argparse.ArgumentParser(description="Script to generate a version number.")

    argument_parser.add_argument("-b",
                                 "--base_path",
                                 type=str,
                                 help="Base path used as reference for the files in file_list_with_path.",
                                 required=True)
    argument_parser.add_argument("-ci",
                                 "--compiler_identifier",
                                 type=str,
                                 help="Identifier of the compiler.",
                                 required=True)
    argument_parser.add_argument("-cv",
                                 "--compiler_version",
                                 type=str,
                                 help="Version of the compiler.",
                                 required=True)
    argument_parser.add_argument("-o",
                                 "--output_path",
                                 type=str,
                                 help="Output path for the generated files.",
                                 required=True)
    argument_parser.add_argument("-if",
                                 "--filename_file_list",
                                 type=str,
                                 help="Name of the file which contains the list of files.",
                                 required=True)
    argument_parser.add_argument("-iv",
                                 "--filename_version_list",
                                 type=str,
                                 help="Name of the file which contains the fingerprints and their associated version numbers.",
                                 required=True)
    argument_parser.add_argument("-of",
                                 "--filename_fingerprint_list",
                                 type=str,
                                 help="Filename of the generated fingerprint list.",
                                 required=True)
    argument_parser.add_argument("-od",
                                 "--filename_version_doxyfile",
                                 type=str,
                                 help="Filename of the generated Doxygen version file.",
                                 required=True)
    argument_parser.add_argument("-oh",
                                 "--filename_version_header",
                                 type=str,
                                 help="Filename of the generated C++ version header file.",
                                 required=True)

    args = argument_parser.parse_args()

    # initialize fingerprint generator and calculate fingerprint
    FG = FingerprintGenerator.FingerprintGenerator(args.base_path, Path(args.output_path, args.filename_file_list))

    # write fingerprint information to file
    FG.write_fingerprint_file(Path(args.output_path, args.filename_fingerprint_list))

    # initialize version number generator and generate version number
    VG = VersionNumberGenerator.VersionNumberGenerator(Path(args.output_path, args.filename_version_list), FG.get_overall_fingerprint())

    # write Doxygen version file
    VG.write_doxygen_version_file(Path(args.output_path, args.filename_version_doxyfile))

    # write C++ version header file
    VG.write_version_header_file(args.compiler_identifier, args.compiler_version, Path(args.output_path, args.filename_version_header))
