# This file is part of the Robotics Toolbox.

# Copyright (C) 2026

# Authors: Bernd Kitt (b.kitt@berndkitt.de)

# The Robotics Toolbox is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 3 of the License,
# or any later version.

# The Robotics Toolbox is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
# Public License for more details.

# You should have received a copy of the GNU General Public License along with
# the Robotics Toolbox. If not, see https://www.gnu.org/licenses/.

"""Class to represent a list of Metrix++ messages."""
from . import MetrixPlusPlusMessage
from . import MetrixPlusPlusMetric


class MetrixPlusPlusMessageList:
    """Class to represent a list of Metrix++ messages."""

    def __init__(self) -> None:
        """Initialize an empty message list."""
        self.__number_of_messages = 0
        self.__message_list       = []

    def add_message(self,
                    message: MetrixPlusPlusMessage.MetrixPlusPlusMessage) -> None:
        """Add a Metrix++ message to the list.

        Args:
            message (MetrixPlusPlusMessage.MetrixPlusPlusMessage): Metrix++ message.
        """
        self.__number_of_messages += 1
        self.__message_list.append(message)

    def get_maximum_value_for_metric(self,
                                     metrixplusplus_metric: MetrixPlusPlusMetric.MetrixPlusPlusMetric) -> int:
        """
        Getter for the maximum value of a Metrix++ metric in all messages in the list.

        Args:
            metrixplusplus_metric (MetrixPlusPlusMetric.MetrixPlusPlusMetric): Metrix++ metric.

        Returns:
            int: Maximum value of the Metrix++ metric in all messages in the list.
        """
        maximum_value_metric = 0

        for current_message in self.__message_list:
            current_value_metric = current_message.get_value_for_metric(metrixplusplus_metric)

            if current_value_metric and current_value_metric > maximum_value_metric:
                maximum_value_metric = current_value_metric

        return maximum_value_metric

    def print_messages(self,
                       metrixplusplus_metric:        MetrixPlusPlusMetric.MetrixPlusPlusMetric,
                       maximum_allowed_value_metric: int = 0) -> None:
        """
        Print all messages in which a Metrix++ metric exceeds the maximum allowed value.

        Args:
            metrixplusplus_metric (MetrixPlusPlusMetric.MetrixPlusPlusMetric): Metrix++ metric.
            maximum_allowed_value_metric (int, optional):                      Maximum allowed value for the metric. Defaults to 0.
        """
        for current_message in self.__message_list:
            current_message.print_message(metrixplusplus_metric, maximum_allowed_value_metric)
