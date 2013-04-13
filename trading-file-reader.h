#ifndef TRADINGFILEREADER_H
#define TRADINGFILEREADER_H

#include "record.h"

#include <QObject>
#include <QTextStream>

class TradingFileReader : public QObject
{
    Q_OBJECT
public:
    explicit TradingFileReader(QObject *parent = 0);

signals:
    void newRecordEncountered(const Record &r);
public slots:
    void startReading(QTextStream &is);
};

#endif // TRADINGFILEREADER_H
