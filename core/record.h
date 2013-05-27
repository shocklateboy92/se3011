#ifndef RECORD_H
#define RECORD_H

#include "common.h"

#include <QDateTime>
#include <QTextStream>
#include <QDataStream>

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

    struct Field {
        enum t {
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
        } v;
        Field(const int &i) {
            v = (t) i;
        }
        Field() = default;
        operator int() const {
            return v;
        }
    };

    typedef QSharedPointer<Record> Ptr;

    Record();
    static Ptr fromCSV(QByteArray csvLine);
    bool isValid() const;

    friend QDebug GROUP8_CORE operator <<(QDebug os, const Record &r);

    QByteArray instrument() const;
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
    long    buyerId() const;
    long    sellerId() const;

    void setInstrument(const QByteArray &value);
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
    void setSellerId(long id);
    void setBuyerId(long id);

    static QString fieldName(Field field);
    bool hasField(Field field);
    QVariant fieldValue(Field field) const;
    QString typeName() const;

    static std::size_t numFields();

    void parseTime(Ptr ret, QList<QByteArray> cols);
private:
    QByteArray m_instrument;
    QDate m_date;
    QTime m_time;
    Type m_type;
    double m_volume;
    double m_undisclosedVolume;
    double m_price;
    double m_value;
    long m_transId;
    long m_bidId;
    long m_askId;
    BidAsk m_bidOrAsk;
    long m_buyerId;
    long m_sellerId;

    bool m_valid;
    bool m_fields[Record::Field::NotAField];

    friend class Ask;
    friend class Bid;
};

Q_DECLARE_METATYPE(Record)
Q_DECLARE_METATYPE(Record::Type)
Q_DECLARE_METATYPE(Record::Field)
Q_DECLARE_METATYPE(Record::BidAsk)
Q_DECLARE_METATYPE(Record::Ptr)


#endif // RECORD_H
