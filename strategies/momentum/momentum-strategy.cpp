#include "momentum-strategy.h"
#include "trading-signal-momentum.h"

#include <QDebug>

QDockWidget *MomentumStrategy::configWidget()
{
    auto widget = new TradingSignalMomentum();
    connect(widget, &TradingSignalMomentum::newMomentum,
            this, &MomentumStrategy::processMomentum);
    connect(widget, &TradingSignalMomentum::deleteMomentum,
            this, &MomentumStrategy::removeMomentum);

    return widget;
}

void MomentumStrategy::processTrade(const Trade &t)
{
    if(m_momentums.contains(t.instrument())) {
        MomentumData &data = m_momentums[t.instrument()];

        if (t.volume() >= data.previousVolume) {
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

        if (data.consecutiveChangesRequired <= data.currentConsecutiveChanges) {
            data.currentConsecutiveChanges = 0;

                if (data.isRising) {
                    if (!data.bought) {
                        data.sold = false;
                        data.bought = true;

                        auto r = Record::Ptr::create();
                        r->setBidId(6666);
                        r->setAskId(0);
                        r->setBidOrAsk(Record::BidAsk::Bid);
                        r->setDate(t.date());
                        r->setTime(t.time());
                        r->setInstrument(t.instrument());
                        r->setType(Record::Type::ENTER);
                        r->setVolume(data.volume);
                        r->setPrice(t.price());
                        r->setValue(r->price() * r->volume());
                        emit newRecordCreated(r);
                        qDebug() << "created a bid";

                    }
                } else {
                    if (!data.sold) {
                        data.sold = true;
                        data.bought = false;

                        auto r = Record::Ptr::create();
                        r->setAskId(6666);
                        r->setBidId(0);
                        r->setBidOrAsk(Record::BidAsk::Ask);
                        r->setDate(t.date());
                        r->setTime(t.time());
                        r->setInstrument(t.instrument());
                        r->setType(Record::Type::ENTER);
                        r->setVolume(data.volume);
                        r->setPrice(t.price());
                        r->setValue(r->price() * r->volume());
                        emit newRecordCreated(r);

                        qDebug() << "created a ask";

                    }
                }


        }
    }
}

void MomentumStrategy::reset()
{
    for (const QString &ins : m_momentums.keys()) {
        m_momentums[ins] = MomentumData();
    }
}


MomentumStrategy::MomentumStrategy(QObject *parent) :
    QObject(parent)
{
}

void MomentumStrategy::processMomentum(const QString &instrument, const QString &volume, const QString &change) {
    //we save the momentum strategy.
    MomentumData data;
    data.consecutiveChangesRequired = change.toInt();
    data.volume = volume.toInt();
    m_momentums.insert(instrument, data);
}

void MomentumStrategy::removeMomentum(const QString &instrument) {
    m_momentums.remove(instrument);
}
