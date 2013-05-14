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

    void parseLine();
    void parseLine_data();
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

void RecordParsingTests::parseLine()
{
//    QFAIL("Test not legit.");
//    QFETCH(QByteArray, line);
//    QFETCH(QString, instrument);
//    QFETCH(QDate, date);
//    QFETCH(QTime, time);
//    QFETCH(Record::Type, type);
//    QFETCH(double, price);
//    QFETCH(double, volume);
//    QFETCH(double, value);

//    Record r;
//    QTextStream ts(line);
//    ts >> r;

//    QCOMPARE(r.instrument(), instrument);
//    QCOMPARE(r.date(), date);
//    QCOMPARE(r.time(), time);
//    QCOMPARE(r.type(), type);
//    QCOMPARE(r.price(), price);
//    QCOMPARE(r.volume(), volume);
//    QCOMPARE(r.value(), value);
}

void RecordParsingTests::parseLine_data()
{
    QTest::addColumn<QByteArray>("line");
    QTest::addColumn<QString>("instrument");
    QTest::addColumn<QDate>("date");
    QTest::addColumn<QTime>("time");
    QTest::addColumn<Record::Type>("type");
    QTest::addColumn<double>("price");
    QTest::addColumn<double>("volume");
    QTest::addColumn<double>("undisclosedVolume");
    QTest::addColumn<double>("value");
    QTest::addColumn<QByteArray>("qualifiers");
    QTest::addColumn<long>("transactionID");
    QTest::addColumn<long>("bidID");
    QTest::addColumn<long>("askID");
    QTest::addColumn<Record::BidAsk>("bidOrAsk");

//    QTest::newRow("BHP1") << QByteArray("BHP,20130501,00:00:00.000,ENTER,32.600,160,0,5216,,0,6263684926150135747,,B,,,,406,") <<
//                             "BHP" << QDate(2013, 5, 1) << QTime(0, 0, 0, 0) << Record::Type::ENTER << 32.600 << 160.0 << 0.0 << 5216.0 << 0 << 6263684926150135747 << 0 << 0 << Record::BidAsk::Bid << 0 << 0 << 0 << 406;
}


int main(int argc, char* argv[]) {
    int status = 0;
    {
        RecordParsingTests t;
        status |= QTest::qExec(&t, argc, argv);
    }
    {
        TradingEngineTests t;
        status |= QTest::qExec(&t, argc, argv);
    }

    return 0;
}

#include "tst_record-parsing-tests.moc"
