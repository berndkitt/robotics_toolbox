"""Class to represent a Metrix++ message."""
from . import MetrixPlusPlusMetric


class MetrixPlusPlusMessage:
    """Class to represent a Metrix++ message."""

    def __init__(self,
                 filename_with_path:     str,
                 region:                 str,
                 region_type:            str,
                 modified:               str,
                 line_start:             int,
                 line_end:               int,
                 complexity_cyclomatic:  int,
                 complexity_indentation: int,
                 codelines_file:         int,
                 codelines_function:     int,
                 maintainability_index:  int) -> None:
        """
        Initialize a Metrix++ message.

        Contains all the information of a message. Not all members will be set. Which members are
        set depends on the message itself and what has been analyzed.

        Args:
            filename_with_path (str):     Filename.
            region (str):                 Region.
            region_type (str):            Region type.
            modified (str):               // TODO
            line_start (int):             Start line.
            line_end (int):               End line.
            complexity_cyclomatic (int):  Cyclomatic complexity.
            complexity_indentation (int): Indentation complexity.
            codelines_file (int):         Number of lines of code in the file.
            codelines_function (int):     Number of lines of code in the function.
            maintainability_index (int):  Maintainability index.
        """
        self.__filename_with_path     = filename_with_path
        self.__region                 = region
        self.__region_type            = region_type
        self.__modified               = modified
        self.__line_start             = line_start
        self.__line_end               = line_end
        self.__complexity_cyclomatic  = complexity_cyclomatic
        self.__complexity_indentation = complexity_indentation
        self.__codelines_file         = codelines_file
        self.__codelines_function     = codelines_function
        self.__maintainability_index  = maintainability_index

    def get_value_for_metric(self,
                             metrixplusplus_metric: MetrixPlusPlusMetric.MetrixPlusPlusMetric) -> int:
        """
        Getter for the value of a Metrix++ metric.

        Args:
            metrixplusplus_metric (MetrixPlusPlusMetric.MetrixPlusPlusMetric): Metrix++ metric.

        Returns:
            int: Value of the Metrix++ metric.
        """
        metric_value = None

        if metrixplusplus_metric == MetrixPlusPlusMetric.MetrixPlusPlusMetric.COMPLEXITY_CYCLOMATIC:
            metric_value = self.__complexity_cyclomatic
        elif metrixplusplus_metric == MetrixPlusPlusMetric.MetrixPlusPlusMetric.COMPLEXITY_INDENTATION:
            metric_value = self.__complexity_indentation
        elif metrixplusplus_metric == MetrixPlusPlusMetric.MetrixPlusPlusMetric.CODELINES_FILE:
            metric_value = self.__codelines_file
        elif metrixplusplus_metric == MetrixPlusPlusMetric.MetrixPlusPlusMetric.CODELINES_FUNCTION:
            metric_value = self.__codelines_function
        elif metrixplusplus_metric == MetrixPlusPlusMetric.MetrixPlusPlusMetric.MAINTAINABILITY_INDEX:
            metric_value = self.__maintainability_index
        else:
            metric_value = None

        return metric_value

    def print_message(self,
                      metrixplusplus_metric:        MetrixPlusPlusMetric.MetrixPlusPlusMetric,
                      maximum_allowed_value_metric: int = 0) -> None:
        """
        Print message information for a Metrix++ metric.

        Information will only be printed in case the value of the metric exceeds the maximum
        allowed value for the metric.

        Args:
            metrixplusplus_metric (MetrixPlusPlusMetric.MetrixPlusPlusMetric): Metrix++ metric.
            maximum_allowed_value_metric (int, optional):                      Maximum allowed value for the metric. Defaults to 0.
        """
        metrixplusplus_metric_string = MetrixPlusPlusMetric.MetrixPlusPlusMetric.get_metric_as_string(metrixplusplus_metric)
        value_metric                 = 0

        if metrixplusplus_metric == MetrixPlusPlusMetric.MetrixPlusPlusMetric.COMPLEXITY_CYCLOMATIC:
            value_metric = self.__complexity_cyclomatic
        elif metrixplusplus_metric == MetrixPlusPlusMetric.MetrixPlusPlusMetric.COMPLEXITY_INDENTATION:
            value_metric = self.__complexity_indentation
        elif metrixplusplus_metric == MetrixPlusPlusMetric.MetrixPlusPlusMetric.CODELINES_FILE:
            value_metric = self.__codelines_file
        elif metrixplusplus_metric == MetrixPlusPlusMetric.MetrixPlusPlusMetric.CODELINES_FUNCTION:
            value_metric = self.__codelines_function
        elif metrixplusplus_metric == MetrixPlusPlusMetric.MetrixPlusPlusMetric.MAINTAINABILITY_INDEX:
            value_metric = self.__maintainability_index
        else:
            pass

        if value_metric and value_metric > maximum_allowed_value_metric:
            message_to_print = f"{self.__filename_with_path}:{self.__line_start} Metrix++: {metrixplusplus_metric_string} is {value_metric}, maximum allowed value is {maximum_allowed_value_metric}."

            print(message_to_print)
