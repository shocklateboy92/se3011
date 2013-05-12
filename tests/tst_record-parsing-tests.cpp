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
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void RecordParsingTests::parseLine_data()
{
    QTest::addColumn<QString>("instrument");
    QTest::addColumn<QDate>("date");
    QTest::addColumn<QTime>("time");
    QTest::newRow({"BHP"});
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
