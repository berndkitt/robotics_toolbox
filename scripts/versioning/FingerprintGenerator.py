"""Module to create fingerprints for files."""

import hashlib
import typing
import xml.etree.ElementTree as ET
from pathlib import Path


class FingerprintGenerator:
    """
    Class to calculate fingerprints for files.

    The class can be used to calculate the individual fingerprints for each file provided in a list
    of all files as well as an overall fingerprint calculated based on all files is the list.
    """

    def __init__(self,
                 base_path:           str,
                 file_list_with_path: str):
        """
        Initialize the fingerprint generator.

        Args:
            base_path (str):           Base path used as reference for the files in file_list_with_path.
            file_list_with_path (str): Name of the file (including its path) which contains the list of files.
        """
        # initialize attributes
        self._base_path            = base_path
        self._list_of_filenames    = self._extract_list_of_files_from_xml(file_list_with_path)
        self._block_size           = 65536
        self._overall_fingerprint  = 0
        self._list_of_fingerprints = []

        # calculate fingerprints
        self._calculate_fingerprints()

    def get_overall_fingerprint(self) -> str:
        """
        Getter for the overall fingerprint.

        Returns:
            str: Overall fingerprint.
        """
        return self._overall_fingerprint

    def write_fingerprint_file(self,
                               filename_fingerprint_list_with_path: str) -> None:
        """
        Write fingerprint information to file.

        Args:
            filename_fingerprint_list_with_path (str): Filename of the generated fingerprint list (including its path).
        """
        # open file
        file_for_fingerprint = open(filename_fingerprint_list_with_path, "w")

        # write overall fingerprint
        file_for_fingerprint.write("##### Overall fingerprint #####\n")
        file_for_fingerprint.write(self._overall_fingerprint + "\n")
        file_for_fingerprint.write("\n")

        # write individual fingerprint for each file
        file_for_fingerprint.write("##### Individual file fingerprints #####\n")

        for counter in range(0, len(self._list_of_filenames)):
            file_for_fingerprint.write(self._list_of_filenames[counter] + "\n")
            file_for_fingerprint.write(self._list_of_fingerprints[counter] + "\n")

        # close file
        file_for_fingerprint.close()

    def _calculate_fingerprint_for_single_file(self,
                                               filename_with_path: str) -> str:
        """
        Calculate the fingerprint for a single file.

        Args:
            filename_with_path (str): Name of the file (including its path) for which the fingerprint shall be calculated.

        Returns:
            str: Fingerprint of the file.
        """
        # initialize fingerprint calculation
        sha512 = hashlib.sha512()

        # open file
        file_to_process = open(filename_with_path, "rb")

        # calculate fingerprint of the file
        for block in iter(lambda: file_to_process.read(self._block_size), b""):
            sha512.update(block)

        # close file
        file_to_process.close()

        # return calculated fingerprint
        return sha512.hexdigest()

    def _calculate_fingerprints(self) -> None:
        """Calculate the individual fingerprints for a list of files as well as an overall fingerprint."""
        # calculate individual fingerprint for each file
        for current_file in self._list_of_filenames:
            current_file_with_path = Path(self._base_path, current_file)
            current_fingerprint    = self._calculate_fingerprint_for_single_file(current_file_with_path)

            self._list_of_fingerprints.append(current_fingerprint)

        # calculate overall fingerprint
        self._overall_fingerprint = self._calculate_overall_fingerprint_for_list_of_files()

    def _calculate_overall_fingerprint_for_list_of_files(self) -> str:
        """
        Calculate overall fingerprint for a list of files.

        Returns:
            str: Overall fingerprint of all files.
        """
        # initialize fingerprint calculation
        sha512 = hashlib.sha512()

        # calculate fingerprint of all files
        for filename in self._list_of_filenames:
            # open file
            filename_with_path = Path(self._base_path, filename)
            file_to_process    = open(filename_with_path, "rb")

            # add current file to fingerprint calculation
            for block in iter(lambda: file_to_process.read(self._block_size), b""):
                sha512.update(block)

            # close file
            file_to_process.close()

        # return calculated fingerprint
        return sha512.hexdigest()

    def _extract_list_of_files_from_xml(self,
                                        file_list_with_path: str) -> typing.List[str]:
        """
        Extract the list of files from a XML file.

        Args:
            file_list_with_path (str): Name of the file (including its path) which contains the list of files.

        Returns:
            typing.List[str]: List of files (including their relative path to the base_path).
        """
        list_of_files = []

        xml_tree = ET.parse(file_list_with_path)
        xml_root = xml_tree.getroot()

        for current_file in xml_root.findall("file"):
            list_of_files.append(current_file.text)

        return list_of_files
