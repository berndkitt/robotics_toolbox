"""Class to represent the Metrix++ metrics."""
from enum import Enum

from . import MetrixPlusPlusMetric


class MetrixPlusPlusMetric(Enum):
    """Class to represent the Metrix++ metrics."""

    COMPLEXITY_CYCLOMATIC  = 1
    COMPLEXITY_INDENTATION = 2
    CODELINES_FILE         = 3
    CODELINES_FUNCTION     = 4
    MAINTAINABILITY_INDEX  = 5

    @staticmethod
    def get_metric_as_string(metrixplusplus_metric: MetrixPlusPlusMetric) -> None:
        """
        Getter for the Metrix++ metric as string.

        Args:
            metrixplusplus_metric (MetrixplusplusMetric): Metrix++ metric.

        Returns:
            str: Metrix++ metric as string.
        """
        metric_as_string = ""

        if metrixplusplus_metric == MetrixPlusPlusMetric.COMPLEXITY_CYCLOMATIC:
            metric_as_string = "Complexity (cyclomatic)"
        elif metrixplusplus_metric == MetrixPlusPlusMetric.COMPLEXITY_INDENTATION:
            metric_as_string = "Complexity (indentation)"
        elif metrixplusplus_metric == MetrixPlusPlusMetric.CODELINES_FILE:
            metric_as_string = "Codelines (file)"
        elif metrixplusplus_metric == MetrixPlusPlusMetric.CODELINES_FUNCTION:
            metric_as_string = "Codelines (function)"
        elif metrixplusplus_metric == MetrixPlusPlusMetric.MAINTAINABILITY_INDEX:
            metric_as_string = "Maintainability Index"
        else:
            metric_as_string = "Metric unknown."

        return metric_as_string
