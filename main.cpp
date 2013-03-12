#include <iostream>
#include <chrono>
#include <boost/date_time.hpp>
#include <time.h>

class Record {
    std::string instrument;
    std::chrono::time_point timestamp;
    Type type;
    double price;
    std::size_t volume;
    std::size_t undisclosedVolume;
    std::size_t value() {
        return volume * price;
    }
    std::string qualifiers;
    std::string transId;

    std::size_t bidId;
    std::size_t askId;

    BidAsk bidAsk;
    std::chrono::time_point entryTime;

    double oldprice;
    std::size_t oldVolume;

    std::size_t buyerId;
    std::size_t sellerId;

    enum BidAsk {
        Bid,
        Ask
    };

    enum class Type {
        ENTER,
        AMEND,
        DELETE,
        TRADE
    };
};

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
