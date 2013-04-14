#ifndef TRADINGFILEREADER_H
#define TRADINGFILEREADER_H

#include "record.h"

#include <QObject>
#include <QTextStream>

class TradingFileReader : public QObject
{
    Q_OBJECT
public:
    explicit TradingFileReader(const QString &fileName,
                               QObject *parent = 0);

    bool isValid() const;
    QString inputName() const;
signals:
    void newRecordEncountered(const Record &r);
public slots:
    void startReading();

private:
    QTextStream m_stream;
    QString m_fileName;
    bool m_valid;
};

#endif // TRADINGFILEREADER_H
