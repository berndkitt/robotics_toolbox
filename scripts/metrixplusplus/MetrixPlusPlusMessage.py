from . import MetrixPlusPlusMetric


class MetrixPlusPlusMessage:
    def __init__(self,
                 filename_with_path:     str,
                 region:                 str,
                 type:                   str,
                 modified:               str,
                 line_start:             int,
                 line_end:               int,
                 complexity_cyclomatic:  int,
                 complexity_indentation: int,
                 codelines_file:         int,
                 codelines_function:     int,
                 maintainability_index:  int) -> None:
        self.__filename_with_path     = filename_with_path
        self.__region                 = region
        self.__type                   = type
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
                      metrixplusplus_metric: MetrixPlusPlusMetric.MetrixPlusPlusMetric,
                      maximum_value_metric:  int = 0) -> None:
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

        if value_metric and value_metric >= maximum_value_metric:
            message_to_print =f"{self.__filename_with_path}:{self.__line_start} Metrix++: {metrixplusplus_metric_string} is {value_metric}."

            print(message_to_print)
