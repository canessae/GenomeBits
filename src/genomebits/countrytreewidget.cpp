#include "countrytreewidget.h"
#include "common.h"

#include <QApplication>

CountryTreeWidget::CountryTreeWidget(QWidget *parent)
    :QTreeWidget(parent)
{
    setColumnCount(2);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setHeaderItem(new QTreeWidgetItem(static_cast <QTreeWidget*>(NULL),
                                      QStringList() << tr("Sequence") << tr("Path")));
    header()->setStretchLastSection(true);

    connect(this, &CountryTreeWidget::itemDoubleClicked, this, &CountryTreeWidget::slotItemDoubleClicked);
}

CountryTreeWidget::~CountryTreeWidget()
{

}

bool CountryTreeWidget::setCountry(QString country, int variant)
{
    //Set the output initial path
    outputPath = QDir(QString("../scripts/%1-input").arg(variant));

    currentCountry = outputPath.absolutePath()+QDir::separator()+country;
    if (!QFileInfo(currentCountry).exists()) {
        qDebug("setCountry %s -> %s, error", qPrintable(country), qPrintable(currentCountry));
        return false;
    }

    qDebug("setCountry %s -> %s, ok", qPrintable(country), qPrintable(currentCountry));
    return true;
}

void CountryTreeWidget::populateCountryTree()
{  
    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    readIndexFile();
    readDataFromFiles();
    qApp->processEvents();
    header()->setSectionResizeMode(0, QHeaderView::Interactive);
}

void CountryTreeWidget::cleanupContryTree()
{
    QTreeWidgetItem *root = invisibleRootItem();

    int count = root->childCount();
    for (int i=count-1; i>=0; i--) {
        delete root->child(i);
    }

    currentCountry = QString();
}

QFileInfoList CountryTreeWidget::getSequenceDirs(QDir processingDir)
{
    QFileInfoList files = processingDir.entryInfoList(QStringList()<<"*",
                                                      QDir::Dirs | QDir::NoDotAndDotDot,
                                                      QDir::NoSort);

    // RAW
    QFileInfo item;
    QList<int> indices;
    foreach (item, files) {
        QStringList tmp = item.fileName().split("-");
        QString index = tmp.at(0);
        indices << index.toInt();
        qDebug("sequence dir: %d %s", index.toInt(), qPrintable(item.absoluteFilePath()));
    }

    // ORDER
    QFileInfoList orderedFiles;
    QList<int> orderedIndices = indices;
    std::sort(orderedIndices.begin(), orderedIndices.end());
    int tmp;
    foreach (tmp, orderedIndices) {
        int position = indices.indexOf(tmp);
        if (position >= 0)
            orderedFiles.append(files.at(position));
        qDebug("ordered file: %s", qPrintable(orderedFiles.last().fileName()));
    }

    return orderedFiles;
}

