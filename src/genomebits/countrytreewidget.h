#ifndef COUNTRYTREEWIDGET_H
#define COUNTRYTREEWIDGET_H

#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QList>
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileInfoList>
#include <QLabel>
#include <QPixmap>
#include <QTextEdit>
#include <QHeaderView>
#include <QCollator>

#include "aspectratiopixmaplabel.h"
#include "showtext.h"

#define INDEX_FILE       "ID-AllFastaFiles.txt"
#define SUBFOLDER_DATA   "A-FASTA-GISAID-GenomeBits"

#define A01_FILE         "A-01-complete.dat"
#define Asums_FILE       "A-sum01-complete.dat"
#define T01_FILE         "T-01-complete.dat"
#define Tsums_FILE       "T-sum01-complete.dat"
#define ATvsbp_FILE      "AT-complete-curves.png"
#define C01_FILE         "C-01-complete.dat"
#define Csums_FILE       "C-sum01-complete.dat"
#define G01_FILE         "G-01-complete.dat"
#define Gsums_FILE       "G-sum01-complete.dat"
#define CGvsbp_FILE      "CG-complete-curves.png"
#define ACGTsums_FILE    "ACGT-sum01-complete.dat"
#define ACGTvsbp_FILE    "ACGT-complete-curves.png"

class CountryTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    CountryTreeWidget(QWidget *parent = NULL);
    ~CountryTreeWidget();
    bool setCountry(QString country, int variant); //!< Set country path and check if it exists
    void populateCountryTree(); //!< Populate the tree
    void cleanupContryTree(); //!< Clean all items from tree

private:
    QString currentCountry;
    QDir outputPath;

    QFileInfoList getSequenceDirs(QDir processingDir);
    bool readDataFromFiles();
    bool readIndexFile();
    void displayPng(QString filename);
    void displayTxt(QString filename, int columns=80);

private slots:
    void slotItemDoubleClicked(QTreeWidgetItem *, int);
};

#endif // COUTRYTREEWIDGET_H
