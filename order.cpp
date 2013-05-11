#include "order.h"

bool Order::operator ==(const Order &other) const
{
    return id() == other.id() && m_record == other.m_record;
}


bool Ask::operator ==(const Ask &other) const
{
    return record()->askId() == other.record()->askId();
}

Order::Order(Record &record)
    : m_record(&record)
{
}

Record* Order::record() const
{
    return m_record.data();
}

Bid::Bid(Record &record)
    : Order(record)
{
}

Ask::Ask(Record &record)
    : Order(record)
{
}

long Bid::id() const
{
    return record()->bidId();
}

long Ask::id() const
{
    return record()->askId();
}

double Order::price() const
{
    return record()->price();
}

void Order::setPrice(double price)
{
    record()->setPrice(price);
}

double Order::volume() const
{
    return record()->volume();
}

void Order::setVolume(double volume)
{
    record()->setVolume(volume);
}

QDate Order::date() const
{
    return record()->date();
}

QTime Order::time() const
{
    return record()->time();
}

void Order::setDate(QDate date)
{
    record()->setDate(date);
}

void Order::setTime(QTime time)
{
    record()->setTime(time);
}

Trade::Trade(Ask ask, Bid bid)
{
    Q_UNUSED (ask)
    Trade(*bid.record());
}

bool Bid::operator <(const Bid &other) const
{
    return date() < other.date() &&
            time() < other.time() &&
             price() < other.price();
}

bool Ask::operator <(const Ask &other) const
{
    return date() < other.date() &&
            time() < other.time() &&
             price() < other.price();
}


int fd = qRegisterMetaType<Trade>("Trade");
