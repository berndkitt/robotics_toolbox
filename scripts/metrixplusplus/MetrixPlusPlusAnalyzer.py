"""Class to run the Metrix++ analysis."""
import os

from file_collector import FileCollector


class MetrixPlusPlusAnalyzer:
    """Class to run the Metrix++ analysis."""

    def __init__(self,
                 base_directory:     str,
                 configuration_json: str) -> None:
        """
        Initialize Metrix++ analyzer.

        Args:
            base_directory (str):     Base directory.
            configuration_json (str): Filename of the configuration including its path.
        """
        # set attributes
        self._base_directory              = base_directory
        self._entity_name                 = os.path.basename(os.path.normpath(self._base_directory))
        self._directory_results           = f"{self._base_directory}testing/metrixplusplus/results/"
        self._filename_database_with_path = f"{self._directory_results}metrixplusplus.db"
        self._filename_results_with_path  = f"{self._directory_results}{self._entity_name}_results.csv"

        # get list of files to check
        files                         = FileCollector.FileCollector(configuration_json, base_directory)
        self._list_of_files_as_string = files.get_list_of_files_as_string()

    # function to perform the analysis
    def analyze(self) -> None:
        """Run Metrix++ analysis."""
        # create directory for the results
        os.makedirs(self._directory_results, exist_ok=True)

        # run analysis for defined entity
        command_collect = f"python3 /usr/local/bin/metrix++ collect --std.code.filelines.code --std.code.lines.code --std.code.complexity.cyclomatic --std.code.complexity.maxindent --std.code.maintindex.simple --db-file={self._filename_database_with_path} -- {self._list_of_files_as_string}"
        command_export  = f"python3 /usr/local/bin/metrix++ export --db-file={self._filename_database_with_path} > {self._filename_results_with_path}"

        os.system(command_collect)
        os.system(command_export)
