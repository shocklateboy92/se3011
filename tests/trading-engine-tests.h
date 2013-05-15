#ifndef TRADINGENGINETESTS_H
#define TRADINGENGINETESTS_H

#include <QTest>
#include <trading-engine.h>
#include <trading-file-reader.h>

class TradingEngineTests : public QObject
{
    Q_OBJECT
public:
    explicit TradingEngineTests(QObject *parent = 0) :
        QObject(parent), m_engine(nullptr) {}

signals:

private slots:

    void init() {
        delete m_engine;
        m_engine = new TradingEngine();
    }

    void testEnterBid() {
        Ask a1 = createAsk();
        a1.setPrice(10);
        a1.setVolume(20);

        Ask a2 = createAsk();
        a2.setPrice(15);
        a2.setVolume(30);

        Bid b1 = createBid();
        b1.setPrice(20);
        b1.setVolume(40);

        m_engine->enterAsk(a1);
        m_engine->enterAsk(a2);
        m_engine->enterBid(b1);

        QCOMPARE(m_engine->m_bidQueue.size(), 1);

        Bid rb = m_engine->m_bidQueue.first();
        QCOMPARE(rb, b1);
        QCOMPARE(rb.record(), b1.record());

        QCOMPARE(m_engine->m_askQueue.size(), 1);
        Ask remainingAsk = (m_engine->m_askQueue.first());
        QCOMPARE(remainingAsk.volume(), 10.0);
        QCOMPARE(remainingAsk.price(), 15.0);
    }

    void fullSimulationBench() {
        TradingFileReader *reader = new TradingFileReader(
                    "demo8@demo-BHP-GOOD-20130513145016968945.csv", this);
        connect(reader, &TradingFileReader::newRecordEncountered,
                m_engine, &TradingEngine::processNewRecord);
        QBENCHMARK_ONCE {
            reader->startReading();
        }
    }

private:
    Record* create() {
        Record *a1 = new Record;
        a1->setType(Record::Type::ENTER);
        static long id = 0;
        a1->setAskId(++id);
        a1->setBidId(++id);
        a1->setTime(QTime::currentTime());
        a1->setDate(QDate::currentDate());

        QTest::qSleep(7);
        return a1;
    }

    Bid createBid() {
        Bid b = QSharedPointer<Record>(create());
        b.record()->setBidOrAsk(Record::BidAsk::Bid);
        return b;
    }

    Ask createAsk() {
        Ask a = QSharedPointer<Record>(create());
        a.record()->setBidOrAsk(Record::BidAsk::Ask);
        return a;
    }

    TradingEngine *m_engine;
};

#endif // TRADINGENGINETESTS_H
