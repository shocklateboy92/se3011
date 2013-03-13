#include <iostream>
#include <sstream>
#include <chrono>
#include <time.h>

#include <QDebug>
#include <QDateTime>

#include <algorithm>
#include <forward_list>
#include <queue>
#include <boost/concept_check.hpp>

const std::string bidAskStrings[] = {"BID", "ASK"};
class Record {

public:
    enum BidAsk {
        Bid = 0,
        Ask
    };

    enum class Type {
        ENTER,
        AMEND,
        DELETE,
        TRADE,
        OFFTR
    };

private:
    std::string instrument;
    QDate date;
    QTime time;

    Type m_type;

    double price;
    std::size_t volume;
    std::size_t undisclosedVolume;
    double value;

    std::string qualifiers;
    std::string transId;

    std::size_t bidId;
    std::size_t askId;

    BidAsk bidAsk;
    QDateTime entryTime;

    double oldPrice;
    std::size_t oldVolume;

    std::size_t buyerId;
    std::size_t sellerId;

public:
    friend std::istream& operator>> (std::istream& in, Record &r);
    friend std::ostream& operator<< (std::ostream& os, const Record& r);
    friend std::ostream& operator<< (std::ostream &os, const Record::Type &type);

    Type type() {
        return m_type;
    }

    bool isAsk() {
        return bidAsk == Ask;
    }

    bool operator< (const Record &other) const {
        if (other.time < time)
            return true;
        else if (other.time == time) {
            if (other.price < this->price) {
                return true;
            }
        }

        return false;
    }
};

std::istream& operator>> (std::istream &in, Record &r) {
    char buf;
    std::string time_string, entryTime_string;
    std::string date_string, entryDate_string;
    std::string bid_or_ask, type_string;

    std::string buff;
    std::getline(in, buff);

    buff = QString::fromStdString(buff).replace("\"\"", "\"-1\"").remove('"').replace(',', ' ').toStdString();

//     std::cout << buff << std::endl;
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
    r.oldPrice >>
    r.oldVolume >>
    r.buyerId >>
    r.sellerId;

    // parse timestring
    r.date = QDate::fromString(QString::fromStdString(date_string), "yyyy-MM-dd");
    r.time = QTime::fromString(QString::fromStdString(time_string), "hh:mm:ss.zzz");

    // switch on type
    if (type_string == "ENTER")
        r.m_type = Record::Type::ENTER;
    else if (type_string == "AMEND")
        r.m_type = Record::Type::AMEND;
    else if (type_string == "DELETE")
        r.m_type = Record::Type::DELETE;
    else if (type_string == "TRADE")
        r.m_type = Record::Type::TRADE;
    else if (type_string == "OFFTR")
        r.m_type = Record::Type::OFFTR;
    else
        qFatal("Uknown Record type encountered ");

    // switch on bid/ask
    if (bid_or_ask == "A")
        r.bidAsk = Record::Ask;
    else /*if (bid_or_ask == "B")*/
        r.bidAsk = Record::Bid;
//     else
//         qFatal("Record is Neither Bid nor Ask");

    return in;
}

std::ostream& operator<<(std::ostream& os, const Record& r)
{
    os << "Record {" <<
    "\n\tinstrument : " << r.instrument <<
    "\n\tdate : " << r.date.toString().toStdString() <<
    "\n\ttime : " << r.time.toString().toStdString() <<
    "\n\trecord : " << r.m_type <<
    "\n\tprice : " << r.price <<
    "\n\tvolume : " << r.volume <<
    "\n\tundisclosedVolume : " << r.undisclosedVolume <<
    "\n\tvalue : " << r.value <<
    "\n\tqualifiers : " << r.qualifiers <<
    "\n\ttransID : " << r.transId <<
    "\n\tbidID : " << r.bidId <<
    "\n\taskID : " << r.askId <<
    "\n\tbidOrAsk " << bidAskStrings[r.bidAsk] <<
    "\n\tentryTime : " << r.entryTime.toString().toStdString() <<
    "\n\toldPrice : " << r.oldPrice <<
    "\n\toldVolume : " << r.oldVolume <<
    "\n\tbuyerId : " << r.buyerId <<
    "\n\tsellerId : " << r.sellerId <<
    "\n}" << endl;
}

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

// JUST USE AN STD::MULTISET
std::vector<Record> records;
std::priority_queue<Record> askQueue;
std::vector<Record> bidQueue;

int main(int argc, char **argv) {
    while (!std::cin.eof()) {
        Record r;
        std::cin >> r;
        std::cout << r;

        if (r.type() == Record::Type::ENTER) {
            if (r.isAsk()) {
                askQueue.push(r);
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
