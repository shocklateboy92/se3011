#include "momentum-strategy.h"

QWidget *MomentumStrategy::configWidget()
{
    return NULL;
}

void MomentumStrategy::processTrade(const Trade &trade)
{
}


MomentumStrategy::MomentumStrategy(QObject *parent) :
    QObject(parent)
{
}
