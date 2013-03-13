
#include <chrono>
#include <time.h>



#include <algorithm>
#include <set>

#include "record.h"

const std::string bidAskStrings[] = {"BID", "ASK"};


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
