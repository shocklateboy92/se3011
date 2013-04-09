#ifndef RECORD_H
#define RECORD_H

#include <QDataStream>

class Record
{
    enum class Type {
        TRADE,
        ENTER,
        AMEND,
        DELETE
    };

    enum class BidAsk {
        Bid,
        Ask
    };

public:
    Record();
    QDataStream& operator>>(QDataStream &in);

private:
    QString instrument;
    QDate date;
    QTime time;
    Type type;
    double volume;
    double value;
    long transId;
    long bidId;
    long askId;
    BidAsk bidOrAsk;
};

#endif // RECORD_H
