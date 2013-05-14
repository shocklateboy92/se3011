#ifndef ORDER_H
#define ORDER_H

#include "record.h"

class Order {
public:
    Order(QSharedPointer<Record> record);

    Record* record() const;

    double  price() const;
    double  volume() const;
    QTime   time() const;
    QDate   date() const;
    QString instrument() const;

    void setPrice(double price);
    void setVolume(double volume);
    void setTime(QTime time);
    void setDate(QDate date);

private:
    QSharedPointer<Record> m_record;
};

class Ask : virtual public Order {
public:
    Ask(QSharedPointer<Record> record);
    long id() const;
    long brokerId() const;

    bool operator <(const Ask &other) const;
    bool operator ==(const Ask &other) const;

    Ask createPartial(double newVolume);
};

class Bid : virtual public Order {
public:
    Bid(QSharedPointer<Record> record);
    long id() const;
    long brokerId() const;

    bool operator <(const Bid &other) const;
    bool operator ==(const Bid &other) const;

    Bid createPartial(double newVolume);
};

class Trade : public Record
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