bool CountryTreeWidget::readDataFromFiles()
{
    QTreeWidgetItem *root = invisibleRootItem();
    QDir processingDir = QDir(currentCountry+QDir::separator()+SUBFOLDER_DATA);
    if (!processingDir.exists())
        return false;

    QFileInfoList files = getSequenceDirs(processingDir);
    QFileInfo itemFile;

    //The number of dirs MUST be the same as childCount
    if (files.count() != root->childCount()) {
        qWarning("ID info fail not compatible with processing dirs!");
        return false;
    }

    for (int i=0; i<root->childCount(); i++) {
        QDir dir(currentCountry+QDir::separator()+SUBFOLDER_DATA);
        // Fasta
        QFileInfo itemFile = QDir(files.at(i).absoluteFilePath()).entryInfoList(QStringList() << "*.fasta").at(0);
        if (itemFile.exists()) {
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "Fasta" << dir.relativeFilePath(dir.relativeFilePath(itemFile.absoluteFilePath())));
        }
        //qDebug("%s -> %s", qPrintable(root->child(i)->text(0)), qPrintable(dir.relativeFilePath(dir.relativeFilePath(itemFile.absoluteFilePath()))));
        // Plot sums
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+ATvsbp_FILE);
        if (itemFile.exists()) {
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "Plot sums: A,T vs bp" << dir.relativeFilePath(itemFile.absoluteFilePath()));
        }
        // A: 0,1
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+A01_FILE);
        if (itemFile.exists()) {
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "   A: 0,1" << dir.relativeFilePath(dir.relativeFilePath(itemFile.absoluteFilePath())));
        }
        // A: sums
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+Asums_FILE);
        if (itemFile.exists())
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "   A: sums" << dir.relativeFilePath(itemFile.absoluteFilePath()));
        // T: 0,1
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+T01_FILE);
        if (itemFile.exists())
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "   T: 0,1" << dir.relativeFilePath(itemFile.absoluteFilePath()));
        // T: sums
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+Tsums_FILE);
        if (itemFile.exists())
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "   T: sums" << dir.relativeFilePath(itemFile.absoluteFilePath()));

        // Plot sums
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+CGvsbp_FILE);
        if (itemFile.exists())
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "Plot sums: C,G vs bp" << dir.relativeFilePath(itemFile.absoluteFilePath()));
        // C: 0,1
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+C01_FILE);
        if (itemFile.exists())
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "   C: 0,1" << dir.relativeFilePath(itemFile.absoluteFilePath()));
        // C: sums
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+Csums_FILE);
        if (itemFile.exists())
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "   C: sums" << dir.relativeFilePath(itemFile.absoluteFilePath()));
        // G: 0,1
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+G01_FILE);
        if (itemFile.exists())
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "   G: 0,1" << dir.relativeFilePath(itemFile.absoluteFilePath()));
        // G: sums
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+Gsums_FILE);
        if (itemFile.exists())
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "   G: sums" << dir.relativeFilePath(itemFile.absoluteFilePath()));

        // Plot sums
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+ACGTvsbp_FILE);
        if (itemFile.exists())
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "Plot sums: A,C,G,T vs bp" << dir.relativeFilePath(itemFile.absoluteFilePath()));
        // ACGT: sums
        itemFile = QFileInfo(files.at(i).absoluteFilePath()+QDir::separator()+ACGTsums_FILE);
        if (itemFile.exists())
            QTreeWidgetItem *item = new QTreeWidgetItem(root->child(i), QStringList() << "   ACGT: sums" << dir.relativeFilePath(itemFile.absoluteFilePath()));
    }

    return true;
}

bool CountryTreeWidget::readIndexFile()
{
    QTreeWidgetItem *root = invisibleRootItem();
    QString indexFile = currentCountry+QDir::separator()+INDEX_FILE;

    QFile file(indexFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString sequence = in.readLine();
        qDebug("%s", qPrintable(sequence));
        root->addChild(new QTreeWidgetItem(QStringList() << sequence));
    }

    file.close();
    return true;
}

void CountryTreeWidget::displayPng(QString filename)
{
    AspectRatioPixmapLabel *widget = new AspectRatioPixmapLabel();
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->setWindowTitle(QFileInfo(filename).fileName());
    widget->setPixmap(QPixmap(filename));
    widget->show();

}

void CountryTreeWidget::displayTxt(QString filename, int columns)
{
    ShowText *widget = new ShowText;
    widget->loadTxtFile(filename);
    widget->show();
}

void CountryTreeWidget::slotItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QDir processingDir = QDir(currentCountry+QDir::separator()+SUBFOLDER_DATA);

    qDebug("item double clicked: %s %d", qPrintable(item->text(1)), column);
    QString filename = processingDir.absolutePath()+QDir::separator()+item->text(1);

    if (QFileInfo(item->text(1)).suffix() == "png") {
        displayPng(filename);
    }
    else if (!item->text(1).isEmpty())
        displayTxt(filename);
}
