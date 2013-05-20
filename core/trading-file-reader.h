#ifndef TRADINGFILEREADER_H
#define TRADINGFILEREADER_H

#include "record.h"

#include <QTextStream>

class GROUP8_CORE  TradingFileReader : public QObject
{
    Q_OBJECT
public:
    explicit TradingFileReader(const QString &fileName,
                               QObject *parent = 0);

    bool isValid() const;
    QString inputName() const;
signals:
    void newRecordEncountered(Record::Ptr record);
public slots:
    void startReading();

private:
    QIODevice *m_stream;
    QString m_fileName;
    bool m_valid;
};

#endif // TRADINGFILEREADER_H
