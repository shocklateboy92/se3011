#ifndef RECORD_H
#define RECORD_H

#include <QDataStream>
#include <QDateTime>

class Record
{
public:
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

    Record();
    QDataStream& operator>>(QDataStream &in);

    QString instrument() const;
    void setInstrument(const QString &value);

    QDate date() const;
    void setDate(const QDate &value);

    QTime time() const;
    void setTime(const QTime &value);

    Type type() const;
    void setType(const Type &value);

    double volume() const;
    void setVolume(double value);

    double value() const;
    void setValue(double value);

    long transactionId() const;
    void setTransId(long value);

    long bidId() const;
    void setBidId(long value);

    long askId() const;
    void setAskId(long value);

    BidAsk bidOrAsk() const;
    void setBidOrAsk(const BidAsk &value);

private:
    QString m_instrument;
    QDate m_date;
    QTime m_time;
    Type m_type;
    double m_volume;
    double m_value;
    long m_transId;
    long m_bidId;
    long m_askId;
    BidAsk m_bidOrAsk;
};

typedef Record Trade;

#endif // RECORD_H
