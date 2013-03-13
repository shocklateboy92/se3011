#include "record.h"

#include <vector>

const std::vector<std::string> type_strings = {
    "ENTER",
    "AMEND",
    "DELETE",
    "TRADE",
    "OFFTR"
};

std::ostream& operator<< (std::ostream &os, const Record::Type &type) {
    os << type_strings[static_cast<int>(type)];
}