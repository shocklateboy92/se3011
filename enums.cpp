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
    switch (type) {
        case Record::Type::ENTER:
            os << "ENTER";
            break;
        case Record::Type::AMEND:
            os << "AMEND";
            break;
        case Record::Type::TRADE:
            os << "TRADE";
            break;
        case Record::Type::DELETE:
            os << "DELETE";
            break;
    };
}