#ifndef PLOTTREEWIDGET_H
#define PLOTTREEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHeaderView>
#include <QApplication>
#include <QDir>
#include <QString>

#include "showtext.h"
#include "aspectratiopixmaplabel.h"

#define APATH      "A-sum01"
#define CPATH      "C-sum01"
#define GPATH      "G-sum01"
#define TPATH      "T-sum01"

#define ALLAPATH   "ALL-A-sum01-complete.png"
#define ALLCPATH   "ALL-C-sum01-complete.png"
#define ALLGPATH   "ALL-G-sum01-complete.png"
#define ALLTPATH   "ALL-T-sum01-complete.png"
#define ROOTPLOT   "../scripts"

class PlotTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    PlotTreeWidget(QWidget *parent = NULL);
    void setVariant(QStringList countries, int variant);
    void cleanupTree();
    void populateTree();

private:
    QStringList countries;
    QDir outputPath;
    void displayPng(QString filename);
    void displayTxt(QString filename, int columns=80);
    QString getParentCountryFromItem(QTreeWidgetItem *item);
    QFileInfoList getFilesForCountry(QString country);
    QFileInfoList getFilesForBothCountries();

private slots:
    void slotItemDoubleClicked(QTreeWidgetItem *, int);
};

#endif // PLOTTREEWIDGET_H
