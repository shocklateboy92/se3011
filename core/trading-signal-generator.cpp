#include "trading-signal-generator.h"
#include "record.h"

#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>
#include <limits>
#include <QDir>

TradingSignalGenerator::TradingSignalGenerator(QObject *parent) :
    QObject(parent)
{
}

const QList<QDockWidget*> TradingSignalGenerator::configWidgets()
{
    QList<QDockWidget*> ret;
    ret.reserve(m_strategies.size());
    for (auto s : m_strategies) {
        ret.append(s->configWidget());
    }

    return ret;
}

void TradingSignalGenerator::processNewRecord(const Record &r) {
    m_records.append(r);
    emit newRecordGenerated(r);
}

void TradingSignalGenerator::dataProcessingRequested() {
    while(!m_records.isEmpty()) {
        auto r = m_records.takeFirst();
        qDebug() << r;
        Record::Ptr rp = Record::Ptr::create();
        *rp = r;
        emit nextRecord(rp);
    }
}



void TradingSignalGenerator::processMagic(const QString &instrument) {
    MagicData data;
    m_magic.insert(instrument, data);
}

void TradingSignalGenerator::removeMagic(const QString &instrument) {
    Q_ASSERT(m_magic.contains(instrument));
    m_magic.remove(instrument);

}

void TradingSignalGenerator::loadPlugins()
{
    auto pluginsDir = QDir(QCoreApplication::instance()->applicationDirPath());

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" ||
            pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("../strategies/momentum/");
    qDebug() << pluginsDir;

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
//        qDebug() << "trying to load " << fileName;
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            TradingStrategy *strategy = qobject_cast<TradingStrategy*>(plugin);
            if (strategy) {
                m_strategies.append(strategy);

                connect (plugin, SIGNAL(newRecordCreated(Record::Ptr)),
                         this, SIGNAL(nextRecord(Record::Ptr)));
            }
        } else {
//            qWarning() << "Failed to load" << fileName << ":"
//                       << loader.errorString();
        }
    }

    qDebug() << m_strategies;
}



void TradingSignalGenerator::processTrade(const Trade &t) {

    for (TradingStrategy *strategy : m_strategies) {
        strategy->processTrade(t);
    }

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
                        emit nextRecord(r);
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
                        emit nextRecord(r);

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
             emit nextRecord(r);

             //this is bad.
             data.totalSold += data.totalBought-data.totalSold;
        }
    }
}
