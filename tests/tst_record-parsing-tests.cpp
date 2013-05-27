#include <record.h>

#include <QString>
#include <QtTest>
#include "trading-engine-tests.h"

const char str[] = "084394583.467";
const char line[]= "BHP,20130501,00:00:00.000,ENTER,32.600,160,0,5216,,0,6263684926150135747,,B,,,,406,";
class RecordParsingTests : public QObject
{
    Q_OBJECT
    
public:
    RecordParsingTests();

private:
    
private Q_SLOTS:
    void simpleParseTest();
    void simpleParseTest2();
    void parseBid();
    void parseBid_data();
    void testFastParse();

    void qStringBench() {
        QString qstr = QString(str);
        QBENCHMARK {
            qstr.toDouble();
        }
    }
    void byteArrayBench() {
        QSet<int> fields;
        bool fs[static_cast<int>(Record::Field::NotAField)];
        QByteArray bstr = QByteArray(str);
        QBENCHMARK {
            bstr.toDouble(&fs[static_cast<int>(Record::Field::Price)]);
//            fields.insert(static_cast<int>(Record::Field::Price));
        }
    }
    void cStringBench() {
        QSet<int> fields;
        QBENCHMARK {
//            fields.insert(static_cast<int>(Record::Field::Price));
            strtod(str, NULL);
        }
    }

//    void parseBenchOld() {
//        QBENCHMARK {
//            Record r;
//            QTextStream ts(line);
//            ts >> r;
//        }
//    }

    void parseBenchNew() {
        QBENCHMARK {
            Record::fromCSV(line);
        }
    }
};


RecordParsingTests::RecordParsingTests()
{
}

//#Instrument,Date,Time,Record Type,Price,Volume,Undisclosed Volume,Value,Qualifiers,Trans ID,Bid ID,Ask ID,Bid/Ask,Entry Time,Old Price,Old Volume,Buyer Broker ID,Seller Broker ID
void RecordParsingTests::simpleParseTest() {
    Record::Ptr r = Record::fromCSV(QByteArray("BHP,20130501,00:00:00.000,ENTER,32.600,160,0,5216,,0,6263684926150135747,,B,,,,406,"));

    QCOMPARE(r->instrument(), QByteArray("BHP"));
    QCOMPARE(r->date(), QDate(2013, 5, 1));
    QCOMPARE(r->time(), QTime(0, 0, 0, 0));
    QCOMPARE(r->type(), Record::Type::ENTER);
    QCOMPARE(r->price(), 32.6);
    QCOMPARE(r->volume(), 160.0);
    QCOMPARE(r->value(), 5216.0);
    QCOMPARE(r->bidId(), 6263684926150135747);
    QCOMPARE(r->bidOrAsk(), Record::BidAsk::Bid);
}

void RecordParsingTests::simpleParseTest2() {
    Record::Ptr r = Record::fromCSV(QByteArray("AZJ,20130501,00:00:00.000,ENTER,3.600,160,0,576,,0,6263684926150135747,,A,,,,406,"));

    QCOMPARE(r->instrument(), QByteArray("AZJ"));
    QCOMPARE(r->date(), QDate(2013, 5, 1));
    QCOMPARE(r->time(), QTime(0, 0, 0, 0));
    QCOMPARE(r->type(), Record::Type::ENTER);
    QCOMPARE(r->price(), 3.6);
    QCOMPARE(r->volume(), 160.0);
    QCOMPARE(r->value(), 576.0);
    QCOMPARE(r->bidId(), 6263684926150135747);
    QCOMPARE(r->bidOrAsk(), Record::BidAsk::Ask);
}

void RecordParsingTests::parseBid()
{
    QFETCH(QByteArray, line);

    {
        Record::Ptr r = Record::fromCSV(line);

        QTEST(r->instrument(), "instrument");
        QTEST(r->date(), "date");
        QTEST(r->time(), "time");
        QCOMPARE(r->type(), Record::Type::ENTER);
        QTEST(r->price(), "price");
        QTEST(r->volume(), "volume");
        QTEST(r->value(), "value");
        QTEST(r->bidId(), "bidId");
        QCOMPARE(r->bidOrAsk(), Record::BidAsk::Bid);

//        QEXPECT_FAIL("BHP-1", "not implemented yet", Continue);
        QTEST(r->buyerId(), "buyerId");
    }
}

void RecordParsingTests::parseBid_data()
{
    QTest::addColumn<QByteArray>("line");
    QTest::addColumn<QByteArray>("instrument");
    QTest::addColumn<QDate>("date");
    QTest::addColumn<QTime>("time");
    QTest::addColumn<double>("price");
    QTest::addColumn<double>("volume");
    QTest::addColumn<double>("value");
    QTest::addColumn<long>("bidId");
    QTest::addColumn<long>("buyerId");

    QTest::newRow("BHP-1") << QByteArray("BHP,20130501,00:00:00.000,ENTER,32.600,160,0,5216,,0,6263684926150135747,,B,,,,406,") << QByteArray("BHP") << QDate(2013, 5, 1) << QTime(0, 0, 0, 0) << 32.6 << 160.0 << 5216.0 << 6263684926150135747l << 406l;
}


void RecordParsingTests::testFastParse() {
    QByteArray bs("BHP,20130501,00:00:00.000,ENTER,32.600,160,0,5216,,0,6263684926150135747,,B,,,,406,");
    Record::Ptr r = Record::fromCSV(bs);
    QCOMPARE(r->instrument(), QByteArray("BHP"));
    QCOMPARE(r->date(), QDate(2013, 5, 1));
    QCOMPARE(r->time(), QTime(0, 0, 0, 0));
    QCOMPARE(r->type(), Record::Type::ENTER);
    QCOMPARE(r->price(), 32.6);
    QCOMPARE(r->volume(), 160.0);
    QCOMPARE(r->value(), 5216.0);
    QCOMPARE(r->bidId(), 6263684926150135747);
    QCOMPARE(r->bidOrAsk(), Record::BidAsk::Bid);
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
