#include <iostream>
#include <sstream>
#include <chrono>
#include <time.h>

#include <QDebug>
#include <QDateTime>

class Record {
    typedef QDateTime Time;
public:
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

    std::string instrument;
    QDate date;
    QTime time;

    Type type;

    double price;
    std::size_t volume;
    std::size_t undisclosedVolume;
    double value;

    std::string qualifiers;
    std::string transId;

    std::size_t bidId;
    std::size_t askId;

    BidAsk bidAsk;
    Time entryTime;

    double oldprice;
    std::size_t oldVolume;

    std::size_t buyerId;
    std::size_t sellerId;

    friend std::istream& operator>> (std::istream& in, Record &r);
};

std::istream& operator>> (std::istream &in, Record &r) {
    char buf;
    std::string time_string, entryTime_string;
    std::string date_string, entryDate_string;
    std::string bid_or_ask, type_string;

    std::string buff;
    std::getline(in, buff);

    buff = QString::fromStdString(buff).remove('"').replace(',', ' ').toStdString();

    std::cout << buff << std::endl;
    std::istringstream is(buff);

    is >> r.instrument >>
    date_string >>
    time_string >>
    type_string >>
    r.price >>
    r.volume >>
    r.undisclosedVolume >>
    r.value >>
    r.qualifiers >>
    r.transId >>
    r.bidId >>
    r.askId >>
    bid_or_ask >>
    entryTime_string >>
    r.oldprice >>
    r.oldVolume >>
    r.buyerId >>
    r.sellerId;

    // parse timestring
    r.date = QDate::fromString(QString::fromStdString(date_string), "yyyy-MM-dd");
    r.time = QTime::fromString(QString::fromStdString(time_string), "hh:mm:ss.zzz");

    // switch on type
    if (type_string == "ENTER")
        r.type = Record::Type::ENTER;
    else if (type_string == "AMEND")
        r.type = Record::Type::AMEND;
    else if (type_string == "DELETE")
        r.type = Record::Type::DELETE;
    else if (type_string == "TRADE")
        r.type = Record::Type::TRADE;
    else
        qFatal("Uknown Record type encountered ");

    // switch on bid/ask
    if (bid_or_ask == "A")
        r.bidAsk = Record::Ask;
    else if (bid_or_ask == "B")
        r.bidAsk = Record::Bid;
    
}

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;

    Record r;
    std::cin >> r;
    return 0;
}
