
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
            switch (r.bidOrAsk()) {
                case Record::BidAsk::Bid:
                    bidQueue.push_back(r);
                    break;
                case Record::BidAsk::Ask:
                    askQueue.insert(r);
                    break;
                case Record::BidAsk::Neither:
                    break;
            };
        }
    }

    for (auto &bid : bidQueue) {
        std::cout << bid << std::endl;
    }

    std::endl(std::cout);
    return 0;
}
