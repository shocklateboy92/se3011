#include "order.h"

bool Order::operator ==(const Order &other) const
{
    return id() == other.id() && m_record == other.m_record;
}


bool Ask::operator ==(const Ask &other) const
{
    return record()->askId() == other.record()->askId();
}

Order::Order(QSharedPointer<Record> record)
    : m_record(record)
{
}

Record* Order::record() const
{
    return m_record.data();
}

Bid::Bid(QSharedPointer<Record> record)
    : Order(record)
{
}

Ask::Ask(QSharedPointer<Record> record)
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

long Ask::brokerId() const
{
    return record()->sellerId();
}

long Bid::brokerId() const
{
    return record()->buyerId();
}

QString Order::instrument() const {
    return record()->instrument();
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

template <typename BidAsk>
inline BidAsk createPartialBidOrAsk(BidAsk *ba, double newVolume) {
    Q_ASSERT (ba->volume() >= newVolume);

    ba->setVolume(ba->volume() - newVolume);

    QSharedPointer<Record> r(new Record(*ba->record()));
    BidAsk a(r);

    a.setVolume(newVolume);
    return a;
}

Ask Ask::createPartial(double newVolume) {
    return createPartialBidOrAsk(this, newVolume);
}

Bid Bid::createPartial(double newVolume) {
    return createPartialBidOrAsk(this, newVolume);
}

Trade::Trade(Ask ask, Bid bid) {
    Q_ASSERT (ask.price() <= bid.price());
    Q_ASSERT (ask.volume() == bid.volume());
    Q_ASSERT (ask.instrument() == bid.instrument());

    setInstrument(ask.instrument());
    setDate(bid.date() > ask.date() ? bid.date() : ask.date());
    setTime(bid.time() > ask.time() ? bid.time() : ask.time());

    setType(Record::Type::TRADE);
    setPrice(bid.price());
    setVolume(ask.volume());
    setValue(bid.record()->value());
    setTransId(0);
    setBidId(bid.id());
    setAskId(ask.id());
    setBuyerId(bid.brokerId());
    setSellerId(ask.brokerId());
}

int fd = qRegisterMetaType<Trade>("Trade");
