#include "processingstatus.h"

ProcessingStatus::ProcessingStatus(QObject *parent)
    :QObject(parent)
{
    runSumsProcessing = false;
    runMultipleProcessing = false;
    runSumsOk = false;
    runMultipleOk = false;
    selectedVariants = QVector<bool>(VARIANT_MAX);
    selectedVariants.fill(false);
    tabs = QVector<bool>(TABS_NUMBER);
    tabs.fill(true);
}

void ProcessingStatus::init()
{
    for (int i=2; i<TABS_NUMBER; i++)
        tabs[i] = false;
    emit signalEnableTabs(tabs);
}

void ProcessingStatus::setVariants(QVector<bool> v)
{
    selectedVariants = v;
}

QVector<bool> ProcessingStatus::getVariants()
{
    return selectedVariants;
}

void ProcessingStatus::slotRunSumsStarted()
{
    runSumsProcessing = true;
    runSumsOk = false;
    runMultipleOk = false;
    runMultipleProcessing = false;

    for (int i=0; i<TABS_NUMBER; i++)
        tabs[i] = true;
    for (int i=2; i<TABS_NUMBER; i++)
        tabs[i] = false;
    tabs[0] = false; //don't move variants

    emit signalEnableTabs(tabs);
}

void ProcessingStatus::slotRunSumsFinished(bool status)
{
    runSumsProcessing = false;
    runSumsOk = status;

    for (int i=0; i<TABS_NUMBER; i++)
        tabs[i] = true;
    for (int i=2; i<TABS_NUMBER; i++)
        tabs[i] = false;
    if (status) {
        tabs[2] = true;
        tabs[3] = true;
    }

    emit signalEnableTabs(tabs);
}

void ProcessingStatus::slotRunMultipleStarted()
{
    runMultipleProcessing = true;
    runMultipleOk = false;

    for (int i=0; i<TABS_NUMBER; i++)
        tabs[i] = false;
    tabs[1] = true;
    tabs[2] = true;
    tabs[3] = true;

    emit signalEnableTabs(tabs);
}

void ProcessingStatus::slotRunMultipleFinished(bool status)
{
    runMultipleProcessing = false;
    runMultipleOk = status;

    for (int i=0; i<TABS_NUMBER; i++)
        tabs[i] = true;
    if (!status) {
        tabs[4] = false;
        tabs[5] = false;
    }

    emit signalEnableTabs(tabs);
}
