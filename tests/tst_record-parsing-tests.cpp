#include <record.h>

#include <QString>
#include <QtTest>
#include "trading-engine-tests.h"

class RecordParsingTests : public QObject
{
    Q_OBJECT
    
public:
    RecordParsingTests();
    
private Q_SLOTS:
    void simpleParseTest();
    void simpleParseTest2();
    void parseBid();
    void parseBid_data();
};

RecordParsingTests::RecordParsingTests()
{
}

//#Instrument,Date,Time,Record Type,Price,Volume,Undisclosed Volume,Value,Qualifiers,Trans ID,Bid ID,Ask ID,Bid/Ask,Entry Time,Old Price,Old Volume,Buyer Broker ID,Seller Broker ID
void RecordParsingTests::simpleParseTest() {
    QTextStream ts(QByteArray("BHP,20130501,00:00:00.000,ENTER,32.600,160,0,5216,,0,6263684926150135747,,B,,,,406,"));
    Record r;
    ts >> r;
    QCOMPARE(r.instrument(), QStringLiteral("BHP"));
    QCOMPARE(r.date(), QDate(2013, 5, 1));
    QCOMPARE(r.time(), QTime(0, 0, 0, 0));
    QCOMPARE(r.type(), Record::Type::ENTER);
    QCOMPARE(r.price(), 32.6);
    QCOMPARE(r.volume(), 160.0);
    QCOMPARE(r.value(), 5216.0);
    QCOMPARE(r.bidId(), 6263684926150135747);
    QCOMPARE(r.bidOrAsk(), Record::BidAsk::Bid);
}

void RecordParsingTests::simpleParseTest2() {
    QTextStream ts(QByteArray("AZJ,20130501,00:00:00.000,ENTER,3.600,160,0,576,,0,6263684926150135747,,A,,,,406,"));
    Record r;
    ts >> r;
    QCOMPARE(r.instrument(), QStringLiteral("AZJ"));
    QCOMPARE(r.date(), QDate(2013, 5, 1));
    QCOMPARE(r.time(), QTime(0, 0, 0, 0));
    QCOMPARE(r.type(), Record::Type::ENTER);
    QCOMPARE(r.price(), 3.6);
    QCOMPARE(r.volume(), 160.0);
    QCOMPARE(r.value(), 576.0);
    QCOMPARE(r.bidId(), 6263684926150135747);
    QCOMPARE(r.bidOrAsk(), Record::BidAsk::Ask);
}

void RecordParsingTests::parseBid()
{
    QFETCH(QByteArray, line);

    {
        Record r;
        QTextStream ts(line);
        ts >> r;

        QTEST(r.instrument(), "instrument");
        QTEST(r.date(), "date");
        QTEST(r.time(), "time");
        QCOMPARE(r.type(), Record::Type::ENTER);
        QTEST(r.price(), "price");
        QTEST(r.volume(), "volume");
        QTEST(r.value(), "value");
        QTEST(r.bidId(), "bidId");
        QCOMPARE(r.bidOrAsk(), Record::BidAsk::Bid);

//        QEXPECT_FAIL("BHP-1", "not implemented yet", Continue);
//        QTEST(r.buyerId(), "buyerId");
    }

    {
        QBENCHMARK {
            Record r;
            QTextStream ts(line);
            ts >> r;
        }
    }
}

void RecordParsingTests::parseBid_data()
{
    QTest::addColumn<QByteArray>("line");
    QTest::addColumn<QString>("instrument");
    QTest::addColumn<QDate>("date");
    QTest::addColumn<QTime>("time");
    QTest::addColumn<double>("price");
    QTest::addColumn<double>("volume");
    QTest::addColumn<double>("value");
    QTest::addColumn<long>("bidId");
    QTest::addColumn<long>("buyerId");

    QTest::newRow("BHP-1") << QByteArray("BHP,20130501,00:00:00.000,ENTER,32.600,160,0,5216,,0,6263684926150135747,,B,,,,406,") << QString("BHP") << QDate(2013, 5, 1) << QTime(0, 0, 0, 0) << 32.6 << 160.0 << 5216.0 << 6263684926150135747l << 406l;
}


int main(int argc, char* argv[]) {
    int status = 0;
    {
        TradingEngineTests t;
        status |= QTest::qExec(&t, argc, argv);
    }
    {
        RecordParsingTests t;
        status |= QTest::qExec(&t, argc, argv);
    }

    return 0;
}

#include "tst_record-parsing-tests.moc"
