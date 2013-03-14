#include "record.h"

#include <vector>
#include <unordered_map>
#include <map>
#include <stdexcept>

const std::vector<std::pair<std::string, Record::Type>> Record::type_strings = {
    { "ENTER", Record::Type::ENTER },
    { "AMEND", Record::Type::AMEND },
    { "DELETE", Record::Type::DELETE },
    { "TRADE", Record::Type::TRADE },
    { "OFFTR", Record::Type::OFFTR }
};

const std::vector<std::pair<std::string, Record::BidAsk>> Record::bid_ask_strings = {
    { "B", Record::Bid },
    { "A", Record::Ask }
};

std::istream& operator>> (std::istream &in, Record &r) {
    std::string time_string, entryTime_string;
    std::string date_string, entryDate_string;
    std::string bid_or_ask;

    std::string buff;
    std::getline(in, buff);

    buff = QString::fromStdString(buff).replace("\"\"", "\"-1\"").remove('"').replace(',', ' ').toStdString();

    std::istringstream is(buff);

    is >> r.instrument >>
    date_string >>
    time_string >>
    r.m_type >>
    r.price >>
    r.volume >>
    r.undisclosedVolume >>
    r.value >>
    r.qualifiers >>
    r.transId >>
    r.bidId >>
    r.askId >>
    r.bidAsk >>
    entryTime_string >>
    r.oldPrice >>
    r.oldVolume >>
    r.buyerId >>
    r.sellerId;

    // parse timestring
    r.date = QDate::fromString(QString::fromStdString(date_string), "yyyy-MM-dd");
    r.time = QTime::fromString(QString::fromStdString(time_string), "hh:mm:ss.zzz");

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
    "\n\tbidOrAsk " << r.bidAsk <<
    "\n\tentryTime : " << r.entryTime.toString().toStdString() <<
    "\n\toldPrice : " << r.oldPrice <<
    "\n\toldVolume : " << r.oldVolume <<
    "\n\tbuyerId : " << r.buyerId <<
    "\n\tsellerId : " << r.sellerId <<
    "\n}\n";

    return os;
}

std::ostream& operator<< (std::ostream &os, const Record::Type &type) {
    for (auto p : Record::type_strings) {
        if (p.second == type) {
            os << p.first;
        }
    }
    return os;
}

std::istream& operator>> (std::istream &in, Record::Type &type) {
    std::string buf;
    in >> buf;

    //FIXME: move this to a function to share with BidAsk operators
    for (auto p : Record::type_strings) {
        if (p.first == buf) {
            type = p.second;
            return in;
        }
    }

    throw std::runtime_error(std::string("unknown record type encountered : ") + buf);

    return in;
}

std::ostream& operator<< (std::ostream &os, const Record::BidAsk &bidOrAsk) {
    for (auto p : Record::bid_ask_strings) {
        if (p.second == bidOrAsk) {
            os << p.first;
        }
    }

    return os;
}

std::istream& operator>> (std::istream &in, Record::BidAsk &bidOrAsk) {
    std::string buf;
    in >> buf;

    for (auto p : Record::bid_ask_strings) {
        if (p.first == buf) {
            bidOrAsk = p.second;
            return in;
        }
    }

    bidOrAsk = Record::Neither;
    return in;
}