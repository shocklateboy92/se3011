#include <record.h>

#include <QString>
#include <QtTest>

class RecordParsingTests : public QObject
{
    Q_OBJECT
    
public:
    RecordParsingTests();
    
private Q_SLOTS:
    void parseLine();
    void parseLine_data();
};

RecordParsingTests::RecordParsingTests()
{
}

void RecordParsingTests::parseLine()
{
    QFETCH(QByteArray, line);
    QFETCH(QString, instrument);
    QFETCH(QDate, date);
    QFETCH(QTime, time);
    QFETCH(Record::Type, type);
    QFETCH(double, price);
    QFETCH(double, volume);
    QFETCH(double, value);

    Record r;
    QTextStream ts(line);
    ts >> r;

    QCOMPARE(r.instrument(), instrument);
    QCOMPARE(r.date(), date);
    QCOMPARE(r.time(), time);
    QCOMPARE(r.type(), type);
    QCOMPARE(r.price(), price);
    QCOMPARE(r.volume(), volume);
    QCOMPARE(r.value(), value);
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
    QTest::addColumn<double>("value");

    QTest::newRow("GUD1") << QByteArray("GUD,20130102,10:04:32.025,TRADE,8.750,1,8.75,,,,,,,AC XT")
                          << "GUD"
                          << QDate(2013, 01, 02)
                          << QTime(10, 4, 32, 25)
                          << Record::Type::TRADE
                          << 8.75
                          << 1.0
                          << 8.75;
}

QTEST_APPLESS_MAIN(RecordParsingTests)

#include "tst_record-parsing-tests.moc"
//#Instrument,  Date,Time,Record Type,Price,Volume,Value,Bid Price,Bid Size,Ask Price,Ask Size,Spread,Relative Spread,Qualifiers
//GUD,20130102,10:04:32.025,TRADE,8.750,1,8.75,,,,,,,AC XT
//GUD,20130102,10:04:32.025,TRADE,8.750,10,87.5,,,,,,,AC
//GUD,20130102,10:04:32.025,TRADE,8.750,145,1268.75,,,,,,,AC
//GUD,20130102,10:04:32.025,TRADE,8.750,59,516.25,,,,,,,AC
//GUD,20130102,10:04:32.025,TRADE,8.750,50,437.5,,,,,,,AC XT
//GUD,20130102,10:04:32.025,TRADE,8.750,224,1960,,,,,,,AC
//GUD,20130102,10:04:32.025,TRADE,8.750,1,8.75,,,,,,,AC XT
//GUD,20130102,10:04:32.025,TRADE,8.750,25,218.75,,,,,,,AC
//GUD,20130102,10:04:32.025,TRADE,8.750,50,437.5,,,,,,,AC
//GUD,20130102,10:04:32.025,TRADE,8.750,50,437.5,,,,,,,AC
