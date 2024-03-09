"""Class to run parse the Metrix++ results."""
import csv
import os

from . import MetrixPlusPlusMessage
from . import MetrixPlusPlusMessageList

# define global variables
COLUMN_ID_FILENAME_WITH_PATH     = 0
COLUMN_ID_REGION                 = 1
COLUMN_ID_TYPE                   = 2
COLUMN_ID_MODIFIED               = 3
COLUMN_ID_LINE_START             = 4
COLUMN_ID_LINE_END               = 5
COLUMN_ID_COMPLEXITY_CYCLOMATIC  = 6
COLUMN_ID_COMPLEXITY_INDENTATION = 7
COLUMN_ID_CODELINES_FILE         = 8
COLUMN_ID_CODELINES_FUNCTION     = 9
COLUMN_ID_MAINTAINABILITY_INDEX  = 10


class MetrixPlusPlusResultsParser:
    """Class to run parse the Metrix++ results."""

    def __init__(self,
                 base_directory: str) -> None:
        """
        Initialize Metrix++ results parser.

        Args:
            base_directory (str): Base directory.
        """
        # set attributes
        self._base_directory             = base_directory
        self._entity_name                = os.path.basename(os.path.normpath(self._base_directory))
        self._directory_results          = f"{self._base_directory}testing/metrixplusplus/results/"
        self._filename_results_with_path = f"{self._directory_results}{self._entity_name}_results.csv"
        self._message_list               = MetrixPlusPlusMessageList.MetrixPlusPlusMessageList()

    def get_message_list(self) -> MetrixPlusPlusMessageList.MetrixPlusPlusMessageList:
        """
        Getter for the Metrix++ message list.

        Returns:
            MetrixPlusPlusMessageList.MetrixPlusPlusMessageList: Metrix++ message list.
        """
        return self._message_list

    def parse_results(self) -> None:
        """Parse Metrix++ results."""
        with open(self._filename_results_with_path) as csv_file:
            metrixplusplus_results = csv.reader(csv_file, delimiter=",")

            next(metrixplusplus_results)

            for current_row in metrixplusplus_results:
                current_filename_with_path     = current_row[COLUMN_ID_FILENAME_WITH_PATH]
                current_region                 = current_row[COLUMN_ID_REGION]
                current_type                   = current_row[COLUMN_ID_TYPE]
                current_modified               = current_row[COLUMN_ID_MODIFIED]
                current_line_start             = current_row[COLUMN_ID_LINE_START]
                current_line_end               = current_row[COLUMN_ID_LINE_END]
                current_complexity_cyclomatic  = current_row[COLUMN_ID_COMPLEXITY_CYCLOMATIC]
                current_complexity_indentation = current_row[COLUMN_ID_COMPLEXITY_INDENTATION]
                current_codelines_file         = current_row[COLUMN_ID_CODELINES_FILE]
                current_codelines_function     = current_row[COLUMN_ID_CODELINES_FUNCTION]
                current_maintainability_index  = current_row[COLUMN_ID_MAINTAINABILITY_INDEX]

                current_message = MetrixPlusPlusMessage.MetrixPlusPlusMessage(current_filename_with_path,
                                                                              current_region,
                                                                              current_type,
                                                                              current_modified,
                                                                              MetrixPlusPlusResultsParser.__convert_string_to_int(current_line_start),
                                                                              MetrixPlusPlusResultsParser.__convert_string_to_int(current_line_end),
                                                                              MetrixPlusPlusResultsParser.__convert_string_to_int(current_complexity_cyclomatic),
                                                                              MetrixPlusPlusResultsParser.__convert_string_to_int(current_complexity_indentation),
                                                                              MetrixPlusPlusResultsParser.__convert_string_to_int(current_codelines_file),
                                                                              MetrixPlusPlusResultsParser.__convert_string_to_int(current_codelines_function),
                                                                              MetrixPlusPlusResultsParser.__convert_string_to_int(current_maintainability_index))

                self._message_list.add_message(current_message)

    @staticmethod
    def __convert_string_to_int(string: str) -> int:
        """Convert string to integer."""
        return_value = None

        if string:
            return_value = int(string)

        return return_value
