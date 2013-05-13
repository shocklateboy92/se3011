#ifndef RECORD_H
#define RECORD_H

#include "common.h"

#include <QDateTime>

class QTextStream;
class QDataStream;

class GROUP8_CORE Record
{
public:
    enum class Type {
        UNKNOWN,
        TRADE,
        ENTER,
        AMEND,
        DELETE
    };

    enum class BidAsk {
        Bid,
        Ask,
        Neither
    };

    enum class Field {
        Instrument = 0,
        Date,
        Time,
        RecordType,
        Price,
        Volume,
        UndisclosedVolume,
        Value,
        Qualifiers,
        TransID,
        BidID,
        AskID,
        BidAsk,
        EntryTime,
        OldPrice,
        OldVolume,
        BuyerBrokerID,
        SellerBrokerID,
        NotAField
    };

    Record();
    bool isValid() const;

    friend QDataStream& GROUP8_CORE operator >>(QDataStream &in, Record &r);
    friend QTextStream& GROUP8_CORE operator >>(QTextStream &in, Record &r);
    friend QDataStream& GROUP8_CORE operator <<(QDataStream &os, const Record &r);
    friend QDebug GROUP8_CORE operator <<(QDebug os, const Record &r);

    QString instrument() const;
    QDate   date() const;
    QTime   time() const;
    Type    type() const;
    double  volume() const;
    double  price() const;
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
    void setPrice(double value);
    void setValue(double value);
    void setTransId(long value);
    void setBidId(long value);
    void setAskId(long value);
    void setBidOrAsk(const BidAsk &value);

    static QString fieldName(Field field);
    QVariant fieldValue(Field field) const;
    QString typeName() const;

    static std::size_t numFields();

private:
    QString m_instrument;
    QDate m_date;
    QTime m_time;
    Type m_type;
    double m_volume;
    double m_price;
    double m_value;
    long m_transId;
    long m_bidId;
    long m_askId;
    BidAsk m_bidOrAsk;

    bool m_valid;
};

Q_DECLARE_METATYPE(Record)
Q_DECLARE_METATYPE(Record::Type)
Q_DECLARE_METATYPE(Record::BidAsk)


#endif // RECORD_H
