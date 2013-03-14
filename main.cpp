
#include <chrono>
#include <time.h>



#include <algorithm>
#include <set>

#include "record.h"




std::multiset<Record> askQueue;
std::vector<Record> bidQueue;

int main(int argc, char **argv) {
    while (!std::cin.eof()) {
        Record r;
        std::cin >> r;
        std::cout << r;

        if (r.type() == Record::Type::ENTER) {
            if (r.isAsk()) {
                askQueue.insert(r);
            } else {
                bidQueue.push_back(r);
            }
        }
    }

    for (auto &bid : bidQueue) {
        std::cout << bid << std::endl;
    }

    std::endl(std::cout);
    return 0;
}
