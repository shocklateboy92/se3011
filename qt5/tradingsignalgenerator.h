#ifndef TRADINGSIGNALGENERATOR_H
#define TRADINGSIGNALGENERATOR_H

class TradingSignalGenerator
{
public:
    TradingSignalGenerator();

Q_SIGNALS:
    void newRecordGenerated();
};

#endif // TRADINGSIGNALGENERATOR_H
