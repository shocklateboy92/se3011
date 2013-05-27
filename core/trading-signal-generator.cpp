#include "trading-signal-generator.h"
#include "record.h"

#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>
#include <limits>
#include <QDir>

TradingSignalGenerator::TradingSignalGenerator(QObject *parent) :
    QObject(parent)
{
}

const QList<QDockWidget*> TradingSignalGenerator::configWidgets()
{
    QList<QDockWidget*> ret;
    ret.reserve(m_strategies.size());
    for (auto s : m_strategies) {
        ret.append(s->configWidget());
    }

    return ret;
}

void TradingSignalGenerator::processNewRecord(const Record &r) {
    m_records.append(r);
    emit newRecordGenerated(r);
}

void TradingSignalGenerator::dataProcessingRequested() {
    while(!m_records.isEmpty()) {
        auto r = m_records.takeFirst();
        qDebug() << r;
        Record::Ptr rp = Record::Ptr::create();
        *rp = r;
        emit nextRecord(rp);
    }
}

void TradingSignalGenerator::loadPlugins()
{
    auto pluginsDir = QDir(QCoreApplication::instance()->applicationDirPath());

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" ||
            pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("../strategies/");
    qDebug() << pluginsDir;

    foreach (QString sub, pluginsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        qDebug() << "Sub: " << sub;
        pluginsDir.cd(sub);
        //qDebug() << pluginsDir;
        foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
            addNewPlugin(pluginsDir.absoluteFilePath(fileName));
        }
        pluginsDir.cdUp();
        //qDebug() << pluginsDir;

    }

    qDebug() << m_strategies;
}

QDockWidget* TradingSignalGenerator::addNewPlugin(QString fileName)
{
//        qDebug() << "trying to load " << fileName;
    QPluginLoader loader(fileName);
    QObject *plugin = loader.instance();
    if (plugin) {
        TradingStrategy *strategy = qobject_cast<TradingStrategy*>(plugin);
        if (strategy) {
            m_strategies.append(strategy);

            connect (plugin, SIGNAL(newRecordCreated(Record::Ptr)),
                     this, SIGNAL(nextRecord(Record::Ptr)));
            return strategy->configWidget();
        }
    } else {
//            qWarning() << "Failed to load" << fileName << ":"
//                       << loader.errorString();
    }
    return nullptr;
}

void TradingSignalGenerator::reset()
{
    for (TradingStrategy *s : m_strategies) {
        s->reset();
    }
}

void TradingSignalGenerator::processTrade(const Trade &t) {

    for (TradingStrategy *strategy : m_strategies) {
        strategy->processTrade(t);
    }


}
