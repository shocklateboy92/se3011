#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <sstream>

#include <QDateTime>

class Record {

public:
    enum BidAsk {
        Bid = 0,
        Ask,
        Neither
    };

    enum class Type {
        ENTER = 0,
        AMEND,
        DELETE,
        TRADE,
        OFFTR
    };

private:
    static const std::vector<std::pair<std::string, Record::Type>> type_strings;
    static const std::vector<std::pair<std::string, Record::BidAsk>> bid_ask_strings;

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

    friend std::istream& operator>> (std::istream& in, Record::Type &type);
    friend std::ostream& operator<< (std::ostream &os, const Record::Type &type);

    friend std::istream& operator>> (std::istream &in, Record::BidAsk &bidOrAsk);
    friend std::ostream& operator<< (std::ostream &os, const Record::BidAsk &bidOrAsk);

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

#endif