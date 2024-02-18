from . import MetrixPlusPlusMessage
from . import MetrixPlusPlusMetric


class MetrixPlusPlusMessageList:
    def __init__(self) -> None:
        self.__number_of_messages = 0
        self.__message_list       = []

    def add_message(self,
                    message: MetrixPlusPlusMessage.MetrixPlusPlusMessage) -> None:
        self.__number_of_messages += 1
        self.__message_list.append(message)

    def get_maximum_value_for_metric(self,
                                     metrixplusplus_metric: MetrixPlusPlusMetric.MetrixPlusPlusMetric) -> int:
        maximum_value_metric = 0

        for current_message in self.__message_list:
            current_value_metric = current_message.get_value_for_metric(metrixplusplus_metric)

            if current_value_metric and current_value_metric > maximum_value_metric:
                maximum_value_metric = current_value_metric

        return maximum_value_metric

    def print_messages(self,
                       metrixplusplus_metric: MetrixPlusPlusMetric.MetrixPlusPlusMetric,
                       maximum_value_metric:  int = 0) -> None:
        for current_message in self.__message_list:
            current_message.print_message(metrixplusplus_metric, maximum_value_metric)
