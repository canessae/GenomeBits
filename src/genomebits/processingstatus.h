#ifndef PROCESSINGSTATUS_H
#define PROCESSINGSTATUS_H

#include <QObject>
#include <QList>
#include <QVector>

#define TABS_NUMBER    6
#define VARIANT_MAX    6

class ProcessingStatus : public QObject
{
    Q_OBJECT

public:
    ProcessingStatus(QObject *parent = NULL);
    void init();
    void setVariants(QVector<bool> v);
    QVector<bool> getVariants();

private:
    QVector<bool> tabs;
    QVector<bool> selectedVariants;
    bool runSumsProcessing, runSumsOk;
    bool runMultipleProcessing, runMultipleOk;

public slots:
    void slotRunSumsStarted();
    void slotRunSumsFinished(bool status);
    void slotRunMultipleStarted();
    void slotRunMultipleFinished(bool status);

signals:
    void signalEnableTabs(QVector<bool>);
};

#endif // PROCESSINGSTATUS_H
