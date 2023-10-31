"""Module to generate a version number based on a fingerprint."""

import datetime
import getpass
import xml.etree.ElementTree as ET

import git


class VersionNumberGenerator:
    """
    Class generate a version number based on a fingerprint.

    The class can be used to generate a version number based on a fingerprint. The version number
    will be extracted from a list containing known fingerprints and their associated version number.
    In case a fingerprint is not known, the version number 99.99.99 will be generated.
    """

    def __init__(self,
                 version_list_with_path: str,
                 overall_fingerprint:    str):
        """
        Initialize the version number generator.

        Args:
            version_list_with_path (str): Name of the file (including its path) which contains the fingerprints and their associated version numbers.
            overall_fingerprint (str):    Overall fingerprint.
        """
        # initialize attributes
        self._overall_fingerprint    = overall_fingerprint
        self._version_major          = "99"
        self._version_minor          = "99"
        self._version_patch          = "99"
        self._version_list_with_path = version_list_with_path

        # get and store version number
        self._extract_version_from_fingerprint()

        # get and store build information
        self._build_user = getpass.getuser()
        self._build_time = datetime.datetime.today().strftime("%Y-%m-%d %H:%M:%S")

        # get and store Git commit hash
        repository          = git.Repo(search_parent_directories=True)
        repository_is_dirty = repository.is_dirty()

        self._git_commit_hash = repository.head.object.hexsha

        if repository_is_dirty:
            self._git_commit_hash = self._git_commit_hash + "-dirty"

    def write_doxygen_version_file(self,
                                   filename_version_doxyfile_with_path: str) -> None:
        """
        Write the version information to a Doxygen file.

        Args:
            filename_version_doxyfile_with_path (str): Filename (including its path) of the generated Doxygen version file.
        """
        # open file
        doxygen_version_file = open(filename_version_doxyfile_with_path, "w")

        # write version
        doxygen_version_file.write("PROJECT_NUMBER         = " + self._version_major + "." + self._version_minor + "." + self._version_patch + " - " + self._git_commit_hash + "\n")

        # close file
        doxygen_version_file.close()

    def write_version_header_file(self,
                                  filename_version_header_with_path: str) -> None:
        """
        Write the version information to a C++ version header file.

        Args:
            filename_version_header_with_path (str): Filename (including its path) of the generated C++ version header file.
        """
        # open file
        version_header_file = open(filename_version_header_with_path, "w")

        # write overall fingerprint
        version_header_file.write("// fingerprint: " + self._overall_fingerprint + "\n")
        version_header_file.write("\n")

        # write version number
        version_header_file.write("const uint64 VersionMajor = " + self._version_major + "U;\n")
        version_header_file.write("const uint64 VersionMinor = " + self._version_minor + "U;\n")
        version_header_file.write("const uint64 VersionPatch = " + self._version_patch + "U;\n\n")

        # write build information
        version_header_file.write("const std::string BuildUser = \"" + self._build_user + "\";\n")
        version_header_file.write("const std::string BuildTime = \"" + self._build_time + "\";\n\n")

        # write Git commit hash
        version_header_file.write("const std::string GitCommitHash = \"" + self._git_commit_hash + "\";\n")

        # close file
        version_header_file.close()

    def _extract_version_from_fingerprint(self) -> None:
        """Extract the version number based on the overall fingerprint."""
        xml_tree = ET.parse(self._version_list_with_path)
        xml_root = xml_tree.getroot()

        for current_version in xml_root.findall("version"):
            current_fingerprint = current_version.find("fingerprint").text

            if current_fingerprint == self._overall_fingerprint:
                self._version_major = current_version.find("versionmajor").text
                self._version_minor = current_version.find("versionminor").text
                self._version_patch = current_version.find("versionpatch").text
