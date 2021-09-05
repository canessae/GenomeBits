#include "plottreewidget.h"

PlotTreeWidget::PlotTreeWidget(QWidget *parent)
    :QTreeWidget(parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    header()->setStretchLastSection(true);

    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    qApp->processEvents();
    header()->setSectionResizeMode(0, QHeaderView::Interactive);

    connect(this, &PlotTreeWidget::itemDoubleClicked, this, &PlotTreeWidget::slotItemDoubleClicked);
}

void PlotTreeWidget::setVariant(QStringList countries, int variant)
{
    //Set the output initial path
    outputPath = QDir(QString("../scripts/%1-input-PLOTS").arg(variant));

    this->countries = countries;
    qDebug("setCountry %d -> %s-%s, ok", variant, qPrintable(countries.at(0)), qPrintable(countries.at(1)));
}

void PlotTreeWidget::cleanupTree()
{
    QTreeWidgetItem *root = invisibleRootItem();

    for (int i=0; i<3; i++) {
        for (int j=0; j<4; j++)
            root->child(i)->child(j)->setText(1, QString());
    }
}

void PlotTreeWidget::populateTree()
{
    QTreeWidgetItem *root = invisibleRootItem();
    QDir dir(QString(ROOTPLOT));

    // Paths for country1 and 2
    QString country;
    int idx = 0;
    foreach (country, countries) {
        qDebug("processing country %s", qPrintable(country));
        if (!country.isEmpty()) {
            QFileInfoList list = getFilesForCountry(country);
            for (int i=0; i<4; i++) {
                QString filename = list.at(i).absoluteFilePath();
                filename = dir.relativeFilePath(filename);
                root->child(idx)->child(i)->setText(1, filename);
            }
        }
        idx++;
    }

    // Paths for country 1&2
    QFileInfoList list = getFilesForBothCountries();
    for (int i=0; i<4; i++) {
        QString filename = list.at(i).absoluteFilePath();
        filename = dir.relativeFilePath(filename);
        root->child(idx)->child(i)->setText(1, filename);
    }

    // Open tree
    expandAll();

    // Refresh column width with respect to content
    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    qApp->processEvents();
    header()->setSectionResizeMode(0, QHeaderView::Interactive);
}

QString PlotTreeWidget::getParentCountryFromItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem *root = invisibleRootItem();
    QString ret;

    if (item == NULL)
        return ret;

    if (item->parent() == root)
        ret = item->text(0);
    else if (item->parent()->parent() == root) {
        ret = item->parent()->text(0);
    }

    return ret;
}

QFileInfoList PlotTreeWidget::getFilesForBothCountries()
{
    QFileInfoList ret;

    QDir processingPath = outputPath;
    qDebug("getFilesForBothCountries: %s", qPrintable(processingPath.absolutePath()));
    ret << processingPath.entryInfoList(QStringList() << ALLAPATH, QDir::Files);
    qDebug("  %s", qPrintable(ret.last().absoluteFilePath()));
    ret << processingPath.entryInfoList(QStringList() << ALLTPATH, QDir::Files);
    qDebug("  %s", qPrintable(ret.last().absoluteFilePath()));
    ret << processingPath.entryInfoList(QStringList() << ALLCPATH, QDir::Files);
    qDebug("  %s", qPrintable(ret.last().absoluteFilePath()));
    ret << processingPath.entryInfoList(QStringList() << ALLGPATH, QDir::Files);
    qDebug("  %s", qPrintable(ret.last().absoluteFilePath()));

    return ret;
}

QFileInfoList PlotTreeWidget::getFilesForCountry(QString country)
{
    QFileInfoList ret;

    QDir processingPath = QDir( outputPath.absolutePath()+QDir::separator()+APATH );
    ret << processingPath.entryInfoList(QStringList() << QString("*-%1.png").arg(country.toUpper()), QDir::Files);
    qDebug("getFilesForCountry %s", qPrintable(ret.last().fileName()));
    processingPath = QDir( outputPath.absolutePath()+QDir::separator()+TPATH );
    ret << processingPath.entryInfoList(QStringList() << QString("*-%1.png").arg(country.toUpper()), QDir::Files);
    qDebug("getFilesForCountry %s", qPrintable(ret.last().fileName()));
    processingPath = QDir( outputPath.absolutePath()+QDir::separator()+CPATH);
    ret << processingPath.entryInfoList(QStringList() << QString("*-%1.png").arg(country.toUpper()), QDir::Files);
    qDebug("getFilesForCountry %s", qPrintable(ret.last().fileName()));
    processingPath = QDir( outputPath.absolutePath()+QDir::separator()+GPATH );
    ret << processingPath.entryInfoList(QStringList() << QString("*-%1.png").arg(country.toUpper()), QDir::Files);
    qDebug("getFilesForCountry %s", qPrintable(ret.last().fileName()));

    return ret;
}

void PlotTreeWidget::slotItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QDir processingDir(ROOTPLOT);

    qDebug("item double clicked: %s %d", qPrintable(item->text(1)), column);
    QString filename = processingDir.absolutePath()+QDir::separator()+item->text(1);

    if (QFileInfo(item->text(1)).suffix() == "png") {
        displayPng(filename);
    }
    else if (!item->text(1).isEmpty())
        displayTxt(filename);
}

void PlotTreeWidget::displayPng(QString filename)
{
    AspectRatioPixmapLabel *widget = new AspectRatioPixmapLabel();
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->setWindowTitle(QFileInfo(filename).fileName());
    widget->setPixmap(QPixmap(filename));
    widget->show();
}

void PlotTreeWidget::displayTxt(QString filename, int columns)
{
    ShowText *widget = new ShowText;
    widget->loadTxtFile(filename);
    widget->show();
}
