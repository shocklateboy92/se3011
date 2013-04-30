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

void TradingSignalGenerator::processMomentum(const QString &instrument, const QString &change) {
    //we save the momentum strategy.
    MomentumData data;
    data.consecutiveChangesRequired = change.toInt();
    m_momentums.insert(instrument, data);
}

void TradingSignalGenerator::processTrade(const Trade &t) {
    MomentumData &data = m_momentums[t.instrument()];
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
    data.currentConsecutiveChanges++;

    if (data.consecutiveChangesRequired <= data.currentConsecutiveChanges) {
        data.currentConsecutiveChanges = 0;
        auto r = Record();
        if (data.isRising) {
            r.setBidId(6666);
            r.setBidOrAsk(Record::BidAsk::Bid);
        } else {
            r.setAskId(6666);
            r.setBidOrAsk(Record::BidAsk::Ask);
        }
        r.setBidOrAsk(data.isRising ? Record::BidAsk::Bid : Record::BidAsk::Ask);
        r.setDate(QDate::currentDate());
        r.setTime(QTime::currentTime());
        r.setInstrument(t.instrument());
        r.setType(Record::Type::ENTER);
        r.setVolume(data.tradeVolume);
        r.setPrice(t.price());
        r.setValue(r.price() * r.volume());
        emit nextRecord(r);
    }
}
