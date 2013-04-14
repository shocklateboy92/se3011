#ifndef RECORD_H
#define RECORD_H

#include <QDateTime>

class QTextStream;
class QDataStream;

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
    bool isValid();

    friend QDataStream& operator >>(QDataStream &in, Record &r);
    friend QTextStream& operator >>(QTextStream &in, Record &r);
    friend QDataStream& operator <<(QDataStream &os, const Record &r);
    friend QTextStream& operator <<(QTextStream &os, const Record &r);

    QString instrument() const;
    QDate   date() const;
    QTime   time() const;
    Type    type() const;
    double  volume() const;
    double  value() const;
    long    transactionId() const;
    long    bidId() const;
    long    askId() const;
    BidAsk  bidOrAsk() const;

    void setInstrument(const QString &value);
    void setDate(const QDate &value);
    void setTime(const QTime &value);
    void setType(const Type &value);
    void setVolume(double value);
    void setValue(double value);
    void setTransId(long value);
    void setBidId(long value);
    void setAskId(long value);
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

    bool m_valid;
};

class Trade : public Record
{
public:
    Trade(const Record &other) {
        *dynamic_cast<Record*>(this) = other;
    }
    Trade() = default;
};

Q_DECLARE_METATYPE(Record)
Q_DECLARE_METATYPE(Trade)


#endif // RECORD_H
