#include "trading-signal-generator.h"
#include "record.h"

#include <QDebug>
#include <limits>

TradingSignalGenerator::TradingSignalGenerator(QObject *parent) :
    QObject(parent)
{
}

void TradingSignalGenerator::processNewRecord(const Record &r) {
    m_records.append(r);
    emit newRecordGenerated(r);
}

void TradingSignalGenerator::dataProcessingRequested() {
    while(!m_records.isEmpty()) {
        auto r = m_records.takeFirst();
        qDebug() << r;
        emit nextRecord(r);
    }
}

void TradingSignalGenerator::processMomentum(const QString &instrument, const QString &volume, const QString &change) {
    //we save the momentum strategy.
    MomentumData data;
    data.consecutiveChangesRequired = change.toInt();
    data.volume = volume.toInt();
    m_momentums.insert(instrument, data);
}



void TradingSignalGenerator::processTrade(const Trade &t) {
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

                        auto r = Record();
                        r.setBidId(6666);
                        r.setAskId(0);
                        r.setBidOrAsk(Record::BidAsk::Bid);
                        r.setDate(QDate::currentDate());
                        r.setTime(QTime::currentTime());
                        r.setInstrument(t.instrument());
                        r.setType(Record::Type::ENTER);
                        r.setVolume(data.volume);
                        r.setPrice(t.price());
                        r.setValue(r.price() * r.volume());
                        emit nextRecord(r);
                        qDebug() << "created a bid";
                    }
                } else {
                    if (!data.sold) {
                        data.sold = true;
                        data.bought = false;

                        auto r = Record();
                        r.setAskId(6666);
                        r.setBidId(0);
                        r.setBidOrAsk(Record::BidAsk::Ask);
                        r.setDate(QDate::currentDate());
                        r.setTime(QTime::currentTime());
                        r.setInstrument(t.instrument());
                        r.setType(Record::Type::ENTER);
                        r.setVolume(data.volume);
                        r.setPrice(t.price());
                        r.setValue(r.price() * r.volume());
                        emit nextRecord(r);

                        qDebug() << "created a ask";
                    }
                }


        }
    }
}
