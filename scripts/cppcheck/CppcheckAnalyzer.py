"""Class to run the Cppcheck analysis."""
import os
import xml.etree.ElementTree as ET


class CppcheckAnalyzer:
    """Class to run the Cppcheck analysis."""

    def __init__(self,
                 base_directory:      str,
                 configuration_xml:   str,
                 check_configuration: bool = False) -> None:
        """
        Initialize Cppcheck analyzer.

        Args:
            base_directory (str):       Base directory.
            configuration_xml (str):    Filename of the configuration including its path.
            check_configuration (bool): Flag to check the Cppcheck configuration. Defaults to False.
        """
        # set attributes
        self._base_directory             = base_directory
        self._entity_name                = os.path.basename(os.path.normpath(self._base_directory))
        self._directory_cppcheck_build   = f"{self._base_directory}testing/cppcheck/build/"
        self._directory_cppcheck_results = f"{self._base_directory}testing/cppcheck/results/"
        self._filename_results_with_path = f"{self._directory_cppcheck_results}{self._entity_name}_results.xml"
        self._check_configuration        = check_configuration

        # read Cppcheck configuration
        self.__read_configuration_from_xml(configuration_xml)

    def analyze(self) -> None:
        """Run Cppcheck analysis."""
        # create directories
        os.makedirs(self._directory_cppcheck_build, exist_ok=True)
        os.makedirs(self._directory_cppcheck_results, exist_ok=True)

        # create Cppcheck command
        command = self.__create_cppcheck_command()

        # run analysis
        os.system(command)

    def __create_cppcheck_command(self) -> str:
        # create Cppcheck command
        command = f"cppcheck {self._source_directory} --cppcheck-build-dir={self._directory_cppcheck_build} --enable=all --xml --output-file={self._filename_results_with_path}"

        for current_include_directory in self._list_of_include_directories:
            command = command + " -I " + current_include_directory

        if self._check_configuration:
            command = command + " --check-config"

        return command

    def __read_configuration_from_xml(self,
                                      configuration_xml: str) -> None:
        """
        Read the Cppcheck configuration from the XML file.

        Args:
            configuration_xml (str): Filename of the configuration including its path.
        """
        self._list_of_include_directories = []
        self._source_directory            = ""

        # parse XML file
        xml_tree = ET.parse(configuration_xml)
        xml_root = xml_tree.getroot()

        for current_include_directory in xml_root.findall("include_directory"):
            current_include_directory_relative = f"{self._base_directory}{current_include_directory.text}"
            self._list_of_include_directories.append(current_include_directory_relative)

        source_directory = xml_root.find("source_code_directory").text
        source_directory_relative = f"{self._base_directory}{source_directory}"
        self._source_directory = source_directory_relative
