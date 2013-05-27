#ifndef ORDER_H
#define ORDER_H

#include "record.h"

class GROUP8_CORE Order {
public:
    Order(QSharedPointer<Record> record);

    inline Record* record() const {
        return m_record.data();
    }

    double  price() const;
    double  volume() const;
    QTime   time() const;
    QDate   date() const;
    QByteArray instrument() const;

    void setPrice(double price);
    void setVolume(double volume);
    void setTime(QTime time);
    void setDate(QDate date);

private:
    QSharedPointer<Record> m_record;
};

class GROUP8_CORE Ask : virtual public Order {
public:
    Ask(QSharedPointer<Record> record);
    long id() const;
    long brokerId() const;

    bool operator <(const Ask &other) const;
    inline bool operator ==(const Ask &other) const {
        return record()->m_askId == other.record()->m_askId;
    }

    Ask createPartial(double newVolume);
};

class GROUP8_CORE Bid : virtual public Order {
public:
    Bid(QSharedPointer<Record> record);
    long id() const;
    long brokerId() const;

    bool operator <(const Bid &other) const;
    bool operator ==(const Bid &other) const {
        return record()->m_bidId == other.record()->m_bidId;
    }

    Bid createPartial(double newVolume);
};

class GROUP8_CORE Trade : public Record
{
    Trade(const Record &other) {
        *dynamic_cast<Record*>(this) = other;
    }
    Trade(Ask ask, Bid bid);
    friend class TradingEngine;

public:
    Trade() = default;
};

Q_DECLARE_METATYPE(Trade)

#endif // ORDER_H
