#include "record.h"

#include <vector>
#include <unordered_map>
#include <map>
#include <stdexcept>

std::ostream& operator<< (std::ostream &os, const Record::Type &type) {
    for (auto p : type_strings) {
        if (p.second == type) {
            os << p.first;
        }
    }
    return os;
}

std::istream& operator>> (std::istream &in, Record::Type &type) {
    std::string buf;
    in >> buf;

    for (auto p : type_strings) {
        if (p.first == buf) {
            type = p.second;
            return in;
        }
    }

    throw std::runtime_error(std::string("unknown record type encountered : ") + buf);

    return in;
}