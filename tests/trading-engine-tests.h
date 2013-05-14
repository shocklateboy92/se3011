#ifndef TRADINGENGINETESTS_H
#define TRADINGENGINETESTS_H

#include <QTest>
#include <trading-engine.h>

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
        Record a1 = create();
        a1.setBidOrAsk(Record::BidAsk::Ask);
        a1.setPrice(10);
        a1.setVolume(20);

        Record a2 = create();
        a2.setBidOrAsk(Record::BidAsk::Ask);
        a2.setPrice(15);
        a2.setVolume(30);

        Record b1 = create();
        b1.setBidOrAsk(Record::BidAsk::Bid);
        b1.setPrice(20);
        b1.setVolume(40);

        m_engine->enterAsk(Ask(QSharedPointer<Record>(&a1)));
        m_engine->enterAsk(Ask(QSharedPointer<Record>(&a2)));
        m_engine->enterBid(Bid(QSharedPointer<Record>(&b1)));

        QCOMPARE(m_engine->m_bidQueue.size(), 1);

        Bid rb = m_engine->m_bidQueue.first();
        QCOMPARE(rb.record(), &b1);

        QEXPECT_FAIL("", "createTrade will remove them from the queue", Continue);
        QCOMPARE(m_engine->m_askQueue.size(), 0);
    }

private:
    Record create() {
        Record a1;
        a1.setType(Record::Type::ENTER);
        static long id = 0;
        a1.setAskId(++id);
        a1.setBidId(++id);
        a1.setTime(QTime::currentTime());
        a1.setDate(QDate::currentDate());

        QTest::qSleep(7);
        return a1;
    }

    TradingEngine *m_engine;
};

#endif // TRADINGENGINETESTS_H
