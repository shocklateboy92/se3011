#include "group8-strategy.h"
#include "trading-signal-group-08.h"

#include <QDebug>

QDockWidget *Group8Strategy::configWidget()
{

    auto widget = new TradingSignalGroup08();
    connect(widget, &TradingSignalGroup08::newMagic, this,
            &Group8Strategy::processMagic);
    connect(widget, &TradingSignalGroup08::deleteMagic, this,
            &Group8Strategy::removeMagic);


    return widget;
}

void Group8Strategy::processMagic(const QString &instrument) {
    MagicData data;
    m_magic.insert(instrument, data);
}

void Group8Strategy::removeMagic(const QString &instrument) {
    if(m_magic.contains(instrument))
        m_magic.remove(instrument);

}

void Group8Strategy::processTrade(const Trade &t)
{
    if (m_magic.contains(t.instrument())) {
        MagicData &data = m_magic[t.instrument()];

        if (t.price() >= data.previousPrice) {
            if (data.isRising == false) {
                data.currentConsecutiveChanges = 0;
            }
            data.isRising = true;
        } else {
            if (data.isRising == true) {
                data.currentConsecutiveChanges = 0;
            }
            data.isRising = false;
        }

        data.previousPrice = t.price();
        data.previousVolume = t.volume();

        data.currentConsecutiveChanges++;


        if (5 <= data.currentConsecutiveChanges && t.time().secsTo(QTime(16,00)) >= 50) {
            data.currentConsecutiveChanges = 0;

                if (data.isRising) {
                        auto r = Record::Ptr::create();
                        r->setBidId(6666);
                        r->setAskId(0);
                        r->setBidOrAsk(Record::BidAsk::Bid);
                        r->setDate(t.date());
                        r->setTime(t.time());
                        r->setInstrument(t.instrument());
                        r->setType(Record::Type::ENTER);
                        r->setVolume(data.previousVolume);
                        r->setPrice(t.price());
                        r->setValue(r->price() * r->volume());
                        emit newRecordCreated(r);
                        qDebug() << "created a bid";

                        //this is bad
                        data.totalBought += data.previousVolume;
                } else {
                       auto r = Record::Ptr::create();
                        r->setAskId(6666);
                        r->setBidId(0);
                        r->setBidOrAsk(Record::BidAsk::Ask);
                        r->setDate(t.date());
                        r->setTime(t.time());
                        r->setInstrument(t.instrument());
                        r->setType(Record::Type::ENTER);
                        r->setVolume(data.totalBought-data.totalSold);
                        r->setPrice(t.price());
                        r->setValue(r->price() * r->volume());
                        emit newRecordCreated(r);

                        qDebug() << "created a ask";

                        //this is bad.
                        data.totalSold += data.totalBought-data.totalSold;

                }


        }
        //qDebug() << abs(QTime(15,40).secsTo(t.time()));
        //qDebug() <<(data.totalBought-data.totalSold);

        if( abs(QTime(16,00).secsTo(t.time())) < 50 && (data.totalBought-data.totalSold) > 0) {
            qDebug() << data.totalBought-data.totalSold;
            data.currentConsecutiveChanges = 0;
            auto r = Record::Ptr::create();
             r->setAskId(6666);
             r->setBidId(0);
             r->setBidOrAsk(Record::BidAsk::Ask);
             r->setDate(t.date());
             r->setTime(t.time());
             r->setInstrument(t.instrument());
             r->setType(Record::Type::ENTER);
             r->setVolume(data.totalBought-data.totalSold);
             r->setPrice(t.price());
             r->setValue(r->price() * r->volume());
             emit newRecordCreated(r);

             //this is bad.
             data.totalSold += data.totalBought-data.totalSold;
        }
    }
}

void Group8Strategy::reset()
{
    for (const QString &ins : m_magic.keys()) {
        m_magic[ins] = MagicData();
    }
}

Group8Strategy::Group8Strategy(QObject *parent) :
    QObject(parent)
{
}
