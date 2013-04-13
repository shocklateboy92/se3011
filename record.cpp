#include "record.h"

#include <QString>

Record::Record() :
    m_valid(false)
{
}


QString Record::instrument() const
{
    return m_instrument;
}

void Record::setInstrument(const QString &value)
{
    m_instrument = value;
}

QDate Record::date() const
{
    return m_date;
}

void Record::setDate(const QDate &value)
{
    m_date = value;
}

QTime Record::time() const
{
    return m_time;
}

void Record::setTime(const QTime &value)
{
    m_time = value;
}

Record::Type Record::type() const
{
    return m_type;
}

void Record::setType(const Type &value)
{
    m_type = value;
}

double Record::volume() const
{
    return m_volume;
}

void Record::setVolume(double value)
{
    m_volume = value;
}

double Record::value() const
{
    return m_value;
}

void Record::setValue(double value)
{
    m_value = value;
}

long Record::transactionId() const
{
    return m_transId;
}

void Record::setTransId(long value)
{
    m_transId = value;
}

long Record::bidId() const
{
    return m_bidId;
}

void Record::setBidId(long value)
{
    m_bidId = value;
}

long Record::askId() const
{
    return m_askId;
}

void Record::setAskId(long value)
{
    m_askId = value;
}

Record::BidAsk Record::bidOrAsk() const
{
    return m_bidOrAsk;
}

void Record::setBidOrAsk(const BidAsk &value)
{
    m_bidOrAsk = value;
}

bool Record::isValid() {
    //FIXME: run some sanity checks here
    return m_valid;
}
