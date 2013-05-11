#ifndef ORDER_H
#define ORDER_H

#include "record.h"

class Order {
public:
    Order(Record &record);

    virtual long id() const = 0;
    bool operator==(const Order &other) const;

    Record* record() const;

    double  price() const;
    double  volume() const;
    QTime   time() const;
    QDate   date() const;

    void setPrice(double price);
    void setVolume(double volume);
    void setTime(QTime time);
    void setDate(QDate date);

private:
    QSharedPointer<Record> m_record;
};

class Ask : virtual public Order {
public:
    Ask(Record &record);
    long id() const;

    bool operator<(const Ask &other) const;
    bool operator==(const Ask &other) const;
};

class Bid : virtual public Order {
public:
    Bid(Record &record);
    long id() const;

    bool operator<(const Bid &other) const;
};

class Trade : public Record
{
public:
    Trade(const Record &other) {
        *dynamic_cast<Record*>(this) = other;
    }
    Trade(Ask ask, Bid bid);
    Trade() = default;
};

Q_DECLARE_METATYPE(Trade)

#endif // ORDER_H
